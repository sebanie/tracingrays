#if !defined(RAY_H)
#define RAY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Point.h"
#include "Direction.h"

typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 


class Ray
{
 private:
  Point _pt;
  Direction _dir;
  float _tMin, _tMax, _dist, _index;
  
 public:
  Ray(void);
  Ray(Point pt, Direction dir, float tMin, float tMax);
  Ray(Point pt, Direction dir, float tMin, float tMax, float index);
  void setPoint(Point pt);
  void setDir(Direction dir);
  void setTMIN(float tmin);
  void setTMAX(float tmax);
  void setDist(float dist);
  void setIndex(float ind);
  vec3 getPos(void);
  vec3 getDir(void);
  float getTMIN(void);
  float getTMAX(void);
  float getDist(void);
  float getIndex(void);
  Ray transform(mat4 matrix);
  virtual ~Ray(void);
};


#endif

