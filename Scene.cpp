#include "Scene.h"
#include <stdio.h>
using namespace std;

Scene::Scene(){
  width = 640;
  height = 480;
  maxDepth = 5;
  fovy = 30.0;
  rt = new RayTracer();
  shapes = new vector<Shape *>();
  lights = new vector<Light *>();

  mat4 spheretransf =
    mat4(1.0, 0.0, 0.0, 0.0,
         0.0, 1.5, 0.0, 0.0,
         0.0, 0.0, 1.5, 0.0,
         1.0, 0.0, 0.23, 1.0);

  Point sphereCent = Point(0.0, 0.5, 0.5);
  Point pt0 = Point(-1.0, -1.0, 0.0);
  Point pt1 = Point(1.0, -1.0, 0.0);
  Point pt2 = Point(1.0, 1.0, 0.0);
  Point pt3 = Point(-1.0, +1.0, 0);


  Point pt4 = Point(-1.0, -1.0, 2.0);
  Point pt5 = Point(1.0, -1.0, 2.0);
  Point pt6 = Point(1.0, 1.0, 2.0);
  Point pt7 = Point(-1.0, +1.0, 2.0);

  Color red = Color(1.0, 0.0, 0.0);
  Color blue = Color(0.0, 0.0, 1.0);
  Color green = Color(0.0, 0.5, 0.0);
  Color black = Color(0.0, 0.0, 0.0);
  shapes->push_back(new Triangle(pt0, pt2, pt3, Color(.1, .1, .1), Color(.3, .3, .3), black, 1.0));
  shapes->push_back(new Triangle(pt0, pt1, pt2, Color(.1, .1, .1), Color(.3, .3, .3), black, 1.0));


  //shapes->push_back(new Triangle(pt4, pt6, pt7, Color(.1, .1, .1), Color(.3, .3, .3), black, 1.0));
  //shapes->push_back(new Triangle(pt4, pt5, pt6, Color(.1, .1, .1), Color(.3, .3, .3), black, 1.0));

  shapes->push_back(new Sphere(sphereCent, 0.7, Color(.5, .5, .5), Color(.7, .7, .7), Color(.1, .1, .1), 20.0, spheretransf));
  lights->push_back(new PointLight(green, Point(0, -2.0, 1.0)));
  lights->push_back(new DirLight(green+blue, Direction(-.5, 3.0, 1.0)));
  lights->push_back(new DirLight(red, Direction(-1.0, 0.0, 1.0)));
  outputFile = "out.png";
  camera = new Camera(vec3(-4.0, -4.0, 4.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), 45.0, height, width);
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
		//cout << i << endl;
    camera->generateRay(curSample, &r);
		//cout << "shine: " << (*shapes)[0]->getShininess() << endl;
		Color outputColor = rt->trace(r, 1);
		film->put(curSample, outputColor);
    i++;
  }
  film->output("test.png");
}

Scene::~Scene(void)
{

}

