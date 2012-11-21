#include "Direction.h"

Direction::Direction(void)
{
  mydir = vec3(0.0);
}


Direction::Direction(float x, float y, float z) {
  mydir = vec3(x, y, z);
}

Direction::Direction(vec3 dir) {
  mydir = vec3(dir.x, dir.y, dir.z);
}

vec3 Direction::getDir(void) {
  return mydir;
}

void Direction::setDir(vec3 dir) {
  mydir.x = dir.x;
  mydir.y = dir.y;
  mydir.z = dir.z;
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

void Direction::normalize(void) {
  mydir = glm::normalize(mydir);
}

Direction::~Direction(void) {

}
