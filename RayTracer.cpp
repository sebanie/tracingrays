#include "RayTracer.h"
#include "Scene.h"
#include "Intersect.h"
#include "Color.h"
#include <stdio.h>
#include <math.h>

RayTracer::RayTracer(vector<Shape *>* shapes, vector<Light *>* lights, vec3 camPosn)
{
  _shapes = shapes;
  _lights = lights;
  cam = camPosn;
}



bool RayTracer::blockedByObject(Ray *r, Shape* shape){
  vector<Shape *>::iterator itStart = _shapes->begin();
  vector<Shape *>::iterator itEnd = _shapes->end();
  for(;itStart != itEnd; itStart++){
    Shape *current = *itStart;
    if (current != shape) {
      Intersect curr = (*itStart)->intersect(*r);
      if (curr.isHit() && (curr.getT() < r->getTMAX())) {
	return true;
      }
    }
  }
  return false;
}

bool refract(vec3 norm, vec3 incident, float ind1, float ind2, Ray &result)
{
  norm = glm::normalize(norm);
  incident = glm::normalize(incident);
  if (ind1 != ind2) {
    float n = ind1 / ind2;
    float DdotN = glm::dot(norm, incident);
    float underSqrt = 1.0 - (n * n * (1.0 - (DdotN * DdotN)));
    if (underSqrt < 0.0) {
      return false;
    }
    float term1 = sqrt(underSqrt);
    vec3 term2 = n * (incident - (DdotN * norm));
    vec3 refrDir = glm::normalize( term2 - (term1 * norm) );
    result.setDir(refrDir);
    result.setTMIN(0.00001);
    result.setTMAX(8888);
    result.setIndex(ind2);
    return true;
  } else {
    result.setDir(incident);
    result.setTMIN(0.00001);
    result.setTMAX(8888);
    result.setIndex(ind2);
    return true;
  }
}

void RayTracer::trace(Ray r, int lvl, Color& outputColor)
{
  Color black = Color(0.0, 0.0, 0.0);

  if(lvl == 0){
    outputColor.setColors(0, 0, 0);
    return;
  }

  Intersect intersect = closestShape(r);

  if(intersect.isHit()){

    vec3 norm = glm::normalize(intersect.getNormal().getDir());
    vec3 incident = glm::normalize(r.getDir());
    //vec3 reflectedDir = 2*glm::dot(norm, glm::normalize(r.getDir())) * norm;
    //reflectedDir = glm::normalize(r.getDir() - reflectedDir);

    vec3 reflectedDir = glm::normalize(glm::reflect(incident, norm));

    Shape *currShape = intersect.getShape();
    if (_lights->empty()) {
      outputColor.setColors(currShape->getAmbient());
      return;
    }

    vec3 result = vec3(0.0, 0.0, 0.0);
    vec3 contribution = vec3(0.0, 0.0, 0.0);

    Ray *lightray = new Ray();
    for (vector<Light *>::iterator lightIter = _lights->begin();
         lightIter != _lights->end(); lightIter++) {
      Light *currLight = *lightIter;
      currLight->generateLightRay(intersect, lightray);
      if (!blockedByObject(lightray, currShape)) {
        currShape->intersectColor(intersect, currLight, cam, contribution);
        result += contribution;
      }
      //return intersect.getShape()->intersectColor(intersect);
    }

    delete lightray;

    result += currShape->getEmission().getColors() + currShape->getAmbient().getColors();

    Ray reflect = Ray();
    vec3 offsetInters = intersect.getPosition().getPoint() + 0.001f * reflectedDir;
    reflect.setPoint(Point(offsetInters));
    reflect.setDir(Direction(reflectedDir));
    Color reflectedCol = Color(0, 0, 0);
    trace(reflect, lvl - 1, reflectedCol);


    // REFRACTION STUFF STARTS HERE

    Color refractedCol = Color(0, 0, 0);
    if (currShape->getIndex() != 0.0) {
      vec3 normal = norm;
      Ray refractRay = Ray();
      float index1 = r.getIndex();
      float index2 = currShape->getIndex();
      if (index1 != 1.0) {
	index2 = 1.0;
	normal = -normal;
      }
      if (refract(normal, incident, index1, index2, refractRay)) {
	refractRay.setPoint
	  ( Point( intersect.getPosition().getPoint() + 0.001f * refractRay.getDir() ) );
	trace(refractRay, lvl - 1, refractedCol);
	float s = glm::length(intersect.getPosition().getPoint() - r.getPos());
	float beer = exp( - log(1.1) * s);\
	refractedCol *= beer;
      }
    }


    /////////////////////////
    

    result += (currShape->getSpecular().getColors() * reflectedCol.getColors());
    result += refractedCol.getColors();

    //cout << "result stuff: " << result.x << " " << result.y << " " << result.z << endl;

    if (result[0] > 1.0) result[0] = 1.0;
    if (result[1] > 1.0) result[1] = 1.0;
    if (result[2] > 1.0) result[2] = 1.0;
    Color finalColor = Color(result.x, result.y, result.z);
    outputColor.setColors(finalColor);

    return;

  }

//cout << "magic6" << endl;
  outputColor.setColors(black);
}

Intersect RayTracer::closestShape(Ray r){

  vector<Shape *>::iterator itStart = _shapes->begin();
  vector<Shape *>::iterator itEnd = _shapes->end();
  
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
