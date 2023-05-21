#version 330 core

#define AMBIENT_STRENGTH 0.2
#define DIFFUSE_STRENGTH 0.5

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

struct DirectionalLight
{
  vec3 direction;
  vec3 color;
  float intensity;
};

/*
 * Calculates the contribution of a directional light.
 */
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

/*
 * Calculates the contribution of a point light.
 */
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection);

in vec3 oNormal;
in vec3 oFragPos;

out vec4 oFragColor;

uniform vec3 uViewPosition;
uniform Material uMaterial;
uniform DirectionalLight uDirectionalLight;
uniform PointLight uPointLight;

void main()
{
  vec3 normalized = normalize(oNormal);
  vec3 viewDirection = normalize(uViewPosition - oFragPos);
  
  vec3 result = calcDirectionalLight(uDirectionalLight, normalized, viewDirection);
  result += calcPointLight(uPointLight, normalized, viewDirection);

  oFragColor = vec4(result, 1.0);
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
  vec3 lightDirection = normalize(-light.direction);

  // Ambient
  vec3 ambient = uMaterial.diffuse * light.intensity * AMBIENT_STRENGTH;

  // Diffuse
  float diff = max(dot(normal, lightDirection), 0.0);
  vec3 diffuse = uMaterial.diffuse * diff * light.intensity * DIFFUSE_STRENGTH;

  // Specular
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), uMaterial.shininess);
  vec3 specular = uMaterial.specular * spec * light.intensity;

  return (ambient + diffuse + specular) * light.color;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDirection)
{
  vec3 lightDirection = normalize(light.position - oFragPos);

  // Ambient
  vec3 ambient = uMaterial.ambient * light.intensity * AMBIENT_STRENGTH;

  // Diffuse
  float diff = max(dot(normal, lightDirection), 0.0);
  vec3 diffuse = diff * uMaterial.diffuse * light.intensity * DIFFUSE_STRENGTH;

  // Specular
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), uMaterial.shininess);
  vec3 specular = spec * uMaterial.specular * light.intensity;

  // Attenuation
  float dist = length(light.position - oFragPos);
  float attenuation = clamp(1.0 - dist * dist / (light.radius * light.radius), 0.0, 1.0);
  attenuation *= attenuation;

  return (ambient + diffuse + specular) * attenuation * light.color;
}