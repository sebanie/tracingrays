#include "Shape.h"
#include "Scene.h"

/*

Intersect Shape::intersect(Ray r){
    return Intersect();
  }

*/

bool Shape::blockedByObject(Ray *r){
	//vector<Shape *>* sceneShapes = scene.getShapes();
	vector<Shape *>::iterator itStart = scene.getShapes()->begin();
	vector<Shape *>::iterator itEnd = scene.getShapes()->end();
	//vector<Shape *> sceneShapes = scene.getShapes();
	//cout << "checking for blocked" << endl;
	for(;itStart != itEnd; itStart++){
		Shape *current = *itStart;
		//std::cout << "i am a " << this << " compared to " << current << std::endl;
		if ( (current != this) &&
		     (*itStart)->intersect(*r).isHit() ) {
			//std::cout << "i am blocked" << std::endl;
			return true;
		}
	}
	return false;
}

Color Shape::intersectColor(Intersect intersection){
   if(!intersection.isHit()){
    return bgColor;
  }


  vec3 result;

  vector<Light *> lights = *(scene.getLights());

  if (lights.empty()) {
    return bgColor;
  }


  for (vector<Light *>::iterator lightIter = lights.begin();
       lightIter != lights.end(); lightIter++) {
    Light *currLight = *lightIter;

    Ray *lightray;
    currLight->generateLightRay(intersection, lightray);

    //std::cout << lightray->getPos().x << " " << lightray->getPos().y << " " << lightray->getPos().z << std::endl;

    if (!blockedByObject(lightray)) {

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
    //std::cout << "norm " << norm.x << norm.y << norm.z << std::endl;

    //std::cout << "lightdir" << lightDir.x << lightDir.y << lightDir.z << std::endl;

    //std::cout << "diff" << diffcontr.x << diffcontr.y << diffcontr.z << std::endl;

    //std::cout << "spec" << speccontr.x << speccontr.y << speccontr.z << std::endl;

    //std::cout << contribution.x << contribution.y << contribution.z << std::endl;
      result += contribution;

    }

  }



  Color finalColor = Color(result.x, result.y, result.z);
  //finalColor += emission;
  return finalColor;
}
