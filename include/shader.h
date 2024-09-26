#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    public:
        unsigned int id;

        Shader(const char* vertexShaderPath, const char * fragmentShaderPath);
        void activate();

        std::string loadShaderSrc(const char* filename);
        GLuint compileShader(const char* filepath, GLenum type);

        // uniform functions
        void setMat4(const std::string& name, glm::mat4 val);
        void setVec3(const std::string& name, glm::vec3 val);
        void setBool(const std::string& name, bool value);
        void setInt(const std::string& name, int value);
        void setFloat(const std::string& name, float value);
        void set4Float(const std::string& name, float v1, float v2, float v3, float v4);
};

#endif
