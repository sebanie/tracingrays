#if !defined(LIGHT_H)
#define LIGHT_H

#include "Color.h"
#include "Intersect.h"
#include "Ray.h"

class Light{
	protected:
		Color lightColor;
	public:
		Light() { lightColor = Color(0, 0, 0); }
		Color getColor() {
			return lightColor;
		}
		virtual vec3 getDirection(Point) = 0;// { return vec3(0, 0, 0); }
		void generateLightRay(Intersect &inters, Ray *ray) {}
};

#endif


