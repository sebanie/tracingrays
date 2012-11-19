#if !defined(DIRLIGHT_H)
#define DIRLIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Light.h"

class DirLight : public Light {
	protected:
		Direction _dir;
	public:
		DirLight(Color color, Direction dir);
		virtual vec3 getDirection(Point ignored);
		void generateLightRay(Intersect &inters, Ray *ray);
};

#endif

