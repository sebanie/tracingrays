#if !defined(SHAPE_H)
#define SHAPE_H

class Intersect;
#include <vector>
#include <stdio.h>
#include "Intersect.h"
#include "Color.h"
#include "Ray.h"

using namespace std;

class Shape{
  Color bgColor;
  bool blockedByObject(Ray *r);
 protected:
  Color diffuse, specular, emission;
  float shininess;
  
  void setMaterialProperties(Color d, Color s, Color e, float shine){
    diffuse = d;
    specular = s;
    emission = e;
    shininess = shine;
  }
 public:
  Shape(){bgColor = Color(0.0, 1.0, 0.0);}
  Color getDiffuse(){
    return diffuse;
  }
  Color getSpecular(){
    return specular;
  }
  Color getEmission(){
    return emission;
  }
  float getShininess(){
    return shininess;
  }
  virtual Intersect intersect(Ray r) = 0;
  Color intersectColor(Intersect intersection);
};

#endif
