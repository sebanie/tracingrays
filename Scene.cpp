#include "Scene.h"
#include <stdio.h>
using namespace std;

Scene::Scene(){
  width = 640;
  height = 480;
  maxDepth = 5;
  fovy = 30.0;
  Point pt0 = Point(-1.0, -1.0, 0.0);
  Point pt1 = Point(1.0, -1.0, 0.0);
  Point pt2 = Point(1.0, 1.0, 0.0);
  Point pt3 = Point(-1.0, +1.0, 0);
  Color red = Color(1.0, 0.0, 0.0);
  Color black = Color(0.0, 0.0, 0.0);
  shapes.push_back(new Triangle(pt0, pt2, pt3, red, black, black, 1.0));
  shapes.push_back(new Triangle(pt0, pt1, pt2, red, black, black, 1.0));
  outputFile = "out.png";
  camera = new Camera(vec3(-4.0, -0.0, 1.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), 45.0, height, width);
  film = new Film(); 
}

void Scene::render(){
  Sampler sampler= Sampler(width, height);
  Sample curSample = Sample(0.0, 0.0);
  cout << "current" << sampler.currPixel << endl;
  cout << "total" << sampler.numPixels << endl;
  Ray r;
  int i = 0;
  while(sampler.getSample(&curSample)) {
    camera->generateRay(curSample, &r);
    Intersect i1 = shapes[0]->intersect(r);
    Intersect i2 = shapes[1]->intersect(r);
    if (i1.getT() < i2.getT()) {
      film->put(curSample, shapes[0]->intersectColor(i1));
      //cout << shapes[0]->intersectColor(i1).getR() << shapes[0]->intersectColor(i1).getG() << shapes[0]->intersectColor(i1).getB() << endl;
    }
    else{
      film->put(curSample, shapes[1]->intersectColor(i2));
      //cout << shapes[1]->intersectColor(i2).getR() << shapes[1]->intersectColor(i2).getG() << shapes[1]->intersectColor(i2).getB() << endl;
    }
    i++;
  }
  film->output("test.png");
}

Scene::~Scene(void)
{

}

