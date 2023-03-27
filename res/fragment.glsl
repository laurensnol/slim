#version 330 core

out vec4 oFragColor;

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
  oFragColor = texture(uTexture, vTexCoord);
}