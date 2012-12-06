#include "Film.h"
#include "Scene.h"
#include <sys/time.h>
#include <stdio.h>

Scene scene;

struct timeval start, end;

int main(int argc, char* argv[]){
  Scene scene = Scene();
  scene.parse(argv[1]);
  gettimeofday(&start, NULL);
  scene.render();
  gettimeofday(&end, NULL);
  float delta = ((end.tv_sec - start.tv_sec) * 1000000u
		 + end.tv_usec - start.tv_usec) / 1.e6;
  cout << "Time taken to render: "
       << (delta / 60.f) << " minutes.\n";
  return 0;
}
