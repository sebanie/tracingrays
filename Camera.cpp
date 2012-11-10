#include "Camera.h"
#include "Point.h"

void Camera::generateRay(Sample &sample, Ray* ray)
{
  vec3 w = glm::normalize(_lookfrom - _lookat);
  vec3 u = glm::normalize(glm::cross(_up, w));
  vec3 v = glm::cross(w, u);

  float j = (float) sample.x();
  float i = (float) sample.y();

  float halfwidth = ((float) _width) / 2.0;
  float halfheight = ((float) _height) / 2.0;
  
  float alpha = (tan(_fovx / 2)) * ((j - halfwidth) / halfwidth);
  float beta = (tan(_fovy / 2)) * ((halfheight - i) / halfheight);

  vec3 direction = glm::normalize((alpha * u) + (beta * v) - w);

  Point eye = Point(_lookfrom.x, _lookfrom.y, _lookfrom.z);
  Direction dir = Direction(direction);

  ray->setPoint(eye);
  ray->setDir(dir);
  ray->setTMIN(0.0001);
  ray->setTMAX(10000);
  
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
}

Camera::Camera(void)
{

}

Camera::~Camera(void)
{

}
