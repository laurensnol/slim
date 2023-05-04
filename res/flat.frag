#version 330 core

out vec4 oFragColor;

uniform vec4 uColor;
uniform vec4 uLightColor;

void main()
{
  oFragColor = uLightColor * uColor;
}