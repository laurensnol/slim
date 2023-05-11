#version 330 core

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

in vec3 oNormal;
in vec3 oFragPos;

out vec4 oFragColor;

uniform vec3 uLightColor;
uniform vec3 uLightPosition;
uniform vec3 uViewPosition;
uniform Material uMaterial;

void main()
{
  // Ambient
  vec3 ambient = uLightColor * uMaterial.ambient;

  // Diffuse
  vec3 norm = normalize(oNormal);
  vec3 lightDirection = normalize(uLightPosition - oFragPos);
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = uLightColor * (diff * uMaterial.diffuse);

  // Specular
  vec3 viewDirection = normalize(uViewPosition - oFragPos);
  vec3 reflectDirection = reflect(-lightDirection, norm);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), uMaterial.shininess);
  vec3 specular = uLightColor * (spec * uMaterial.specular);

  vec3 result = ambient + diffuse + specular;
  oFragColor = vec4(result, 1.0);
}