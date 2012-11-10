#if !defined(SAMPLER_H)
#define SAMPLER_H


class Sampler
{
 private:
  int _sizeX, _sizeY, currPixel, numPixels; 

 public:
  Sampler(int sizeX, int sizeY);
  bool getSample(Sample *sample);
  ~Sampler(void);
};


#endif

