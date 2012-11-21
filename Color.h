#if !defined(COLOR_H)
#define COLOR_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ;

class Color{
 private:
  vec3 rgbValues;
 public:
  Color(){
    rgbValues = vec3(0.0, 0.0, 0.0);
  }
  Color(float r, float g, float b){
    rgbValues = vec3(r,g,b);
  }
  Color(vec3 input){
    rgbValues = input;
  }
  vec3 getColors(){
    return rgbValues;
  }
  float getR(){
    return rgbValues[0];
  }
  float getG(){
    return rgbValues[1];
  }
  float getB(){
    return rgbValues[2];
  }
  void setR(float r){
    rgbValues[0] = r;
  }
  void setG(float g){
    rgbValues[1] = g;
  }
  void setB(float b){
    rgbValues[2] = b;
  }
  void setColors(float r, float g, float b){
    rgbValues[0] = r;
    rgbValues[1] = g;
    rgbValues[2] = b;
  }
  void setColors(Color color){
    vec3 col = color.getColors();
    rgbValues[0] = col.x;
    rgbValues[1] = col.y;
    rgbValues[2] = col.z;
  }
  Color operator=(const Color &param){
    if(this != &param){
      rgbValues = param.rgbValues;
    }
    return *this;
  }
  Color operator+=(const Color &param){
    rgbValues += param.rgbValues;
    if (rgbValues[0] > 1.0) rgbValues[0] = 1.0;
    if (rgbValues[1] > 1.0) rgbValues[1] = 1.0;
    if (rgbValues[2] > 1.0) rgbValues[2] = 1.0;
    return *this;
  }
  Color operator*=(float scalar){
    rgbValues *= scalar;
    if (rgbValues[0] > 1.0) rgbValues[0] = 1.0;
    if (rgbValues[1] > 1.0) rgbValues[1] = 1.0;
    if (rgbValues[2] > 1.0) rgbValues[2] = 1.0;
    return *this;
  }
  Color operator*=(const Color &param){
    rgbValues *= param.rgbValues;
    if (rgbValues[0] > 1.0) rgbValues[0] = 1.0;
    if (rgbValues[1] > 1.0) rgbValues[1] = 1.0;
    if (rgbValues[2] > 1.0) rgbValues[2] = 1.0;
    return *this;
  }
  Color operator+(const Color &operand) const{
    Color result = *this;
    result += operand;
    return result;
  }
  Color operator*(const double scalar) const{
    Color result = *this;
    result *= scalar;
    return result;
  }
  Color operator*(const Color &operand) const{
    Color result = *this;
    result *= operand;
    return result;
  }
};
#endif
