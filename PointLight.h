#if !defined(POINTLIGHT_H)
#define POINTLIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Light.h"

class PointLight : public Light {
	protected:
		Point _position;
	public:
		PointLight(Color color, Point position) {
			_position = position;
			lightColor = color;
		}
		vec3 getPosition();
		virtual vec3 getDirection(Point pt);
		void generateLightRay(Intersect &inters, Ray *ray);
};

#endif

