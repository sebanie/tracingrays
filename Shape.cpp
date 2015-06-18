#include "Shape.h"
#include "Scene.h"


void Shape::intersectColor(Intersect intersection, Light* currLight, vec3 cam, vec3 &result){

  vec3 currLightColor = currLight->getColor().getColors();

  vec3 atten = currLight->getAttenuation();
  float r = 0.f;
  float attenuationDenom = atten.x;

  if (atten.y != 0.0 || atten.z != 0.0) {
    r = intersection.getPosition().dist(currLight->getPosition());
    attenuationDenom += (r * atten.y) + (r * r * atten.z);
  }

  vec3 lightDir = currLight->getDirection(intersection.getPosition());
  vec3 viewDir = cam - intersection.getPosition().getPoint();
  vec3 halfDir = glm::normalize(glm::normalize(lightDir) + glm::normalize(viewDir));

  vec3 norm = glm::normalize(intersection.getNormal().getDir());

  float lambTerm = max(glm::dot(norm, lightDir), 0.0f);
  vec3 diffcontr = (currLightColor / attenuationDenom) * lambTerm * diffuse.getColors();

  float specTerm =
    pow(max(glm::dot(halfDir, norm), 0.0f), shininess);
  vec3 speccontr = (currLightColor / attenuationDenom) * specTerm * specular.getColors();

  vec3 contribution = diffcontr + speccontr;
  
  result.x = contribution.x;
  result.y = contribution.y;
  result.z = contribution.z;
}
