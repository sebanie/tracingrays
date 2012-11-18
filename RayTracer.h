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
 public:
  RayTracer(void);
	Color trace(Ray r, int lvl);
	Intersect closestShape(Ray r);
  ~RayTracer(void);
};


#endif

