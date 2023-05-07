#version 330 core

out vec4 oFragColor;

uniform vec3 uColor;

void main()
{
  oFragColor = vec4(uColor, 1.0);
}