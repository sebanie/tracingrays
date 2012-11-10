#if !defined(SCENE_H)
#define SCENE_H

#include <vector>
#include "Film.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ;
typedef glm::vec2 vec2 ;
// To account for C++ namespace issues
#define vector std::vector  
//typedef vector<Point> Pvector;


class Scene  
{
 private:
  vector<Surface> surfaces;
  int width, height;
  float fovx, fovy;
  vec3 cameraPos, lookAt, upVector;
  string outputFile;
  Camera *camera;
  Film *film;
  int maxDepth;
 public:
  Scene();
  void init()
  int width(){
    return width;
  }
  int height(){
    return height;
  }
  float fovx(){
    return fovx;
  }
  float fovy(){
    return fovy;
  }
  vec3 cameraPos(){
    return cameraPos;
  }
  vec3 lookat(){
    return lookAt;
  }
  vec3 upVector(){
    return upVector;
  }
  int maxDepth(){
    return maxDepth;
  }
  virtual ~Scene();
  virtual void draw(int levelOfDetail);
};

#endif

