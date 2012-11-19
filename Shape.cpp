#include "Shape.h"
#include "Scene.h"

Intersect Shape::intersect(Ray r){
    return Intersect();
  }


Color Shape::intersectColor(Intersect intersection){
   if(!intersection.isHit()){
    return bgColor;
  }

//std::cout << "whoa whoa" << std::endl;

  vec3 result;

  vector<Light *> lights = *(scene.getLights());


//std::cout << "bam" << std::endl;

  if (lights.empty()) {
    return bgColor;
  }


  for (vector<Light *>::iterator lightIter = scene.getLights()->begin();
       lightIter != scene.getLights()->end(); lightIter++) {
    Light *currLight = *lightIter;

    vec3 currLightColor = currLight->getColor().getColors();


    vec3 lightDir = currLight->getDirection(intersection.getPosition());
    vec3 viewDir = scene.getCameraPos() - intersection.getPosition().getPoint();
    vec3 halfDir = glm::normalize(lightDir + viewDir);

    vec3 norm = intersection.getNormal().getDir();

    float lambTerm = max(glm::dot(norm, lightDir), 0.0f);
    vec3 diffcontr = currLightColor * lambTerm * diffuse.getColors();

    float specTerm =
      pow(max(glm::dot(halfDir, norm), 0.0f), shininess);
    vec3 speccontr = currLightColor * specTerm * specular.getColors();

    vec3 contribution = diffcontr + speccontr;

    //std::cout << lambTerm << std::endl;
    //std::cout << "diffuse.getColors()" << diffuse.getColors().x << diffuse.getColors().y << diffuse.getColors().z << std::endl;

    //std::cout << "diff" << diffcontr.x << diffcontr.y << diffcontr.z << std::endl;

    //std::cout << "spec" << speccontr.x << speccontr.y << speccontr.z << std::endl;

    //std::cout << contribution.x << contribution.y << contribution.z << std::endl;
    result += contribution;
  }



  Color finalColor = Color(result.x, result.y, result.z);
  finalColor += emission;
  return finalColor;
}
