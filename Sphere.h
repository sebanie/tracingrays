#if !defined(SPHERE_H)
#define SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Shape.h"


class Sphere : public Shape{
 protected:
  Point center;
  float radius;
 public:
  Sphere(Point c, float r, Color d, Color s, Color e, float shine){
    center = c;
    radius = r;
    setMaterialProperties(d, s, e, shine);
  }
  Sphere(){}
  Intersect intersect(Ray r){
    vec3 centerPoint = center.getPoint();
    float a = glm::dot(r.getDir(), r.getDir());
    float b = glm::dot(r.getDir()*vec3(2), (r.getPos()-centerPoint));
    float c = glm::dot((r.getPos()-centerPoint),(r.getPos()-centerPoint)) - pow(radius,2.0);

    //vec3 normal = glm::cross((b - a), (c - a));
    vec3 normal = centerPoint;
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
    vec3 intersectPoint = r.getPos() + t*r.getDir();
    normal = glm::normalize(intersectPoint - centerPoint);
   
    // if INTERSECTPOINT is within triangle, then these cross products should
    // return vectors that face the same direction as NORMAL
    return Intersect(Point(intersectPoint), Direction(normal), (Shape *)this, t);
  }
};

#endif
