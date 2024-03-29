#if !defined(TRINORMAL_H)
#define TRINORMAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Shape.h"
#include <stdio.h>

class TriNormal : public Shape{
 protected:
  Point v1, v2, v3;
	Direction d1, d2, d3;
 public:
  TriNormal(Point vert1,  Point vert2, Point vert3, Direction vn1, Direction vn2, Direction vn3, Color a, Color d, Color s, Color e, float shine){
    v1 = vert1;
    v2 = vert2;
    v3 = vert3;
		d1 = vn1;
		d2 = vn2;
		d3 = vn3;
    setMaterialProperties(a, d, s, e, shine);
    setBoundingBox();
  }

  TriNormal() {}

  Intersect intersect(Ray r){

    vec3 a = v1.getPoint();
    vec3 b = v2.getPoint();
    vec3 c = v3.getPoint();
		vec3 a_n = d1.getDir();
		vec3 b_n = d2.getDir();
		vec3 c_n = d3.getDir();


    vec3 normal = glm::normalize(glm::cross((b - a), (c - a)));
    float t = glm::dot((a - r.getPos()), normal) / glm::dot(r.getDir(), normal);
    if(t < 0.0){
      return Intersect();
    }

    vec3 intersectPoint = r.getPos() + t*r.getDir();
   
    if ( (glm::dot(glm::cross(b - a, intersectPoint - a), normal) >= 0.0) &&
	 (glm::dot(glm::cross(c - b, intersectPoint - b), normal) >= 0.0) &&
	 (glm::dot(glm::cross(a - c, intersectPoint - c), normal) >= 0.0) ) {
			vec3 n_a = glm::normalize(glm::cross((c-b), (intersectPoint - b)));
			vec3 n_b = glm::normalize(glm::cross((a-c), (intersectPoint - c)));
			vec3 n_c = glm::normalize(glm::cross((b-a), (intersectPoint - a)));
			float alpha = glm::dot(normal, n_a)/glm::dot(normal, normal);
			float beta = glm::dot(normal, n_b)/glm::dot(normal, normal);
			float gamma = glm::dot(normal, n_c)/glm::dot(normal, normal);
			vec3 intersectNormal = vec3(alpha*a_n + beta*b_n + gamma*c_n);
      return Intersect(Point(intersectPoint), Direction(intersectNormal), (Shape *)this, t);
    } else {

      return Intersect();
    }
  }
  void setBoundingBox() {
    vec3 minCoord, maxCoord;
    for (int i = 0; i < 3; i++){
      minCoord[i] = std::min(v1.getPoint()[i], std::min(v2.getPoint()[i], v3.getPoint()[i]));
      maxCoord[i] = std::max(v1.getPoint()[i], std::max(v2.getPoint()[i], v3.getPoint()[i]));
    }
    boundingBox = Box(minCoord, maxCoord);
  }

};

#endif
