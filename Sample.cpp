#include "Sample.h"


Sample::Sample(void)
{

}

Sample::Sample(float x, float y)
{
  _x = x;
  _y = y;
}

float Sample::x(void)
{
  return _x;
}


float Sample::y(void)
{
  return _y;
}

void Sample::setX(float x)
{
  _x = x;
}

void Sample::setY(float y)
{
  _y= y;
}

Sample::~Sample(void)
{

}
