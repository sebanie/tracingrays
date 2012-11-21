#if !defined(RAYTRACER_H)
#define RAYTRACER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#include "Scene.h"
#include "Intersect.h"
#include "Color.h"

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 


class RayTracer{
  vector<Shape *>* _shapes;
  vector<Light *>* _lights;
  vec3 cam;
  bool blockedByObject(Ray *r, Shape* shape);
 public:
  RayTracer(vector<Shape *>* shapes, vector<Light *>* lights, vec3 camPosn);
	void trace(Ray r, int lvl, Color &color);
	Intersect closestShape(Ray r);
  ~RayTracer(void);
};


#endif

