#include "Point.h"

Point::Point(void)
{

}

Point::Point(vec3 pos) {
  mypoint = vec3(pos.x, pos.y, pos.z);
}

Point::Point(float x, float y, float z) {
  mypoint = vec3(x, y, z);
}

vec3 Point::getPoint(void) {
  return mypoint;
}

void Point::setPoint(float x, float y, float z) {
  mypoint = vec3(x, y, z);
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

void Point::add(Direction* dir, Point &result) {
  float newx = x() + dir->x();
  float newy = y() + dir->y();
  float newz = z() + dir->z();
  result.setPoint(newx, newy, newz);
}

float Point::dist(Point* pt)
{
  return glm::distance(mypoint, pt->getPoint());
}

Point::~Point() {

}
