#pragma once

#ifndef SHADER_H
#define SHADER

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <memory>

#include <GL/glew.h>
#include "GLDebug.h"

#include "glm/glm.hpp"
#include "utils/SingletonFile.h"

struct ShaderProgramSource
{
    std::string vertexShader;
    std::string fragmentShader;
};

class Shader : public SingletonFile<Shader>
{
friend SingletonFile<Shader>;

public:
    using ptr = std::shared_ptr<Shader>;

    struct Uniform {
    friend Shader;
    private:
        int location;
        Uniform(int loc) : location(loc) {}
    };

private:
    Shader(const char *filepath);

private:
    unsigned int _rendererID;
    std::unordered_map<std::string, int> _uniformLocationCache;

public:
    ~Shader();

    void bind() const;
    void unbind() const;

    Shader::Uniform getUniformLocation(const std::string &name);

    void setUniform1i(Shader::Uniform uniform, int value);
    void setUniform1i(const std::string &name, int value);

    void setUniform4f(Shader::Uniform uniform, float v0, float v1, float v2, float v3);
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

    void setUniformMat4f(Shader::Uniform uniform, const glm::mat4 &matrix);
    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);
private:

    ShaderProgramSource parseShader();
    unsigned int compileShader(unsigned int type, const std::string &source);
    unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);
};

#endif
