#if !defined(SCENE_H)
#define SCENE_H

class RayTracer;
#include <vector>
#include "Film.h"
#include "Color.h"
#include "Camera.h"
#include "Sample.h"
#include "Sampler.h"
#include "Point.h"
#include "Light.h"
#include "PointLight.h"
#include "DirLight.h"
#include "Shape.h"
#include "Triangle.h"
#include "Sphere.h"
#include "TriNormal.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Intersect.h"
#include "Direction.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ;
typedef glm::vec2 vec2 ;
typedef glm::mat4 mat4 ;
// To account for C++ namespace issues
#define vector std::vector  


class Scene  
{
 private:
  vector<Shape *>* shapes;
  vector<Light *>* lights;
  int width, height;
  float fovx, fovy;
  vec3 cameraPos, lookAt, upVector;
  string outputFile;
  Camera *camera;
  Film *film;
  int maxDepth;
  RayTracer *rt;

  vec3 ambient,
       emission,
       diffuse,
       specular,
       attenuation;
  float shine;
  float aperture, halfap, focalLength;

 public:
  Scene();
  void parse(const char * filename);
  void init();
  int getWidth(){
    return width;
  }
  int getHeight(){
    return height;
  }
  float getFovx(){
    return fovx;
  }
  float getFovy(){
    return fovy;
  }
  vec3 getCameraPos(){
    return cameraPos;
  }
  vec3 getLookat(){
    return lookAt;
  }
  vec3 getUpVector(){
    return upVector;
  }
  int getMaxDepth(){
    return maxDepth;
  }
  vector<Shape *>* getShapes(){
    return shapes;
  }
  vector<Light *>* getLights(){
    return lights;
  }
  void render();
  ~Scene();
};
extern Scene scene;

#endif
