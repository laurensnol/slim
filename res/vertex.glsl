#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vertexColor;

out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(pos, 1.0);
  color = vec4(vertexColor, 1.0);
}