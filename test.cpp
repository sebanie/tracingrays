#include "Film.h"
#include "Scene.h"

Scene scene;

int main(int argc, char* argv[]){
  Scene scene = Scene();
  scene.render();
  return 0;
}
