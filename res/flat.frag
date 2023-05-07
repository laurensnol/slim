#version 330 core

in vec3 oNormal;
in vec3 oFragPos;

uniform vec3 uColor;
uniform vec3 uLightColor;
uniform vec3 uLightPosition;

out vec4 oFragColor;

void main()
{
  // Ambient
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * uLightColor;

  // Diffuse
  vec3 norm = normalize(oNormal);
  vec3 lightDirection = normalize(uLightPosition - oFragPos);
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = diff * uLightColor;

  vec3 result = (ambient + diffuse) * uColor;
  oFragColor = vec4(result, 1.0);
}