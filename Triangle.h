#if !defined(TRIANGLE_H)
#define TRIANGLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Shape.h"
#include <stdio.h>

class Triangle : public Shape{
 protected:
  Point v1, v2, v3;
 public:
  Triangle(Point vert1, Point vert2, Point vert3, Color a, Color d, Color s, Color e, float shine, float ind){
    v1 = vert1;
    v2 = vert2;
    v3 = vert3;
    setMaterialProperties(a, d, s, e, shine);
    index = ind;
    setBoundingBox();
  }

  Triangle() {}

  Intersect intersect(Ray r){
  //cout << "meme, it was a triangle!" << endl;

    vec3 a = v1.getPoint();
    vec3 b = v2.getPoint();
    vec3 c = v3.getPoint();

    vec3 normal = glm::normalize(glm::cross((b - a), (c - a)));
    float t = glm::dot((a - r.getPos()), normal) / glm::dot(r.getDir(), normal);
    if(t < 0.0){
      //std::cout << "hey booiiiii" << std::endl;
      return Intersect();
    }

    vec3 intersectPoint = r.getPos() + t*r.getDir();
   
    // if INTERSECTPOINT is within triangle, then these cross products should
    // return vectors that face the same direction as NORMAL
    if ( (glm::dot(glm::cross(b - a, intersectPoint - a), normal) >= 0.0) &&
	 (glm::dot(glm::cross(c - b, intersectPoint - b), normal) >= 0.0) &&
	 (glm::dot(glm::cross(a - c, intersectPoint - c), normal) >= 0.0) ) {

    //cout << "tri tri world intersect: " << intersectPoint.x << intersectPoint.y << intersectPoint.z << endl;
//cout << "allo" << endl;
      return Intersect(Point(intersectPoint), Direction(normal), (Shape *)this, t);
    } else {
      //std::cout << "bam" << std::endl;
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
    //std::cout << "Triangle Bounding Box Mins: " << "x -- " << boundingBox.getMin().x << "y -- " << boundingBox.getMin().y << "z -- " << boundingBox.getMin().z << std::endl;
    //std::cout << "Triangle Bounding Box Maxs: " << "x -- " << boundingBox.getMax().x << "y -- " << boundingBox.getMax().y << "z -- " << boundingBox.getMax().z << std::endl;

  }
};

#endif
