#include "Shader.h"

Shader::Shader(const char *filepath)
    : SingletonFile<Shader>(filepath), _rendererID(0)
{
    ShaderProgramSource source = parseShader();
    _rendererID = createShader(source.vertexShader, source.fragmentShader);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(_rendererID));
}

ShaderProgramSource Shader::parseShader()
{
    std::ifstream stream(_filepath);

    enum class ShaderType
    {
        VERTEX = 0,
        FRAGMENT = 1,
        NONE = -1
    };

    ShaderType type = ShaderType::NONE;

    std::string line;
    std::stringstream ss[2];
    
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            if(type == ShaderType::NONE)
                std::cout << "Bad formating.\n";
            else
            {
                ss[(int)type] << line << '\n';
            }
        }
        
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
    unsigned int id;
    GLCall(id = glCreateShader(type));

    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char *msg = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, msg));

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: ";
        std::cout << msg << std::endl;
    }

    return id;
}

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program;
    GLCall(program = glCreateProgram());

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::bind() const {
    GLCall(glUseProgram(_rendererID));
}

void Shader::unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::setUniform1i(Uniform uniform, int value) {
    GLCall(glUniform1i(uniform.location, value));
}

void Shader::setUniform1i(const std::string &name, int value) {
    setUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform4f(Uniform uniform, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(uniform.location, v0, v1, v2, v3));
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    setUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4f(Uniform uniform, const glm::mat4 &matrix)
{
    GLCall(glUniformMatrix4fv(uniform.location, 1, GL_FALSE, &(matrix[0][0])));
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
    setUniformMat4f(getUniformLocation(name), matrix);
}

Shader::Uniform Shader::getUniformLocation(const std::string &name)
{
    if(_uniformLocationCache.find(name) != _uniformLocationCache.end())
        return _uniformLocationCache[name];

    int location;
    GLCall(location = glGetUniformLocation(_rendererID, name.c_str()));

    if(location == -1)
        std::cout << "[Shader] Warning: uniform " << name << " @ " << _filepath
                  << " doesn't exist!\n";

    _uniformLocationCache[name] = location;
    
    return location;
}
