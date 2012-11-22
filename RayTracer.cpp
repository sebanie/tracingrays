#include "RayTracer.h"
#include "Scene.h"
#include "Intersect.h"
#include "Color.h"
#include <stdio.h>

RayTracer::RayTracer(vector<Shape *>* shapes, vector<Light *>* lights, vec3 camPosn)
{
  _shapes = shapes;
  _lights = lights;
  cam = camPosn;
}



bool RayTracer::blockedByObject(Ray *r, Shape* shape){
	//vector<Shape *>* sceneShapes = scene.getShapes();
	vector<Shape *>::iterator itStart = _shapes->begin();
	vector<Shape *>::iterator itEnd = _shapes->end();
	//vector<Shape *> sceneShapes = scene.getShapes();
	//cout << "checking for blocked" << endl;
	for(;itStart != itEnd; itStart++){
		Shape *current = *itStart;
		//std::cout << "i am a " << this << " compared to " << current << std::endl;
		if ( (current != shape) &&
		     (*itStart)->intersect(*r).isHit() ) {
			//std::cout << "i am blocked" << std::endl;
			return true;
		}
	}
	return false;
}



void RayTracer::trace(Ray r, int lvl, Color& outputColor){
  Color black = Color(0.0, 0.0, 0.0);
//cout << "magic1" << endl;
  if(lvl == 0){
    outputColor.setColors(0, 0, 0);
    return;
  }
//cout << "magic2" << endl;
  Intersect intersect = closestShape(r);
//cout << "magic3" << endl;

  if(intersect.isHit()){
//cout << "magic4" << endl;
    vec3 norm = intersect.getNormal().getDir();
    vec3 reflectedDir = 2*glm::dot(norm, glm::normalize(r.getDir())) * norm;
    reflectedDir = glm::normalize(r.getDir() - reflectedDir);
//cout << "magic5" << endl;

    Shape *currShape = intersect.getShape();
//cout << "oh god why " << _lights->empty() << endl;
    if (_lights->empty()) {
      outputColor.setColors(currShape->getAmbient());
      return;
    }

    vec3 result = vec3(0.0, 0.0, 0.0);
    vec3 contribution = vec3(0.0, 0.0, 0.0);

    for (vector<Light *>::iterator lightIter = _lights->begin();
         lightIter != _lights->end(); lightIter++) {
//cout << "yo what's up" << endl;
      Light *currLight = *lightIter;
//cout << "i hate my life" << endl;
      Ray *lightray = new Ray();
      currLight->generateLightRay(intersect, lightray);
//cout << "so sad" << endl;
      if (!blockedByObject(lightray, currShape)) {
//cout << "sadness" << endl;
        currShape->intersectColor(intersect, currLight, cam, contribution);
        result += contribution;
      }
    //return intersect.getShape()->intersectColor(intersect);

    }
   
//cout << "did i get here?" << endl;
    result += currShape->getEmission().getColors() + currShape->getAmbient().getColors();

    Ray reflect = Ray();
    vec3 offsetInters = intersect.getPosition().getPoint() + 0.001f * reflectedDir;
    reflect.setPoint(Point(offsetInters));
    reflect.setDir(Direction(reflectedDir));
    Color reflectedCol = Color(0, 0, 0);
    trace(reflect, lvl - 1, reflectedCol);

    result += (currShape->getSpecular().getColors() * reflectedCol.getColors());

    if (result[0] > 1.0) result[0] = 1.0;
    if (result[1] > 1.0) result[1] = 1.0;
    if (result[2] > 1.0) result[2] = 1.0;
    Color finalColor = Color(result.x, result.y, result.z);
//cout << "finishes color computation" << endl;
    outputColor.setColors(finalColor);
    return;

  }

//cout << "magic6" << endl;
  outputColor.setColors(black);
}

Intersect RayTracer::closestShape(Ray r){


//cout << "do i got shapes yo?" << _shapes->empty() << endl;

	vector<Shape *>::iterator itStart = _shapes->begin();
//cout << "magic8" << endl;
	vector<Shape *>::iterator itEnd = _shapes->end();


//cout << "magic9" << endl;
	//vector<Shape *> sceneShapes = scene.getShapes();
	//cout << "Scene Shine: " << sceneShapes[0]->getShininess() << endl;
	Intersect closest = Intersect(Intersect());
	for(;itStart != itEnd; itStart++){
//cout << "magic10" << endl;
		Intersect currentIntersect = (*itStart)->intersect(r);
//cout << "magic11" << endl;
		if(currentIntersect.isHit()){
//cout << "magic12" << endl;
//cout << "efja;jkdasd" << endl;
			if(currentIntersect.getT() < closest.getT()){
//cout << "magic13" << endl;
				closest = currentIntersect;
			}
		}
	}
//cout << "magic14" << endl;
	return closest;
}
RayTracer::~RayTracer() {

}
