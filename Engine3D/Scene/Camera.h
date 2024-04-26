#pragma once
#include <Engine3D/Core/core.h>
#include <glm/glm.hpp>
namespace Engine3D{
    /**
     * @name Camera
     * @note Represent our different camera perspectives
     * @note Orthographic, Perspective, Scene, and even Player Camera will share similar functionalities from here
     * @note For right now, not in use
     * @note Once we start expanding then we will start designing how the camera architecture will work.
    */
    // class Camera{};

    /**
     * @name OrthographicCameraController
     * @note Just basically a camera that we can use to visually navigate our current active scene
     * @note As of right now we do not have a way of differentiating that
     * @note This is simply for debugging purposes and doing some checks with the renderer. 
    */
    class Camera{
    public: 
        Camera() = default;
        Camera(float l, float r, float b, float t) : projectionMat(glm::ortho(l, r, b, t, -1.0f, 1.0f)), viewMatrix(1.f) {
            viewProjectionMatrix = projectionMat * viewMatrix;
        }

        glm::vec3 GetPosition() { return position; }
        float GetRotation() { return rotation; }

        const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return viewMatrix; }
        const glm::mat4& GetProjectionMatrix() const { return projectionMat; }

        void SetRotation(float rotate){
            rotation = rotate;
            RecomputeMatrix();
        }

        void SetPosition(const glm::vec3& pos){
            position = pos;
            RecomputeMatrix();
        }

        void SetProjection(float l, float r, float b, float t){
            projectionMat = glm::ortho(l, r, b, t, -1.0f, 1.0f);
            viewProjectionMatrix = projectionMat * viewMatrix;
        }

        void RecomputeMatrix(){
            glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position)
							  * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));

            viewMatrix = glm::inverse(transformation);
            viewProjectionMatrix = projectionMat * viewMatrix;
        }

        //! @note The user will be calling this API
        // void GetCameraLocation();
        // void GetViewProjection();
        // void GetTransformationMatrix();
        // void GetModelMatrix();

    private:
        glm::mat4 projectionMat = glm::mat4(1.0f);
        glm::mat4 viewMatrix;
        glm::mat4 viewProjectionMatrix;

        glm::vec3 position = {0.f, 0.f, 0.f};
        float rotation = 1.f;

        // float left = 0.f, right = 0.f, bottom = 0.f, top = 0.f;
    };

    struct CameraBounds{
        CameraBounds() = default;
        CameraBounds(float l, float r, float b, float t) : left(l), right(r), bottom(b), top(t) {}

        float GetWidth() { return right - left; }
        float GetHeight() { return top - bottom; }

        float left, right, bottom, top;
    };

    class OrthographicCameraController{
    public:
        OrthographicCameraController(float ratio, bool rotation = false);

        glm::mat4 GetProjection() { return camera.GetProjectionMatrix(); }

        void OnUpdate(float ts);
        void OnEvent(Event& e);

        // void OnResize(float width, float height);

        Camera& GetCamera() { return camera; }
        Camera GetCamera() const { return camera; }

        float GetZoomLevel() const { return zoomLevel; }
        void SetZoomLevel(float level) { zoomLevel = level; }

        void OnResize(float width, float height);

        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        void CalculateView();

    private:
        float aspectRatio;
        float zoomLevel = 0.f;
        Camera camera;
        CameraBounds bounds;

        bool isRotationEnabled;
        glm::vec3 position = {0.f, 0.f, 0.f};
        float cameraRotation = 0.f;
        float cameraTranslationSpeed = 5.0f, cameraRotationSpeed = 180.0f;
        
    };
};