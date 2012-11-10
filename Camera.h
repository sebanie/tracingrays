#if !defined(CAMERA_H)
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Sample.h"
#include "Ray.h"

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 


class Camera
{
 private:
  vec3 _lookfrom;
  vec3 _lookat;
  vec3 _up;
  float _fovy, _fovx;
  int _height, _width;
  //mat4 cam2world, world2cam;
  
 public:
  Camera(void);
  Camera(vec3 lookfrom, vec3 lookat, vec3 up, float fovy, int height, int width);
  ~Camera(void);
  void generateRay(Sample &sample, Ray* ray);
  
};



#endif

