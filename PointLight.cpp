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
        vec3 lightminuseye = getPosition() - inters.getPosition().getPoint();
	vec3 rayDir = glm::normalize(lightminuseye);
        Direction temp(rayDir);
	ray->setDir(temp);

	vec3 lraypt = inters.getPosition().getPoint() + (0.0001f * rayDir);
	ray->setPoint(Point(lraypt));

        float tmax = lightminuseye.x /rayDir.x;

	ray->setTMIN(0.000001);
	ray->setTMAX(tmax);

}
