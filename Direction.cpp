#include "Direction.h"

Direction::Direction(void)
{

}


Direction::Direction(float x, float y, float z) {
  mydir = vec3(x, y, z);
}

Direction::Direction(vec3 dir) {
  mydir = dir;
}

vec3 Direction::getDir(void) {
  return mydir;
}

void Direction::setDir(vec3 dir) {
  mydir = dir;
}

float Direction::x(void) {
  return mydir.x;
}

float Direction::y(void) {
  return mydir.y;
}

float Direction::z(void) {
  return mydir.z;
}

void Direction::mult(float t, Direction &result) {
  result.setDir(t * mydir);
}

Direction::~Direction(void) {

}
