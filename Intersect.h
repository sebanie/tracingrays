#if !defined(INTERSECT_H)
#define INTERSECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include "Point.h"

using namespace std;
typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ;
typedef glm::vec2 vec2 ;


class Intersect{
 private:
  Point position;
  Direction normal;
  Shape *shape;
  bool hit;
 public:
  Intersect(){
    position = Point(0.0, 0.0, 0.0);
    normal = Direction(0.0, 0.0, 0.0);
    *shape = NULL;
    hit = false;
  }
  Intersect(Point pos, Direction norm, Shape *s){
    position = pos;
    normal = norm;
    *shape = *s;
    hit = true;
  }
  Point position(){
    return position;
  }
  Direction normal(){
    return normal;
  }
  Shape* shape(){
    return shape;
  }
  bool isHit(){
    return hit;
  }
};

#endif
