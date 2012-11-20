#include "PointLight.h"



vec3 PointLight::getPosition()
{
	return _position.getPoint();
}

vec3 PointLight::getDirection(Point pt)
{
	return glm::normalize(_position.getPoint() - pt.getPoint());
}

void PointLight::generateLightRay(Intersect &inters, Ray *ray)
{
	vec3 rayDir = glm::normalize(getPosition() - inters.getPosition().getPoint());
	ray->setDir(Direction(rayDir));

	vec3 lraypt = inters.getPosition().getPoint() + (0.0001f * rayDir);
	ray->setPoint(Point(lraypt));

	ray->setTMIN(0.000001);
	ray->setTMAX(10000000);

}
