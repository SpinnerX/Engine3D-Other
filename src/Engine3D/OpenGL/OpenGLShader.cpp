#include <Engine3D/Engine3DPrecompiledHeader.h>
#include <Engine3D/interfaces/Shader.h>

namespace Engine3D{
    static GLenum shaderTypeFromString(const std::string& type){
        if(type == "vertex") return GL_VERTEX_SHADER;
        else if(type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

        coreLogWarn("Unknown Shader Type!");
        assert(false);
        return 0;
    }

    Shader::Shader(const std::string& name) : filename(name){
        initializeShaders();
    }

    Shader::Shader(const std::string& vertex, const std::string& fragment) : filename(""){
        initializeShaders(true, vertex, fragment);
    }

    void Shader::initializeShaders(bool isEnabled, const std::string& vertex, const std::string fragment){
        //! @note TODO ---- Time how long it is taking to build shaders

        //! @note This may be needed to change later on.
        //! @note But as of right now, I will allow shaders to pass in the shaders as strings
        //! @note filename.empty() should always be empty when this is enabled
        //! @param isEnabled
        //! @note Should be true to set the sources manually hitting the else.
        if(!isEnabled){
            std::string src = read(filename);
            auto sources = preProcess(src);
            if(!compileShaders(sources)){
                coreLogError("Compiling Shaders failed in file -- {} and in function Shader::initializeShaders()", __FILE__);
                assert(false);
                return;
            }
        }
        else{
            std::unordered_map<GLenum, std::string> sources;
            sources[GL_VERTEX_SHADER] = vertex;
            sources[GL_FRAGMENT_SHADER] = fragment;
            InitializeShaders(sources);
            // if(!compileShaders(sources)){
            //     coreLogError("Compiling Shaders failed in file -- {} and in function Shader::initializeShaders()", __FILE__);
            //     assert(false);
            //     return;
            // }
        }
    }

    Ref<Shader> Shader::Create(const std::string& vertex, const std::string& fragment){
        // return std::shared_ptr<Shader>(vertex, fragment);
        return CreateRef<Shader>(vertex, fragment);
    }

    Ref<Shader> Shader::Create(const std::string& filename){
        // return std::shared_ptr<Shader>(filename);
        return CreateRef<Shader>(filename);
    }

    void Shader::bind(){
        glUseProgram(id);
    }

    void Shader::unbind(){
        glUseProgram(0);
    }

    void Shader::InitializeShaders(std::unordered_map<GLenum, std::string>& srcs){
        GLuint programID = glCreateProgram();
        // std::array<GLenum, 2> glShaderIDs;

        int shaderIndex = 0;

        for(auto[Type, Src] : srcs){
            GLenum type = Type;
            const std::string& src = Src;

            //! @note Creating our shader
            uint32_t shader = glCreateShader(type);

            const GLchar* sourceCStr = src.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE){
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				coreLogError("Vertex Shader compilation failure! (In Shader.cpp)");
                coreLogError("{}", infoLog.data());
				break;
			}

			glAttachShader(programID, shader);
			shaderIds[shaderIndex++] = shader;
        }

        id = programID;

		// Link our program
		glLinkProgram(programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
		
        if (isLinked == GL_FALSE){
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(programID);
			
			for (auto shaderID : shaderIds)
				glDeleteShader(shaderID);

            coreLogError("Fragment Shader link failure!");
            coreLogError("{}", infoLog.data());
			return;
		}

		for (auto shaderID : shaderIds){
			glDetachShader(programID, shaderID);
			glDeleteShader(shaderID);
		}
    }

    std::string Shader::read(const std::string& filename){
        std::ifstream ins(filename, std::ios::in | std::ios::binary);
        std::string result = "";

        if(!ins){
            coreLogError("File was not able to be loaded in OpenGLShader(const string&)");
            coreLogError("Could not open filepath: {}\n", filename);
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

    std::unordered_map<GLenum, std::string> Shader::preProcess(const std::string& src){
        std::unordered_map<GLenum, std::string> shaderSources;
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = src.find(typeToken, 0);

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
        }

        return shaderSources;
    }

    bool Shader::compileShaders(std::unordered_map<GLenum, std::string>& srcs){
        uint32_t programID = glCreateProgram();

        // std::array<GLenum, 3> glShaderIDs;

        uint32_t shaderID = 0;

        // render_core_assert(shaderSources.size() <= 2, "We only support 2 shaders for now!");

        // std::array<GLenum, 3> glShaderIDs;
        // int shaderID = 0; // Keeping track of our shaders

        // Iterating the shader sources to create our shaders
        for(auto& [Type, Source] : srcs){
            GLenum type = Type;
            const std::string& src = Source;
            GLuint shader = glCreateShader(type);

            const GLchar *sourceCStr = src.c_str(); // ID for vertex
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

            // Checking if compiling our shaders ended up failing
            // Then we log that information if it failed.
            if(isCompiled == GL_FALSE){
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
                
                glDeleteShader(shader);

                coreLogError("Vertex Shader compilation failure! (In Shader.cpp)");
                coreLogError("{}", infoLog.data());
                // render_core_assert(false, "Shader compilation error!");
                return false;
            }

            glAttachShader(id, shader);
            shaderIds[shaderID++] = shader;
        }
        id = programID;

        linkShaders(programID);
        return true;
    }

    void Shader::linkShaders(uint32_t& programID){

        //! @note Link our program
        //! @note With our pogram ID being "id"
        glLinkProgram(programID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);

        if (isLinked == GL_FALSE){
            GLint maxLength = 0;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the program anymore.
            glDeleteProgram(programID);
            
            for(GLenum id : shaderIds){
                glDeleteShader(id);
            }

            coreLogError("Fragment Shader link failure!");
            coreLogError("{}", infoLog.data());
            // assert(false);
            // render_core_assert(false, "Shader link error!");
            return;
        }

        for(GLenum id : shaderIds){
            glDetachShader(programID, id);
        }
        id = programID;
    }
};