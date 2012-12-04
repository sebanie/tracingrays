#include "Scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <stdlib.h>
#include <time.h>
#include "Transform.h"

using namespace std;

Scene::Scene(){
  init();

/*
  width = 640;
  height = 480;
  maxDepth = 5;
  fovy = 30.0;
  rt = new RayTracer();
  shapes = new vector<Shape *>();
  lights = new vector<Light *>();

  mat4 spheretransf =
    mat4(1.0, 0.0, 0.0, 0.0,
         0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 1.0, 0.0,
         0.0, 0.0, 0.0, 1.0);

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
  shapes->push_back(new Triangle(pt0, pt2, pt3, black, Color(.1, .1, .1), Color(.3, .3, .3), black, 1.0));
  shapes->push_back(new Triangle(pt0, pt1, pt2, black, Color(.1, .1, .1), Color(.3, .3, .3), black, 1.0));


  //shapes->push_back(new Triangle(pt4, pt6, pt7, Color(.1, .1, .1), Color(.3, .3, .3), black, 1.0));
  //shapes->push_back(new Triangle(pt4, pt5, pt6, Color(.1, .1, .1), Color(.3, .3, .3), black, 1.0));

  shapes->push_back(new Sphere(sphereCent, 0.7, black, Color(.5, .5, .5), Color(.7, .7, .7), Color(.1, .1, .1), 20.0, spheretransf));
  lights->push_back(new PointLight(green, Point(0, -2.0, 1.0)));
  lights->push_back(new DirLight(green+blue, Direction(-.5, 3.0, 1.0)));
  lights->push_back(new DirLight(red, Direction(-1.0, 0.0, 1.0)));
  outputFile = "out.png";
  camera = new Camera(vec3(-4.0, -4.0, 4.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), 45.0, height, width);
  film = new Film();
*/
}

void Scene::init()
{

  shapes = new vector<Shape *>();
  lights = new vector<Light *>();
  maxDepth = 5;
  outputFile = "out.png";
  attenuation = vec3(1.0, 0.0, 0.0);
  ambient = vec3(0.2, 0.2, 0.2);
  emission = vec3(0.0);
  diffuse = vec3(0.0);
  specular = vec3(0.0);
  shine = 0.f;
  aperture = 200.f;
  halfap = 100.f;
  focalLength = 3;

}

void clamp(Color &col) {
  vec3 rgbValues = col.getColors();
  if (rgbValues[0] > 1.0) col.setR(1.0);
  if (rgbValues[1] > 1.0) col.setG(1.0);
  if (rgbValues[2] > 1.0) col.setB(1.0);
}

void Scene::render(){
  Sampler sampler= Sampler(width, height);
  Sample curSample = Sample(0.0, 0.0);
  cout << "current" << sampler.currPixel << endl;
  cout << "total" << sampler.numPixels << endl;
  Ray r, dofray;
  srand((unsigned) time(0));
  int i = 0;
  while(sampler.getSample(&curSample)) {
    if (i % (sampler.numPixels / 20) == 0) {
      cout << (i / (sampler.numPixels / 20)) * 5 << "\%\n";
    }
    //cout << i << endl;
    Color outputColor = Color(0, 0, 0);
    Color intermColor = Color(0, 0, 0);
    //Color dofColor = Color(0, 0, 0);
    for (int p = 0; p < 8; p++) {
      for (int q = 0; q < 8; q++) {
	float ii = curSample.x();
	float jj = curSample.y();
	float e1 = (float) (rand() % RAND_MAX);
	float e2 = (float) (rand() % RAND_MAX);
	e1 = e1 / ((float) RAND_MAX);
	e2 = e2 / ((float) RAND_MAX);

	Sample jitter = Sample(ii + ((p + e1) / 8), jj + ((q + e2) / 8));
	camera->generateRay(jitter, &r);

	
	vec3 focalpt = camera->findFocalPt(r, focalLength);
	//cout << "my focal point! " << focalpt.x << " " <<  focalpt.y << " " << focalpt.z << endl;

	float jitI = jitter.x();
	float jitJ = jitter.y();
	float e3 = (float) (rand() % RAND_MAX);
	float e4 = (float) (rand() % RAND_MAX);
	e3 = e3 / ((float) RAND_MAX);
	e4 = e4 / ((float) RAND_MAX);

	Sample dofSample =
	  Sample( jitI + (aperture * ((p + e3) / 8.f)) - halfap,
		  jitJ + (aperture * ((q + e4) / 8.f)) - halfap);
	camera->generateDOFRay(dofSample, &dofray, focalpt);

	/*

	for (int k = 0; k < 4; k++) {
	  for (int l = 0; l < 4; l++) {
	    float jitI = jitter.x();
	    float jitJ = jitter.y();
	    float e3 = (float) (rand() % RAND_MAX);
	    float e4 = (float) (rand() % RAND_MAX);
	    e3 = e3 / ((float) RAND_MAX);
	    e4 = e4 / ((float) RAND_MAX);
	    //Sample dofSample =
	    //  Sample(jitI + k + e1 - 1.f, jitJ + l + e2 - 1.f);
	    Sample dofSample =
	      Sample( jitI + (200 * ((k + e3) / 4.f)) - 100.f,
		      jitJ + (200 * ((l + e4) / 4.f)) - 100.f);
	    camera->generateDOFRay(dofSample, &dofray, focalpt);
	    rt->trace(dofray, maxDepth, dofColor);
	    outputColor += dofColor;
	    //fuck
	  }
	}

	outputColor *= (1.0 / 16.0);
	//clamp(outputColor);
	
	*/

	rt->trace(dofray, maxDepth, outputColor);
	intermColor += outputColor;
      }
    }
    Color finalColor = Color( ( (1.0f / 64.0f) * intermColor.getColors()) );
    clamp(finalColor);
    film->put(curSample, finalColor);
    i++;
  }
  film->output("test.png");
}


void rightmultiply(const mat4 & M, stack<mat4> &transfstack) {
  mat4 &T = transfstack.top() ; 
  // Right multiply M, but do this left to account for row/column major 
  T = T * M ; 
}



bool readvals(stringstream &s, const int numvals, float * values) {
  for (int i = 0 ; i < numvals ; i++) {
    s >> values[i] ; 
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n" ; 
      return false ;
    }
  }
  return true ; 
}

void Scene::parse(const char * filename)
{

//  init();

  vector<vec3> verts = vector<vec3>();
  vector<vec3> vnverts = vector<vec3>();
  vector<vec3> vnnorms = vector<vec3>();
  
  string str, cmd ; 
  ifstream in ;
  in.open(filename) ; 
  if (in.is_open()) {

    // I need to implement a matrix stack to store transforms.  
    // This is done using standard STL Templates 
    stack <mat4> transfstack ; 
    transfstack.push(mat4(1.0)) ;  // identity

    getline (in, str) ; 

    while ((str.find_first_not_of(" \t\r\n") == string::npos) || (str[0] == '#')) {
      getline(in, str);
      //cout << "yoyoyo" << endl;
    }

    stringstream sizecmd(str);
    sizecmd >> cmd;
    if (cmd == "size") {
      bool validsizeinput;
      float dimension[2];
      if (readvals(sizecmd, 2, dimension)) {
        width = ((int) dimension[0]);
        height = ((int) dimension[1]);
      } else {
        cerr << "Malformed input to SIZE \n" ;
      }
    } else {
      cerr << "First command should be SIZE \n" ;
    }
    //check for image size

    getline(in, str);

    while (in) {
      if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
        // Ruled out comment and blank lines 

        stringstream s(str) ;
        s >> cmd ; 
        int i ; 
        float values[10] ; // position and color for light, colors for others
                             // Up to 10 params for cameras.  
        bool validinput ; // validity of input 


        // MISC
        if (cmd == "maxdepth") { 
          validinput = readvals(s, 1, values) ;
          if (validinput) {
            maxDepth = values[0];
          }
        }

        else if (cmd == "output") { 
          validinput = readvals(s, 1, values) ;
          if (validinput) {
            //outputFile = string(values[0]);
          }
        }

        else if (cmd == "maxverts") { 
          validinput = readvals(s, 1, values) ;
          if (validinput) {
            //ignore for now
          }
        }

        else if (cmd == "outvertnorms") { 
          validinput = readvals(s, 1, values) ;
          if (validinput) {
            //ignore for now
          }
        }


        // DIRECTIONAL LIGHT
        else if (cmd == "directional") { 
          validinput = readvals(s, 6, values) ;
          if (validinput) {
            vec3 dir = glm::normalize(vec3(values[0], values[1], values[2]));
            dir = glm::normalize(vec3(transfstack.top() * vec4(dir, 0.0)));
            Color color = Color(values[3], values[4], values[5]);
            lights->push_back(new DirLight(color, Direction(dir)));
          }
        }

        // POINT LIGHT
        else if (cmd == "point") { 
          validinput = readvals(s, 6, values) ;
          if (validinput) {
            vec3 pt = vec3(values[0], values[1], values[2]);
            pt = vec3(transfstack.top() * vec4(pt, 1.0));
            Color color = Color(values[3], values[4], values[5]);
            lights->push_back(new PointLight(color, Point(pt), attenuation));
          }
        }

        // Material Commands . 

        else if (cmd == "attenuation") {
          validinput = readvals(s, 3, values) ; // colors 
          if (validinput) 
             attenuation = vec3(values[0], values[1], values[2]);
        }
        else if (cmd == "ambient") {
          validinput = readvals(s, 3, values) ; // colors 
          if (validinput) 
             ambient = vec3(values[0], values[1], values[2]);
        }
        else if (cmd == "diffuse") {
          validinput = readvals(s, 3, values) ; 
          if (validinput) 
             diffuse = vec3(values[0], values[1], values[2]);
        }
        else if (cmd == "specular") {
          validinput = readvals(s, 3, values) ; 
          if (validinput) 
             specular = vec3(values[0], values[1], values[2]);
        }
        else if (cmd == "emission") {
          validinput = readvals(s, 3, values) ; 
          if (validinput) 
             emission = vec3(values[0], values[1], values[2]);
        }
        else if (cmd == "shininess") {
          validinput = readvals(s, 1, values) ; 
          if (validinput) shine = values[0] ; 
        }


        //CAMERA  DONE

        else if (cmd == "camera") {
          validinput = readvals(s,10,values) ;
          if (validinput) {
            vec3 lookfrom = vec3(values[0], values[1], values[2]);
            vec3 lookat = vec3(values[3], values[4], values[5]);
            vec3 up = glm::normalize(vec3(values[6], values[7], values[8]));
            float fov = values[9];
            camera = new Camera(lookfrom, lookat, up, fov, height, width);
          }
        }

        else if (cmd == "lens") {
          validinput = readvals(s,2,values) ;
          if (validinput) {
            aperture = values[0];
	    halfap = aperture * 0.5;
            focalLength = values[1];
          }
        }

        // SHAPES N SHIT

        // SPHERE DONE
        else if (cmd == "sphere") {
          validinput = readvals(s, 4, values) ; 
          if (validinput) {
            Point center = Point(values[0], values[1], values[2]);
            float radius = values[3];
            shapes->push_back(new Sphere(center,
                                         radius,
                                         Color(ambient),
                                         Color(diffuse),
                                         Color(specular),
                                         Color(emission), shine, transfstack.top())); 
          }
        }

        else if (cmd == "vertex") {
          validinput = readvals(s, 3, values) ; 
          if (validinput) {
            vec3 vert = vec3(values[0], values[1], values[2]);
            verts.push_back(vert);
          }
        }
        else if (cmd == "vertexnormal") {
          validinput = readvals(s, 6, values) ; 
          if (validinput) {
            vec3 vert = vec3(values[0], values[1], values[2]);
            vec3 norm = vec3(values[3], values[4], values[5]);
            vnverts.push_back(vert);
            vnnorms.push_back(norm);
          }
        }
        else if (cmd == "tri") {
          validinput = readvals(s, 3, values) ; 
          if (validinput) {
            vec4 temp1 = vec4(verts[values[0]], 1.0);
            vec4 temp2 = vec4(verts[values[1]], 1.0);
            vec4 temp3 = vec4(verts[values[2]], 1.0);
            Point v1 = Point(vec3(transfstack.top() * temp1));
            Point v2 = Point(vec3(transfstack.top() * temp2));
            Point v3 = Point(vec3(transfstack.top() * temp3));

            //cout << "v1: " << v1.getPoint().x << v1.getPoint().y << v1.getPoint().z << endl;
            //cout << "v2: " << v2.getPoint().x << v2.getPoint().y << v2.getPoint().z << endl;
            //cout << "v3: " << v3.getPoint().x << v3.getPoint().y << v3.getPoint().z << endl << endl;

            shapes->push_back(new Triangle(v1, v2, v3, Color(ambient), Color(diffuse), Color(specular), Color(emission), shine));
          }
        }
        else if (cmd == "trinormal") {
          validinput = readvals(s, 3, values) ; 
          if (validinput) {
            Point v1 = Point(vnverts[values[0]]);
            Point v2 = Point(vnverts[values[1]]);
            Point v3 = Point(vnverts[values[2]]);
						Direction vn1 = Direction(vnnorms[values[0]]);
						Direction vn2 = Direction(vnnorms[values[1]]);
						Direction vn3 = Direction(vnnorms[values[2]]);
            shapes->push_back(new TriNormal(v1, v2, v3, vn1, vn2, vn3, ambient, diffuse, specular, emission, shine));
          }
        }


        // TRANSFORMATIONS -- WILL FIX

        else if (cmd == "translate") {
          validinput = readvals(s,3,values) ; 
          if (validinput) {
	    float tx = values[0];
	    float ty = values[1];
	    float tz = values[2];
	    mat4 translate = Transform::translate(tx, ty, tz);
	    rightmultiply(translate, transfstack);
//cout << "hey ho" << endl;
          }
        }
        else if (cmd == "scale") {
          validinput = readvals(s,3,values) ; 
          if (validinput) {
	    float sx = values[0];
	    float sy = values[1];
	    float sz = values[2];
	    mat4 scale = Transform::scale(sx, sy, sz);
	    rightmultiply(scale, transfstack);
          }
        }
        else if (cmd == "rotate") {
          validinput = readvals(s,4,values) ; 
          if (validinput) {
	    float x = values[0];
	    float y = values[1];
	    float z = values[2];
	    vec3 axis = glm::normalize(vec3(x, y, z));
	    float degrees = values[3];
	    mat4 rotate = mat4(Transform::rotate(degrees, axis));
	    rightmultiply(rotate, transfstack);  
//cout << "bernernernern" << endl;
          }
        }
        
        // I include the basic push/pop code for matrix stacks
        else if (cmd == "pushTransform") 
          transfstack.push(transfstack.top()) ; 
        else if (cmd == "popTransform") {
          if (transfstack.size() <= 1) 
            cerr << "Stack has no elements.  Cannot Pop\n" ; 
          else transfstack.pop() ; 
        }
        
        else {
          cerr << "Unknown Command: " << cmd << " Skipping \n" ; 
        }
      }
      getline (in, str) ; 
    }

  }
  else {
    cerr << "Unable to Open Input Data File " << filename << "\n" ; 
    throw 2 ; 
  }

  rt = new RayTracer(shapes, lights, camera->getCameraPos());
  film = new Film(height, width);
  

//cout << "more junk " << shapes->empty() << endl;
//cout << "shienshienshine" << (*shapes)[0]->getDiffuse().getR() << endl;
  
}



Scene::~Scene(void)
{

}

