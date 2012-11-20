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
  Sphere(Point c, float r, Color d, Color s, Color e, float shine, mat4 transf){
    center = c;
    radius = r;
    setMaterialProperties(d, s, e, shine);
    matrix = transf;
    inverse = glm::inverse(transf);
    //std::cout << inverse[2][2] << std::endl;
  }
  Sphere(){}
  Intersect intersect(Ray r){

    Ray transfRay = r.transform(inverse);

    vec3 centerPoint = center.getPoint();
    //float a = glm::dot(r.getDir(), r.getDir());
    //float b = glm::dot(r.getDir()*vec3(2), (r.getPos()-centerPoint));
    //float c = glm::dot((r.getPos()-centerPoint),(r.getPos()-centerPoint)) - pow(radius,2.0);


    float a = glm::dot(transfRay.getDir(), transfRay.getDir());
    float b = glm::dot(transfRay.getDir()*vec3(2), (transfRay.getPos()-centerPoint));
    float c = glm::dot((transfRay.getPos()-centerPoint),(transfRay.getPos()-centerPoint)) - pow(radius,2.0);

    //vec3 normal = glm::cross((b - a), (c - a));
    //vec3 normal = centerPoint;
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
      //std::cout << "whaddu[" << std::endl;
      return Intersect();
    }

    vec3 intersectPoint = transfRay.getPos() + t*transfRay.getDir();

    vec3 normal = glm::normalize(intersectPoint - centerPoint);

    //std::cout << "norm " << normal.x << normal.y << normal.z << std::endl;

    normal = glm::normalize(vec3(glm::transpose(inverse) * vec4(normal, 0.0)));

    //std::cout << "norm " << normal.x << normal.y << normal.z << std::endl << std::endl;


    intersectPoint = vec3(matrix * vec4(intersectPoint, 1.0));
    
   
    // if INTERSECTPOINT is within triangle, then these cross products should
    // return vectors that face the same direction as NORMAL
    return Intersect(Point(intersectPoint), Direction(normal), (Shape *)this, t);
  }

  vec3 calculateNormal(vec3 pt) {
    vec3 normal = vec3(glm::transpose(inverse) * (vec4(pt, 1.0) - vec4(center.getPoint(), 1.0)));
    //normal = vec3(glm::transpose(inverse) * vec4(normal, 0.0));
    return glm::normalize(normal);
  }

};

#endif
