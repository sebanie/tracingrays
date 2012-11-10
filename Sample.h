#if !defined(SAMPLE_H)
#define SAMPLE_H


class Sample
{
 private:
  float _x, _y;

 public:
  Sample(void);
  Sample(float x, float y);
  float x(void);
  float y(void);
  void setX(float x);
  void setY(float y);
  ~Sample(void);
};


#endif

