#include "Direction.h"

Direction::Direction(void)
{

}

Direction::Direction(vec3 dir) {
  mydir = dir;
}

vec4 Direction::getDir(void) {
  return mydir;
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

Direction* Direction::mult(float t) {
  return new Direction(t * mydir);
}

Direction::~Direction(void) {

}
