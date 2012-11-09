#include "Point.h"

Point::Point(void)
{
  mypoint = vec3(0, 0, 0);
}

Point::Point(float x, float y, float z) {
  mypoint = vec3(x, y, z);
}

vec3 Point::getPoint(void) {
  return mypoint;
}

float Point::x(void) {
  return mypoint.x;
}

float Point::y(void) {
  return mypoint.y;
}

float Point::z(void) {
  return mypoint.z;
}

Point* Point::mult(Direction* dir) {
  float newx = x() + dir->x();
  float newy = y() + dir->y();
  float newz = z() + dir->z();
  return new Direction(newx, newy, newz);
}

Point::~Point() {

}
