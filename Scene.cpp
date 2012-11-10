#include "Scene.h"
using namespace std;

Scene::Scene(){
  width = 640;
  height = 480;
  maxDepth = 5;
  fovy = 30.0;
  Point pt0 = Point(-1.0, -1.0, 0);
  Point pt1 = Point(1.0, -1.0, 0);
  Point pt2 = Point(1.0, 1.0, 0);
  Point pt3 = Point(-1.0, +1.0, 0);
  Color red = Color(1.0,0.0,0.0);
  Color black = Color(0.0,0.0,0.0);
  shapes.push_back(new Triangle(pt0, pt1, pt2, red, black, black, 1.0));
  shapes.push_back(new Triangle(pt0, pt2, pt3, red, black, black, 1.0));
  outputFile = "out.png";
  camera = new Camera(vec3(-4.0, -4.0, -4.0), vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), 30.0, height, width);
  film = new Film(); 
}

void Scene::render(){
  Sampler sampler= Sampler(width, height);
  Sample curSample = Sample(0.0, 0.0);
  Ray r;
  while(!sampler.getSample(&curSample)) {
    camera.generateRay(curSample, &r);
    Intersect i1 = shapes[0]->intersect(r);
    Intersect i2 = shapes[1]->intersect(r);
    if (i1.getT() <= i2.getT()) {
      film.put(curSample, shapes[0]->intersectColor(i1));
    }
    else{
      film.put(curSample, shapes[1]->intersectColor(i2));
    }
  }
  film.output("test.png");
}

