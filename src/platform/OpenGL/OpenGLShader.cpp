#include "platform/OpenGL/OpenGLShader.h"

#include <glad/gl.h>
#include <spdlog/spdlog.h>
#include <string>
#include <optional>
#include <vector>
#include <fstream>
#include <filesystem>
#include "OpenGLShader.h"
#include "OpenGLShader.h"
#include "OpenGLShader.h"

namespace slim
{
  OpenGLShader::OpenGLShader(std::string_view vertexPath, std::string_view fragmentPath)
  {
    GLuint vertexShader = createShader(vertexPath, OpenGLShaderType::Vertex);
    GLuint fragmentShader = createShader(fragmentPath, OpenGLShaderType::Fragment);

    _id = glCreateProgram();
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);

    GLint success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
      GLchar description[_LOG_LENGTH];
      glGetProgramInfoLog(_id, _LOG_LENGTH, NULL, description);

      std::string_view descriptionString{description};
      spdlog::error("OpenGL: Shader Program linking error: {}", descriptionString);

      glDeleteProgram(_id);
    }

    GLchar description[_LOG_LENGTH];

    glDetachShader(_id, vertexShader);
    glDeleteShader(vertexShader);
    
    glDetachShader(_id, fragmentShader);
    glDeleteShader(fragmentShader);
  }

  OpenGLShader::~OpenGLShader()
  {
    glDeleteProgram(_id);
  }

  void OpenGLShader::bind()
  {
    glUseProgram(_id);
  }

  void OpenGLShader::unbind()
  {
    glUseProgram(0);
  }

  void OpenGLShader::setFloat(const std::string &name, float value)
  {
    uint32_t location = glGetUniformLocation(_id, name.c_str());
    glUniform1f(location, value);
  }

  void OpenGLShader::setFloat2(const std::string &name, const glm::vec2 &value)
  {
    uint32_t location = glGetUniformLocation(_id, name.c_str());
    glUniform2f(location, value.x, value.y);
  }

  void OpenGLShader::setFloat3(const std::string &name, const glm::vec3 &value)
  {
    uint32_t location = glGetUniformLocation(_id, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
  }

  void OpenGLShader::setFloat4(const std::string &name, const glm::vec4 &value)
  {
    uint32_t location = glGetUniformLocation(_id, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
  }

  void OpenGLShader::setInt(const std::string &name, uint32_t value)
  {
    uint32_t location = glGetUniformLocation(_id, name.c_str());
    glUniform1i(location, value);
  }

  GLuint OpenGLShader::createShader(std::string_view path, OpenGLShaderType shaderType)
  {
    // Reading file
    std::string data;
    std::ifstream file(path, std::ios::in);
    if (file.is_open())
      data = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    else
      spdlog::error("OpenGL: Failed to open Shader source: {}", path);

    // Shader creation
    GLuint type = shaderType == OpenGLShaderType::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    const char *source = data.c_str();

    GLuint shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      GLchar description[_LOG_LENGTH];
      glGetShaderInfoLog(shader, _LOG_LENGTH, NULL, description);
      glDeleteShader(shader);

      std::string_view descriptionString{description};
      spdlog::error("OpenGL: Failed to compile shader: {}", descriptionString);
    }

    return shader;
  }
}