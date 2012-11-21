#if !defined(SHAPE_H)
#define SHAPE_H

class Intersect;
class Light;
#include <vector>
#include <stdio.h>
#include "Intersect.h"
#include "Color.h"
#include "Ray.h"

using namespace std;

class Shape{
  //bool blockedByObject(Ray *r);
 protected:
  Color diffuse, specular, emission, ambient;
  float shininess;
  
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
  virtual Intersect intersect(Ray r) = 0;
  void intersectColor(Intersect intersection, Light* currLight, vec3 camPosn, vec3 &result);
};

#endif
