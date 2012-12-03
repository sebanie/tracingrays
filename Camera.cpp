#include "Camera.h"
#include "Point.h"
#include <iostream>

using namespace std;

void Camera::generateRay(Sample &sample, Ray* ray)
{
  float j = (float) sample.x();
  float i = ((float) _height) - ((float) sample.y());

  float alpha = (tan(_fovx / 2)) * ((j - halfwidth) / halfwidth);
  float beta = (tan(_fovy / 2)) * ((halfheight - i) / halfheight);

  vec3 direction = glm::normalize((alpha * u) + (beta * v) - w);
  float dist = glm::length((alpha * u) + (beta * v) - w);

  Point eye = Point(_lookfrom.x, _lookfrom.y, _lookfrom.z);
  Direction dir = Direction(direction);

  ray->setPoint(eye);
  ray->setDir(dir);
  ray->setTMIN(0.0001);
  ray->setTMAX(10000);
  ray->setDist(dist);
  
}

void Camera::generateDOFRay(Sample &sample, Ray* ray, vec3 focalpt)
{
  float j = (float) sample.x();
  float i = ((float) _height) - ((float) sample.y());

  float alpha = (tan(_fovx / 2)) * ((j - halfwidth) / halfwidth);
  float beta = (tan(_fovy / 2)) * ((halfheight - i) / halfheight);

  vec3 imagePlanePt = (alpha * u) + (beta * v) - w;

  vec3 startPt = _lookfrom + imagePlanePt;
  vec3 direction = glm::normalize(focalpt - startPt);

  ray->setPoint(Point(startPt));
  ray->setDir(Direction(direction));
  ray->setTMIN(0.0001);
  ray->setTMAX(10000);

}

vec3 Camera::findFocalPt(Ray &ray, float focal)
{
  float dist = ray.getDist();
  float focalhorz = 1.f + focal;
  
  float focalDist = dist * focalhorz;

  vec3 focalpt = ray.getPos() + (focalDist * ray.getDir());
  return focalpt;
}

Camera::Camera(vec3 lookfrom, vec3 lookat, vec3 up, float fovy, int height, int width)
{
  _lookfrom = lookfrom;
  _lookat = lookat;
  _up = up;
  _fovy = glm::radians(fovy);
  _height = height;
  _width = width;

  float z = (1 / tan(_fovy / 2.0)) * ((float) height / 2.0);
  //check for z==0
  _fovx = 2 * atan(((float) width / 2.0) / z);

  w = glm::normalize(_lookfrom - _lookat);
  u = glm::normalize(glm::cross(_up, w));
  v = glm::cross(w, u);

  halfwidth = ((float) _width) / 2.0;
  halfheight = ((float) _height) / 2.0;
}

vec3 Camera::getCameraPos(void)
{
  return _lookfrom;
}

Camera::Camera(void)
{

}

Camera::~Camera(void)
{

}
