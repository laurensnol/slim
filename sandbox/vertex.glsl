#version 410

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iColor;

out vec3 fColor;

void main() {
  gl_Position = vec4(iPosition, 1.0);
  fColor = iColor;
}
