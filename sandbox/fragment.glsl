#version 410

in vec3 fColor;

out vec4 oColor;

void main() {
  oColor = vec4(fColor, 1.0);
}
