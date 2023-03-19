#include "platform/OpenGL/OpenGLShader.h"

#include <spdlog/spdlog.h>
#include <string>
#include <optional>
#include <vector>
#include <fstream>
#include <filesystem>

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