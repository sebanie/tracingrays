#if !defined(FILM_H)
#define FILM_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Color.h"
#include <iostream>
#include <string>

using namespace std;
typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ;
typedef glm::vec2 vec2 ;

class Film{
 private:
  vector<vector<Color> > pixelData;
 public:
  Film();
  void put(vec2 pixel, Color c);
  Color getPixel(int x, int y);
  void output(string path);
};
#endif
