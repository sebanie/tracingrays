#include "Film.h"
#include "Scene.h"

Scene scene;

int main(int argc, char* argv[]){
  Scene scene = Scene();
  scene.parse(argv[1]);
  scene.render();
  return 0;
}
