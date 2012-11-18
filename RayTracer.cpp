#include "RayTracer.h"
#include "Scene.h"
#include "Intersect.h"
#include "Color.h"
#include <stdio.h>

RayTracer::RayTracer(void)
{

}
Color RayTracer::trace(Ray r, int lvl){
  Color black = Color(0.0, 0.0, 0.0);
  if(lvl == 0){
    return black;
  }
  Intersect intersect = closestShape(r);
  if(intersect.isHit()){
    vec3 norm = intersect.getNormal().getDir();
    vec3 vpar = 2*glm::dot(norm, glm::normalize(r.getDir())) * norm;
    vec3 reflectedRay = glm::normalize(r.getDir() - vpar);
    return intersect.getShape()->intersectColor(intersect)+intersect.getShape()->getSpecular();
  }
  return black;
}

Intersect RayTracer::closestShape(Ray r){
	//vector<Shape *>* sceneShapes = scene.getShapes();
	vector<Shape *>::iterator itStart = scene.getShapes()->begin();
	vector<Shape *>::iterator itEnd = scene.getShapes()->end();
	//vector<Shape *> sceneShapes = scene.getShapes();
	//cout << "Scene Shine: " << sceneShapes[0]->getShininess() << endl;
	Intersect closest = Intersect();
	for(;itStart != itEnd; itStart++){
		Intersect currentIntersect = (*itStart)->intersect(r);
		if(currentIntersect.isHit()){
			if(currentIntersect.getT() < closest.getT()){
				closest = currentIntersect;
			}
		}
	}
	return closest;
}
RayTracer::~RayTracer() {

}
