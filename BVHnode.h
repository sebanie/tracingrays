#if !defined(BVHNODE_H)
#define BVHNODE_H

#include "Shape.h"
#include "Ray.h"
#include "Box.h"
#include "Intersect.h"

class BVHnode : public Shape {
 private:
  Shape *left, *right;
 public:
  BVHnode(Box bBox, Shape *l, Shape *r){
    left = l;
    right = r;
    boundingBox = bBox;
  }
  Intersect intersect(Ray r);
};

Box mergeBoxes(vector<Shape *> &shapes);
void partition(vector<Shape *> &shapes, vec3 mid, int axis,
	       vector<Shape *> &left, vector<Shape *> &right);
BVHnode* createBVHtree(vector<Shape *> &shapes);
#endif
