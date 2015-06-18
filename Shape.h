#if !defined(SHAPE_H)
#define SHAPE_H

class Intersect;
class Light;
#include <vector>
#include <stdio.h>
#include "Intersect.h"
#include "Color.h"
#include "Ray.h"
#include "Box.h"
#include <algorithm>

using namespace std;

class Shape{
 protected:
  Color diffuse, specular, emission, ambient;
  float shininess;
  float index;
  Box boundingBox;
  
  void setMaterialProperties(Color a, Color d, Color s, Color e, float shine){
    ambient = a;
    diffuse = d;
    specular = s;
    emission = e;
    shininess = shine;
  }
 public:
  Shape() {}
  Color getAmbient(){
    return ambient;
  }
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
  float getIndex(){
    return index;
  }
  Box getBoundingBox(){
    return boundingBox;
  }
  virtual Intersect intersect(Ray r) = 0;
  void intersectColor(Intersect intersection, Light* currLight, vec3 camPosn, vec3 &result);
};

#endif
