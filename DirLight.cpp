#include "DirLight.h"

DirLight::DirLight(Color color, Direction dir) {
        dir.normalize();
	_dir = dir;
	lightColor = color;
        attenuation = vec3(1.0, 0, 0);
}

vec3 DirLight::getPosition(void)
{
  return vec3(0, 0, 0);
}

vec3 DirLight::getDirection(Point ignored) {
	return _dir.getDir();
}

void DirLight::generateLightRay(Intersect &inters, Ray *ray)
{
	Direction rayDir = Direction(glm::normalize(-1 * _dir.getDir()));
	ray->setDir(rayDir);

	vec3 lraypt = inters.getPosition().getPoint() + (0.001f * rayDir.getDir());
	ray->setPoint(Point(lraypt));

	ray->setTMIN(0.000000);
	ray->setTMAX(10000000);

}
