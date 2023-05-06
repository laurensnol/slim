#version 330 core

out vec4 oFragColor;

uniform vec4 uColor;

void main()
{
  oFragColor = uColor;
}