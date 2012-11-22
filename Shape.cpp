#include "Shape.h"
#include "Scene.h"

/*

Intersect Shape::intersect(Ray r){
    return Intersect();
  }



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

*/

void Shape::intersectColor(Intersect intersection, Light* currLight, vec3 cam, vec3 &result){
  // if(!intersection.isHit()){
  //  return ambient;
 // }

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
