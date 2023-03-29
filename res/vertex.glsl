#version 330 core

out vec4 vColor;
out vec3 vTexCoord;

layout (location = 0) in vec3 lPos;
layout (location = 1) in vec3 lColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
  gl_Position = uProjection * uView * uModel * vec4(lPos, 1.0);
  vColor = vec4(lColor, 1.0);
  vTexCoord = lPos;
}