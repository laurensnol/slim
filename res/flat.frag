#version 330 core

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct PointLight
{
  vec3 position;
  vec3 color;
  float intensity;
  float radius;
};

in vec3 oNormal;
in vec3 oFragPos;

out vec4 oFragColor;

uniform vec3 uViewPosition;
uniform Material uMaterial;
uniform PointLight uPointLight;

void main()
{
  // Ambient
  float ambientStrength = 0.2;
  vec3 ambient = uMaterial.ambient * uPointLight.intensity * ambientStrength;

  // Diffuse
  vec3 norm = normalize(oNormal);
  vec3 lightDirection = normalize(uPointLight.position - oFragPos);
  float diff = max(dot(norm, lightDirection), 0.0);

  float diffuseStrength = 0.5;
  vec3 diffuse = diff * uMaterial.diffuse * uPointLight.intensity * diffuseStrength;

  // Specular
  vec3 viewDirection = normalize(uViewPosition - oFragPos);
  vec3 reflectDirection = reflect(-lightDirection, norm);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), uMaterial.shininess);
  vec3 specular = spec * uMaterial.specular * uPointLight.intensity;

  vec3 result = ambient + diffuse + specular;
  oFragColor = vec4(result * uPointLight.color, 1.0);
}