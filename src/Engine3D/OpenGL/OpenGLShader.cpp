#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/OpenGL/OpenGLShader.h>

namespace Engine3D{
    static GLenum shaderTypeFromString(const std::string& type){
        if(type == "vertex") return GL_VERTEX_SHADER;
        if(type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

        coreLogWarn("Unknown Shader Type!");
        assert(false);
        return 0;
    }

    static std::string shaderTypeToString(const GLenum type){
        switch (type){
        case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
        case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
        }
        coreLogWarn("Unknown Shader Type!");
        assert(false);
        return "";
    }


	OpenGLShader::OpenGLShader(const std::string& n, const std::string& vertex, const std::string& fragment) : name(n) {
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertex;
		sources[GL_FRAGMENT_SHADER] = fragment;

		CompileShaders(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& path) : filepath(path) {
		std::string shaderSource = read(filepath);

        coreLogWarn("Shader Source String ----\n{}", shaderSource);

        if(shaderSource.empty()){
            coreLogError("Shader Source returned from read(const std::string&) was null terminated!");
            return;
        }

		auto src = preProcess(shaderSource);

		CompileShaders(src);

		// Examples Filepath: asets/shaders/Texture.glsl
        // Essentially how we will extract Texture.glsl from the filepath.
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

        auto lastDot = filepath.rfind('.');
        // If no dot found, then the count is the filepath.size() - lastSlash
        // Though if there is a dot (.), then we go backwards until we hit our back slash and that'll be our count
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;

        // This is how we get our name, when every time we load in our shader
        // The name of the file is our key, and the actual shader, is our value in unordered map
        // In Short: Name will be used to get the specific shader, that we're storing
        name = filepath.substr(lastSlash, count);
		coreLogTrace("Path Parsed Name = {}", name);
	}

	OpenGLShader::~OpenGLShader(){
		glDeleteShader(id);
	}

	void OpenGLShader::bind() const{
		glUseProgram(id);
	}

	void OpenGLShader::unbind() const {
		glUseProgram(0);
	}

	uint32_t OpenGLShader::getShaderIDInternal() const { return id; }

	const std::string& OpenGLShader::getShaderNameInternal() const { return name; }

	std::string OpenGLShader::read(const std::string& path){
		std::fstream ins(path, std::ios::in | std::ios::binary);
        std::string result = "";

        if(!ins){
            coreLogError("File was not able to be loaded in OpenGLShader(const string&)");
            coreLogError("Could not open filepath: {}\n", path);
        }
        else{
            ins.seekg(0, std::ios::end);
            result.resize(ins.tellg());
            ins.seekg(0, std::ios::beg);
            ins.read(&result[0], result.size());
            ins.close();
        }

        return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& src){
		std::unordered_map<GLenum, std::string> shaderSources;
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);

        //! @note We start parsing at the beginning of the file looking for #type
        //! @note This "#type" allows us to identify if the shader we are parsing are a vertex or fragment shader
        size_t pos = src.find(typeToken, 0);

        //! @note Then we parse from our starting position
        while(pos != std::string::npos){
            size_t eol = src.find_first_of("\r\n", pos);
            // render_core_assert(eol != std::string::npos, "Syntax Error!");
			assert(eol != std::string::npos);

            size_t begin = pos + typeTokenLength + 1; // being the beginning of the token
            std::string type = src.substr(begin, eol - begin); // extracting that actual string type
            // render_core_assert(shaderTypeFromString(type), "Invalid shader type specifier");
			assert(shaderTypeFromString(type));

            size_t nextLinePos = src.find_first_not_of("\r\n", eol);
            pos = src.find(typeToken, nextLinePos);
            shaderSources[shaderTypeFromString(type)] = src.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? src.size()-1 : nextLinePos));
            coreLogWarn("Shader Type To String is {}", shaderTypeToString(shaderTypeFromString(type)));
        }

        return shaderSources;
	}

	void OpenGLShader::CompileShaders(const std::unordered_map<GLenum, std::string>& sources){
		GLint program = glCreateProgram();

		std::array<GLenum, 3> shaderIDs;
		int glShaderIDIndex = 0; //  Keeping track of shaders

		for(auto& [t, value] : sources){
			GLenum type = t;
			const std::string& src = value;
			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = src.c_str();

			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

			if(isCompiled == GL_FALSE){
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                
                glDeleteShader(shader);

                coreLogError("Vertex Shader compilation failure! (In Shader.cpp)");
                coreLogError("{}", infoLog.data());
                // render_core_assert(false, "Shader compilation error!");
				// assert(false);
                break;
            }

			glAttachShader(program, shader);
            shaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);

		GLint isLinked =0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

		if(isLinked == GL_FALSE){
			GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the program anymore.
            glDeleteProgram(program);
            
            for(GLenum shaderID : shaderIDs){
                glDeleteShader(shaderID);
            }

            // coreLogError("Fragment Shader link failure!");
            coreLogError("{}", infoLog.data());
            // render_core_assert(false, "Shader link error!");
			// assert(false);
            return;
		}

		for(GLenum shaderID : shaderIDs){
			glDetachShader(program, shaderID);
		}

		id = program;
	}

	void OpenGLShader::UploadFloat3(const std::string& name, const glm::vec3& values){
		GLint location = glGetUniformLocation(id, name.c_str());
        glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadFloat4(const std::string& name, const glm::vec4& values){
		GLint location = glGetUniformLocation(id, name.c_str());
        glUniform4f(location, values.x, values.y, values.z, values.w);
	}


    /**
     * 
     * Shader Library Implementations
     * 
     * 
     * 
    */

//    void ShaderLibrary::Add(const Ref<Shader>& shader){
//         auto& name = shader->GetName();
//         if(contains(name)){
//             coreLogWarn("Shader already exists!");
//             assert(false);
//         }

//         shaders[name] = shader;
//    }

//    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader){
//         shaders[name] = shader;
//    }

//    Ref<Shader> ShaderLibrary::Get(const std::string& name){
//         if(!contains(name)){
//             coreLogWarn("Shader named --- {} was not found in ShaderLibrary", name);
//             assert(false);
//         }

//         return shaders[name];
//    }

//    Ref<Shader> ShaderLibrary::Load(const std::string& filepath){
//         auto shader = Shader::Create(filepath);
//         Add(shader);
//         return shader;
//    }

//    void ShaderLibrary::Load(const std::string& name, const std::string& path){
//         auto shader = Shader::Create(path);
//         Add(name, shader);
//    }

//    bool ShaderLibrary::contains(const std::string& name){
//         return shaders.contains(name);
//    }
};