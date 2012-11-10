#include "Scene.h"
using namespace std;

Scene::Scene(){
  width = 160;
  height = 120;
  maxDepth = 5;
  fovy = 35
  outputFile = "out.png";
  camera = new Camera();
  film = new Film();
  
}
