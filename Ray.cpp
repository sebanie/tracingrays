#include "Ray.h"

Ray::Ray(void)
{

}

Ray::Ray(Point pt, Direction dir, float tMin, float tMax)
{
  _pt = pt;
  _dir = dir;
  _tMin = tMin;
  _tMax = tMax;
}

Ray::~Ray(void)
{

}

void Ray::setPoint(Point pt)
{
  _pt = pt;
}

void Ray::setDir(Direction dir)
{
  _dir = dir;
}

void Ray::setTMIN(float tmin)
{
  _tMin = tmin;
}

void Ray::setTMAX(float tmax)
{
  _tMax = tmax;
}

vec3 Ray::getPos(void)
{
  return _pt.getPoint();
}

vec3 Ray::getDir(void)
{
  return _dir.getDir();
}

float Ray::getTMIN(void)
{
  return _tMin;
}

float Ray::getTMAX(void)
{
  return _tMax;
}
