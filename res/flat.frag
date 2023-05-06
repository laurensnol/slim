#version 330 core

out vec4 oFragColor;

uniform vec4 uColor;
uniform vec4 uLightColor;

void main()
{
  float ambientStrength = 0.1;
  vec4 ambient = ambientStrength * uLightColor;

  oFragColor = ambient * uColor;
}