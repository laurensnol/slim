#version 330 core

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light
{
  vec3 position;
  vec3 color;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec3 oNormal;
in vec3 oFragPos;

out vec4 oFragColor;

uniform vec3 uViewPosition;
uniform Material uMaterial;
uniform Light uLight;

void main()
{
  // Ambient
  vec3 ambient = uLight.ambient * uMaterial.ambient;

  // Diffuse
  vec3 norm = normalize(oNormal);
  vec3 lightDirection = normalize(uLight.position - oFragPos);
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = uLight.diffuse * (diff * uMaterial.diffuse);

  // Specular
  vec3 viewDirection = normalize(uViewPosition - oFragPos);
  vec3 reflectDirection = reflect(-lightDirection, norm);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), uMaterial.shininess);
  vec3 specular = uLight.specular * (spec * uMaterial.specular);

  vec3 result = ambient + diffuse + specular;
  oFragColor = vec4(result * uLight.color, 1.0);
}