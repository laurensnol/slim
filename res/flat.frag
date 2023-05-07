#version 330 core

in vec3 oNormal;
in vec3 oFragPos;

uniform vec3 uColor;
uniform vec3 uLightColor;
uniform vec3 uLightPosition;
uniform vec3 uViewPosition;
uniform float uAmbientStrength;
uniform float uSpecularStrength;
uniform int uShininess;

out vec4 oFragColor;

void main()
{
  // Ambient
  vec3 ambient = uAmbientStrength * uLightColor;

  // Diffuse
  vec3 norm = normalize(oNormal);
  vec3 lightDirection = normalize(uLightPosition - oFragPos);
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = diff * uLightColor;

  // Specular
  vec3 viewDirection = normalize(uViewPosition - oFragPos);
  vec3 reflectDirection = reflect(-lightDirection, norm);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), uShininess);
  vec3 specular = uSpecularStrength * spec * uLightColor;

  vec3 result = (ambient + diffuse + specular) * uColor;
  oFragColor = vec4(result, 1.0);
}