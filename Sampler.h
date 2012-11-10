#if !defined(SAMPLER_H)
#define SAMPLER_H
#include "Sample.h"

class Sampler
{
 private:
  int _sizeX, _sizeY; 

 public:
  int currPixel, numPixels;
  Sampler(int sizeX, int sizeY);
  bool getSample(Sample *sample);
  ~Sampler(void);
};


#endif

