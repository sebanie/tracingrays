#if !defined(INTERSECT_H)
#define INTERSECT_H

class Shape;
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include "Point.h"
#include "Shape.h"
#include "Direction.h"

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
  Shape* shape;
  bool hit;
  float t;
 public:
  Intersect(){
    position = Point(0.0, 0.0, 0.0);
    normal = Direction(0.0, 0.0, 0.0);
    shape = NULL;
    hit = false;
    t = 99999.9;
  }
  Intersect(Point pos, Direction norm, Shape *s, float tVal){
    position = pos;
    normal = norm;
    t = tVal;
    shape = s;
    hit = true;
  }
  Point getPosition(){
    return position;
  }
  Direction getNormal(){
    return normal;
  }
  float getT(){
    return t;
  }
  Shape* getShape(){
    return shape;
  }
  bool isHit(){
    return hit;
  }
};

#endif

