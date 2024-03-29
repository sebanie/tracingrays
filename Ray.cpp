#include "Ray.h"

Ray::Ray(void)
{
  _pt = Point(0, 0, 0);
  _dir = Direction(0, 0, 0);
  _tMin = 0;
  _tMax = 9999;
  _index = 1.0;
}

Ray::Ray(Point pt, Direction dir, float tMin, float tMax)
{ 
  _pt = pt;
  _dir = dir;
  _tMin = tMin;
  _tMax = tMax;
  _index = 1.0;
}

Ray::Ray(Point pt, Direction dir, float tMin, float tMax, float index)
{ 
  _pt = pt;
  _dir = dir;
  _tMin = tMin;
  _tMax = tMax;
  _index = index;
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


void Ray::setDist(float dist)
{
  _dist = dist;
}


void Ray::setIndex(float ind)
{
  _index = ind;
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

float Ray::getDist(void)
{
  return _dist;
}

float Ray::getIndex(void)
{
  return _index;
}

Ray Ray::transform(mat4 matrix)
{
  vec4 transfPos = matrix * vec4(getPos(), 1.0);
  vec4 transfDir = matrix * vec4(getDir(), 0.0);
  return Ray(Point(vec3(transfPos.x, transfPos.y, transfPos.z) / transfPos.w), Direction(glm::normalize(vec3(transfDir))), _tMin, _tMax);
}
