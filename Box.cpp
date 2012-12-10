#include "Box.h"

Box::Box(vec3 minCoords, vec3 maxCoords) {
  for (int i = 0; i < 3; i++){
    _min[i] = std::min(minCoords[i], maxCoords[i]);
    _max[i] = std::max(minCoords[i], maxCoords[i]);
  }
}

bool Box::isHit(Ray r){
  vec3 t_min, t_max;
  double a;
  double minPos;
  double maxPos;
  for (int i = 0; i < 3; i ++){
    a = 1.0 / r.getDir()[i];
    minPos = a * (_min[i] - r.getPos()[i]);
    maxPos = a * (_max[i] - r.getPos()[i]);
    if ( a >= 0) {
      t_min[i] = minPos;
      t_max[i] = maxPos;  
    }
    else {
      t_min[i] = maxPos;
      t_max[i] = minPos;
    }
  }
  if ((t_min[0] > t_max[1]) || (t_max[0] < t_min[1]) ||
      (t_min[0] > t_max[2]) || (t_max[0] < t_min[2]) ||
      (t_min[1] > t_max[2]) || (t_max[1] < t_min[2])) {
    return false;
  }
  else {
    return true;
  }
}

Box Box::merge(Box sibling) {
  vec3 minCoord, maxCoord;
  for (int i = 0; i < 3; i ++){
    minCoord[i] = std::min((this->_min)[i], sibling.getMin()[i]);
    maxCoord[i] = std::max((this->_max)[i], sibling.getMax()[i]);
  }
  return Box(minCoord, maxCoord);
}

vec3 Box::center() {
  vec3 midpoint;
  for (int i = 0; i < 3; i++) {
    midpoint[i] = (_min[i] + _max[i]) / 2.0;
  }
  return midpoint;
}
