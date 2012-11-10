#include "Sampler.h"
#include "Sample.h"

Sampler::Sampler(int sizeX, int sizeY)
{
  _sizeX = sizeX;
  _sizeY = sizeY;
  numPixels = sizeX * sizeY;
  currPixel = 0;
}

bool Sampler::getSample(Sample *sample)
{
  if (currPixel != numPixels) {
    sample->setX(((float) (currPixel % _sizeX)));
    sample->setY(((float) (currPixel / _sizeX)));
    currPixel++;
    return true;
  } else {
    return false;
  }

}

Sampler::~Sampler(void)
{

}
