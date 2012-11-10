#if !defined(SHAPE_H)
#define SHAPE_H

#include <vector>
#include "Intersect.h"
#include "Color.h"

using namespace std;

class Shape{
  Color bgColor = Color(0.0,1.0,0.0);
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
  Color diffuse(){
    return diffuse;
  }
  Color specular(){
    return specular;
  }
  Color emission(){
    return emission;
  }
  float shininess(){
  }
  virtual Intersect intersect(Ray r){
    return Intersect();
  }
  Color intersectColor(Intersect intersection){
    Color result;
    if(!intersection.isHit()){
      return bgColor;
    }
    //vec3 viewDirec = scene->cameraPos() - intersection.position().normalize();
    result = diffuse;
    return result;
};

#endif
