#if !defined(BOX_H)
#define BOX_H

#include "Ray.h"
#include <algorithm>
typedef glm::vec3 vec3; 

class Box {
 private:
  vec3 _min, _max;
 
 public:
  Box() {}
  Box(vec3 minCoords, vec3 maxCoords);
  bool isHit(Ray r);
  Box merge(Box sibling);
  vec3 center();
  vec3 getMin(){
    return _min;
  }
  vec3 getMax(){
    return _max;
  }
};

#endif
