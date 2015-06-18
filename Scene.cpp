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
#include <omp.h>

using namespace std;

Scene::Scene()
{
  init();
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
  aperture = 0.0;
  halfap = 0.0;
  focalLength = 3;
  index = 0.0;

}

void clamp(Color &col) {
  vec3 rgbValues = col.getColors();
  if (rgbValues[0] > 1.0) col.setR(1.0);
  if (rgbValues[1] > 1.0) col.setG(1.0);
  if (rgbValues[2] > 1.0) col.setB(1.0);
}

void Scene::render(){
  Sampler sampler= Sampler(width, height);
  Sample curSample = Sample(0.0, 0.0); //private
  cout << "current" << sampler.currPixel << endl;
  cout << "total" << sampler.numPixels << endl;
  Ray r, dofray; //private
  srand((unsigned) time(0));
  int i = 0; //private?

  # pragma omp parallel for private(curSample, r, dofray) num_threads(8)
  for (int sampleX = 0; sampleX < width; sampleX++) {
    for (int sampleY = 0; sampleY < height; sampleY++) {
      curSample.setX((float) sampleX);
      curSample.setY((float) sampleY);


      if (i % (sampler.numPixels / 20) == 0) {
        cout << (i / (sampler.numPixels / 20)) * 5 << "\%\n";
      }
      Color outputColor = Color(0, 0, 0);
      Color intermColor = Color(0, 0, 0);
      for (int p = 0; p < 9; p++) {
        for (int q = 0; q < 9; q++) {
        	float ii = curSample.x();
        	float jj = curSample.y();
        	float e1 = (float) (rand() % RAND_MAX);
        	float e2 = (float) (rand() % RAND_MAX);
        	e1 = e1 / ((float) RAND_MAX);
        	e2 = e2 / ((float) RAND_MAX);

        	Sample jitter = Sample(ii + ((p + e1) / 9), jj + ((q + e2) / 9));
        	camera->generateRay(jitter, &r);

        	if (aperture != 0.0) {

        	  vec3 focalpt = camera->findFocalPt(r, focalLength);

        	  float jitI = jitter.x();
        	  float jitJ = jitter.y();
        	  float e3 = (float) (rand() % RAND_MAX);
        	  float e4 = (float) (rand() % RAND_MAX);
        	  e3 = e3 / ((float) RAND_MAX);
        	  e4 = e4 / ((float) RAND_MAX);

        	  Sample dofSample =
        	    Sample( jitI + (aperture * ((p + e3) / 9.f)) - halfap,
        		    jitJ + (aperture * ((q + e4) / 9.f)) - halfap);
        	  camera->generateDOFRay(dofSample, &dofray, focalpt);
        	  rt->trace(dofray, maxDepth, outputColor);

        	} else {
        	  rt->trace(r, maxDepth, outputColor);
        	}
        	intermColor += outputColor;
        }
      }
      Color finalColor = Color( ( (1.0f / 81.0f) * intermColor.getColors()) );
      clamp(finalColor);
      film->put(curSample, finalColor);
      i++;

    }
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

  vector<vec3> verts = vector<vec3>();
  vector<vec3> vnverts = vector<vec3>();
  vector<vec3> vnnorms = vector<vec3>();
  
  string str, cmd ; 
  ifstream in ;
  in.open(filename) ; 
  if (in.is_open()) {

    stack <mat4> transfstack ; 
    transfstack.push(mat4(1.0)) ;  // identity

    getline (in, str) ; 

    while ((str.find_first_not_of(" \t\r\n") == string::npos) || (str[0] == '#')) {
      getline(in, str);
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
            // Not implemented -- ignore
          }
        }

        else if (cmd == "maxverts") { 
          validinput = readvals(s, 1, values) ;
          if (validinput) {
            // Not implemented -- ignore
          }
        }

        else if (cmd == "outvertnorms") { 
          validinput = readvals(s, 1, values) ;
          if (validinput) {
            // Not implemented -- ignore
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
        else if (cmd == "index") {
          validinput = readvals(s, 1, values) ; 
          if (validinput) index = values[0] ; 
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
                                         Color(emission),
                              					 shine,
                              					 transfstack.top(),
                              					 index)); 
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

            shapes->push_back(new Triangle(v1, v2, v3, Color(ambient), Color(diffuse), Color(specular), Color(emission), shine, index));
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


        else if (cmd == "translate") {
          validinput = readvals(s,3,values) ; 
          if (validinput) {
      	    float tx = values[0];
      	    float ty = values[1];
      	    float tz = values[2];
      	    mat4 translate = Transform::translate(tx, ty, tz);
      	    rightmultiply(translate, transfstack);
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
          }
        }
        
        else if (cmd == "pushTransform") {
          transfstack.push(transfstack.top()) ;
        }
        
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
  bvhTree = (Shape *) createBVHtree(*shapes);
  rt = new RayTracer(shapes, lights, camera->getCameraPos(), bvhTree);
  film = new Film(height, width);
  
}



Scene::~Scene(void)
{

}

