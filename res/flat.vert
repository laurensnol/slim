#version 330 core

layout (location = 0) in vec3 lPosition;
layout (location = 1) in vec3 lNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 oNormal;
out vec3 oFragPos;

void main()
{
  oNormal = lNormal;
  oFragPos = vec3(uModel * vec4(lPosition, 1.0));
  
  gl_Position = uProjection * uView * uModel * vec4(lPosition, 1.0);
}