#version 330 core

out vec4 oFragColor;

in vec4 vColor;
in vec3 vTexCoord;

uniform samplerCube uTexture;

void main()
{
  oFragColor = texture(uTexture, vTexCoord);
}