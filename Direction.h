#if !defined(DIRECTION_H)
#define DIRECTION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 


class Direction
{
 private:
  vec3 mydir;
  
 public:
  Direction(void);
  Direction(vec3 dir);
  virtual ~Direction();
  vec3 getDir(void);
  float x(void);
  float y(void);
  float z(void);
  Direction* mult(float t);
};



#endif

