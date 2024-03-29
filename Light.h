#if !defined(LIGHT_H)
#define LIGHT_H

#include "Color.h"
#include "Intersect.h"
#include "Ray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light{
	protected:
		Color lightColor;
		vec3 attenuation;
	public:
		Light() { lightColor = Color(0, 0, 0); }
		Color getColor() {
			return lightColor;
		}
            void setAttenuation(vec3 atten) {
			attenuation = atten;
		}
            vec3 getAttenuation() {
			return attenuation;
		}
                virtual vec3 getPosition(void) = 0;

		virtual vec3 getDirection(Point) = 0;
		virtual void generateLightRay(Intersect &inters, Ray *ray) = 0;
};

#endif


