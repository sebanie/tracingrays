#if !defined(TRIANGLE_H)
#define TRIANGLE_H

#include "Shape.h"

using namespace std;
typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ;
typedef glm::vec2 vec2 ;

class Triangle : public Shape{
 protected:
  Point v1, v2, v3;
 public:
  Triangle(Point vert1, Point vert2, Point vert3, Color d, Color s, Color e, float shine){
    v1 = vert1;
    v2 = vert2;
    v3 = vert3;
    setMaterialProperties(d, s, e, shine);
  }
  Triangle(){}
  Intersect intersect(Ray r){
    vec3 a = v1.getPoint();
    vec3 b = v2.getPoint();
    vec3 c = v3.getPoint();

    vec3 normal = glm::cross((b - a), (c - a));
    
    float t = glm::dot((a - r.getPos()), normal) / glm::dot(r.getDir(), normal);
    if(t < 0.0){
      return Intersect();
    }
    vec3 intersectPoint = r.getPos() + t*r.getDir();
   
    // if INTERSECTPOINT is within triangle, then these cross products should
    // return vectors that face the same direction as NORMAL
    if ( (glm::dot(glm::cross(b - a, intersectPoint - a), normal) >= 0.0) &&
	 (glm::dot(glm::cross(c - b, intersectPoint - b), normal) >= 0.0) &&
	 (glm::dot(glm::cross(a - c, intersectPoint - c), normal) >= 0.0) ) {
      return Intersect(intersectPoint, normal, this);
    } else {
      return Intersect();
    }
  }
};
#endif
