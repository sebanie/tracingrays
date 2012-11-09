#if !defined(POINT_H)
#define POINT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 


class Point 
{
 private:
  vec3 mypoint;
  
 public:
  Point(void);
  Point(float x, float y, float z);
  virtual ~Point(void);
  vec3 getPoint(void);
  float x(void);
  float y(void);
  float z(void);
  Point* add(Direction* dir);
  //Direction* operator-(const Point* pt);
};


#endif

