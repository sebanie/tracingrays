#include "DirLight.h"

DirLight::DirLight(Color color, Direction dir) {
	_dir = dir;
	lightColor = color;
}

vec3 DirLight::getDirection(Point ignored) {
	return _dir.getDir();
}

void DirLight::generateLightRay(Intersect &inters, Ray *ray)
{
	vec3 rayDir = glm::normalize(getDirection(Point()));
	ray->setDir(Direction(rayDir));

	vec3 lraypt = inters.getPosition().getPoint() + (0.0001f * rayDir);
	ray->setPoint(Point(lraypt));

	ray->setTMIN(0.000001);
	ray->setTMAX(10000000);

}
