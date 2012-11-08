// Transform.cpp: implementation of the Transform class.


#include "Transform.h"


// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  float rads = glm::radians(degrees);
  float x = axis[0];
  float y = axis[1];
  float z = axis[2];
  mat3 outerProd =
    mat3(
	 x*x, y*x, z*x,
	 x*y, y*y, z*y,
	 x*z, y*z, z*z
	 );
  mat3 dual =
    mat3(
	 0, z, -y,
	 -z, 0, x,
	 y, -x, 0
	 );
  mat3 rotateMat = (glm::mat3(1.0) * glm::cos(rads));
  return rotateMat
    + ((1 - glm::cos(rads)) * outerProd)
    + glm::sin(rads) * dual;  
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 rotateMat = rotate(-degrees, glm::normalize(up));
  eye = eye * rotateMat;  
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
  vec3 side = glm::cross(up, eye);
  mat3 rotateMat = rotate(degrees, glm::normalize(side));
  eye = eye * rotateMat;
  up = up * rotateMat; 
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
  //need to fix with nonzero center
  vec3 negEye =
    vec3(-eye[0], -eye[1], -eye[2]);

  vec3 w = glm::normalize(eye - center);
  vec3 u = glm::normalize(glm::cross(up, w));
  vec3 v = glm::cross(w, u);

  float uX = u[0];
  float uY = u[1];
  float uZ = u[2];

  float vX = v[0];
  float vY = v[1];
  float vZ = v[2];

  float wX = w[0];
  float wY = w[1];
  float wZ = w[2];

  float reX = glm::dot(negEye, u);
  float reY = glm::dot(negEye, v);
  float reZ = glm::dot(negEye, w);

  mat4 lookAt =
    mat4(
	 uX, uY, uZ, reX,
	 vX, vY, vZ, reY,
	 wX, wY, wZ, reZ,
	 0.0, 0.0, 0.0, 1.0
	 );
  return lookAt;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  //check if transpose
  float A = - (zFar + zNear) / (zFar - zNear);
  float B = - (2 * zFar * zNear) / (zFar - zNear);
  float d = glm::cos(glm::radians(fovy / 2)) / glm::sin(glm::radians(fovy / 2));
  mat4 persp =
    mat4(
	 (d / aspect), 0.0, 0.0, 0.0,
	 0.0, d, 0.0, 0.0,
	 0.0, 0.0, A, B,
	 0.0, 0.0, -1.0, 0.0
	 );
  return persp;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
  mat4 scaleMat =
    mat4(
	 sx, 0.0, 0.0, 0.0,
	 0.0, sy, 0.0, 0.0,
	 0.0, 0.0, sz, 0.0,
	 0.0, 0.0, 0.0, 1.0
	 );
  return scaleMat;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
  //need to check if transpose or not
  mat4 scaleMat =
    mat4(
	 1.0, 0.0, 0.0, 0.0,
	 0.0, 1.0, 0.0, 0.0,
	 0.0, 0.0, 1.0, 0.0,
	 tx, ty, tz, 1.0
	 );
  return scaleMat;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) {
  vec3 x = glm::cross(up,zvec) ; 
  vec3 y = glm::cross(zvec,x) ; 
  vec3 ret = glm::normalize(y) ; 
  return ret ; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
