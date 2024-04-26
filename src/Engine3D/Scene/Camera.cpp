#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/Scene/Camera.h>
#include <Engine3D/Event/InputPoll.h>

namespace Engine3D{
    OrthographicCameraController::OrthographicCameraController(float ratio, bool rotation) : aspectRatio(ratio), isRotationEnabled(rotation){
        bounds = CameraBounds(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
        // glClearNamedFramebufferfv = Camera(bounds.left, bounds.right, bounds.bottom, bounds.top);
		camera = Camera(bounds.left, bounds.right, bounds.bottom, bounds.top);
	}

	// A way to control our cameras
	void OrthographicCameraController::OnUpdate(float ts){
		// RENDER_PROFILE_FUNCTION();

        if(InputPoll::IsKeyPressed(ENGINE_KEY_A)){ // RIGHT
			position.x -= std::cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
			position.y -= std::sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
        }
        else if(InputPoll::IsKeyPressed(ENGINE_KEY_D)){ // LEFT
			position.x += std::cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
			position.y += std::sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
        }
        else if(InputPoll::IsKeyPressed(ENGINE_KEY_W)){ // UP
			position.x += -std::sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
			position.y += std::cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
        }
        else if(InputPoll::IsKeyPressed(ENGINE_KEY_S)){ // DOWN
			position.x -= -std::sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
			position.y -= std::cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
        }
		
		// Checking if we set the rotation speed
		if(isRotationEnabled){

			if(InputPoll::IsKeyPressed(ENGINE_KEY_Q)){ // Rotate Right
				cameraRotation -= cameraRotationSpeed * ts;
			}

			if(InputPoll::IsKeyPressed(ENGINE_KEY_E)){ // Rotate Left
				cameraRotation += cameraRotationSpeed * ts;
			}
			
			if(cameraRotation > 180.0f)
				cameraRotation -= 360.0f;
			else if(cameraRotation <= -180.0f)
				cameraRotation += 360.0f;

			// Then we set the camera rotation
			camera.SetRotation(cameraRotation);
		}
		
		camera.SetPosition(position);
		cameraTranslationSpeed = zoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e){
		// RENDER_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<WindowResizeEvent>(bind(this, &OrthographicCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(bind(this, &OrthographicCameraController::OnMouseScrolled));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e){
		// RENDER_PROFILE_FUNCTION();

		zoomLevel -= e.GetYOffset() * 0.25f; // Modify thihs const offset for window resized event event
		
		zoomLevel = std::max(zoomLevel, 0.25f); // This allows us to control our offsets for our zooming level, making sure we don't zoom too far our or zooming in too close.
		CalculateView();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e){
		// RENDER_PROFILE_FUNCTION();
		this->OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
		
	void OrthographicCameraController::CalculateView(){
		bounds = { -aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel };
		camera.SetProjection(bounds.left, bounds.right, bounds.bottom, bounds.top);
	}

	void OrthographicCameraController::OnResize(float width, float height){
		aspectRatio = width / height;
		this->CalculateView(); // recalculates the view when we change and resize the camera controller's w and h.
	}
};