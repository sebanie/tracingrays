#if !defined(SPHERE_H)
#define SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Shape.h"

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 


class Sphere : public Shape{
 protected:
  Point center;
  float radius;
  mat4 matrix, inverse;
 public:
  Sphere(Point c, float r, Color a, Color d, Color s, Color e, float shine, mat4 transf, float ind){
    center = c;
    radius = r;
    setMaterialProperties(a, d, s, e, shine);
    matrix = transf;
    inverse = glm::inverse(transf);
    index = ind;
    setBoundingBox();
  }

  Sphere(){}

  Intersect intersect(Ray r){

    Ray transfRay = r.transform(inverse);

    vec3 centerPoint = center.getPoint();

    float a = glm::dot(transfRay.getDir(), transfRay.getDir());
    float b = glm::dot(transfRay.getDir()*vec3(2), (transfRay.getPos()-centerPoint));
    float c = glm::dot((transfRay.getPos()-centerPoint),(transfRay.getPos()-centerPoint)) - pow(radius,2.0);

    float discriminant = pow(b,2.0) - 4.0 * a * c;
    if (discriminant < 0.0){
      return Intersect();
    }
    float t;
    float t1= (-b + sqrt(discriminant))/2*a;
    float t2= (-b - sqrt(discriminant))/2*a;
    if(t1 > 0.0 && t2 > 0.0){
      if(t1 <= t2){
      	t = t1;
      }
      else{
      	t = t2;
      }
    }
    else if (t1 > 0.0){
      t = t1;
    }
    else if (t2 > 0.0){
      t = t2;
    }
    else{
      return Intersect();
    }

    vec3 intersectPoint = transfRay.getPos() + t*transfRay.getDir();

    vec3 normal = glm::normalize(intersectPoint - centerPoint);

    normal = glm::normalize(vec3(glm::transpose(inverse) * vec4(normal, 0.0)));

    intersectPoint = vec3(matrix * vec4(intersectPoint, 1.0));

    float worldt = (intersectPoint - r.getPos()).x / r.getDir().x;
    
  
    return Intersect(Point(intersectPoint), Direction(normal), (Shape *)this, worldt);
  }

  vec3 calculateNormal(vec3 pt) {
    vec3 normal = vec3(glm::transpose(inverse) * (vec4(pt, 1.0) - vec4(center.getPoint(), 1.0)));
    return glm::normalize(normal);
  }
  
  void setBoundingBox() {
    vec4 bounds[8];
    vec3 sphereCenter = center.getPoint();
    bounds[0] = matrix * vec4((sphereCenter + vec3(radius, radius, radius)), 1);
    bounds[1] = matrix * vec4((sphereCenter + vec3(radius, radius, -radius)), 1);
    bounds[2] = matrix * vec4((sphereCenter + vec3(radius, -radius, radius)), 1);
    bounds[3] = matrix * vec4((sphereCenter + vec3(radius, -radius, -radius)), 1);
    bounds[4] = matrix * vec4((sphereCenter + vec3(-radius, radius, radius)), 1);
    bounds[5] = matrix * vec4((sphereCenter + vec3(-radius, radius, -radius)), 1);
    bounds[6] = matrix * vec4((sphereCenter + vec3(-radius, -radius, radius)), 1);
    bounds[7] = matrix * vec4((sphereCenter + vec3(-radius, -radius, -radius)), 1);
    vec3 minCoord, maxCoord;
    minCoord = vec3(bounds[0]);
    maxCoord = vec3(bounds[0]);
    for (int i = 0; i < 3; i++){
      for (int j = 1; j < 8; j++){
      	minCoord[i] = min(minCoord[i], bounds[j][i]);
      	maxCoord[i] = max(maxCoord[i], bounds[j][i]);
      }
    }
    boundingBox = Box(minCoord, maxCoord);
  }
    

};

#endif
