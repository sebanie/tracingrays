#if !defined(RAY_H)
#define RAY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 


class Ray
{
 private:
  Point _pt;
  Direction _dir;
  float _tMin, _tMax;
  
 public:
  Ray(void);
  Ray(Point pt, Direction dir, float tMin, float tMax);
  void setPoint(Point pt);
  void setDir(Direction dir);
  void setTMIN(float tmin);
  void setTMAX(float tmax);
  vec3 getPoint(void);
  vec3 getDir(void);
  float getTMIN(void);
  float getTMAX(void);
  virtual ~Ray(void);
};


#endif

