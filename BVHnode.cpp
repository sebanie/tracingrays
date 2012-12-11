#include "BVHnode.h"

Intersect BVHnode::intersect(Ray r){
  if (!boundingBox.isHit(r)){
    return Intersect();
  }
  Intersect leftIntersect = Intersect();
  Intersect rightIntersect = Intersect();
  double distLeft, distRight;

  if (left != NULL){
    leftIntersect = left->intersect(r);
  }
  if (right != NULL){
    rightIntersect = right->intersect(r);
  }
  if (leftIntersect.isHit() && rightIntersect.isHit()){
    distLeft = glm::length((leftIntersect.getPosition().getPoint() - r.getPos()));
    distRight = glm::length((rightIntersect.getPosition().getPoint() - r.getPos()));
    if (distLeft < distRight){
      return leftIntersect;
    }
    else {
      return rightIntersect;
    }
  }
  else if (leftIntersect.isHit()){
    return leftIntersect;
  }
  else if (rightIntersect.isHit()){
    return rightIntersect;
  }
  else {
    return Intersect();
  }
}
/*
bool BVHnode::shadowIntersect(Ray r){
  if (!boundingBox.isHit(r)){
    return Intersect();
  }
  Intersect leftIntersect = Intersect();
  Intersect rightIntersect = Intersect();
  double distLeft, distRight;

  if (left != NULL){
    leftIntersect = left->shadowIntersect(r);
		if(leftIntersect.isHit() && (leftIntersect.getT() < r->getTMAX())){
			return true;
		}
  }
  if (right != NULL){
    rightIntersect = right->shadowIntersect(r);
		if(rightIntersect.isHit() && (rightIntersect.getT() < r->getTMAX())){
			return true;
		}
  }
  if (leftIntersect.isHit() || rightIntersect.isHit()){
    distLeft = glm::length((leftIntersect.getPosition().getPoint() - r.getPos()));
    distRight = glm::length((rightIntersect.getPosition().getPoint() - r.getPos()));
    if (distLeft < distRight){
      return leftIntersect;
    }
    else {
      return rightIntersect;
    }
  }
  else if (leftIntersect.isHit()){
    return leftIntersect;
  }
  else if (rightIntersect.isHit()){
    return rightIntersect;
  }
  else {
    return Intersect();
  }
}
*/
Box mergeBoxes(vector<Shape *> &shapes){
  vector<Shape *>::iterator i = shapes.begin();
  vector<Shape *>::iterator end = shapes.end();
  Box newBox = (*i)->getBoundingBox();
  i++;
  for (; i != end; i++){
    newBox = newBox.merge((*i)->getBoundingBox());
  }
  return newBox;
}

void partition(vector<Shape *> &shapes, vec3 mid, int axis,
	       vector<Shape *> &left, vector<Shape *> &right){
  vector<Shape *>::iterator i = shapes.begin();
  vector<Shape *>::iterator  end = shapes.end();
  for (; i != end; i++){
    if ((*i)->getBoundingBox().center()[axis] < mid[axis]) {
      left.push_back(*i);
    }
    else {
      right.push_back(*i);
    }
  }
  if (left.size() == shapes.size()) {
    right.push_back(left.back());
    left.pop_back();
  }
  else if (right.size() == shapes.size()) {
    left.push_back(right.back());
    right.pop_back();
  }
}

int longestAxis(Box bbox) {
  vec3 minCoords = bbox.getMin();
  vec3 maxCoords = bbox.getMax();
  float xLen = maxCoords[0] - minCoords[0];
  float yLen = maxCoords[1] - minCoords[1];
  float zLen = maxCoords[2] - minCoords[2];
  if (xLen > yLen) {
    if (xLen > zLen){
      return 0;
    }
    else{
      return 2;
    }
  }
  else if (yLen > zLen) {
    return 1;
  }
  else {
    return 2;
  }
}
BVHnode* createBVHtree(vector<Shape *> &shapes) {
  int count = shapes.size();
  if (count == 0) {
    return NULL;
  }
  else if (count == 1) {
    return new BVHnode(shapes[0]->getBoundingBox(), shapes[0], NULL);
  }
  else if (count == 2) {
    Box newBox = shapes[0]->getBoundingBox().merge(shapes[1]->getBoundingBox());
    return new BVHnode(newBox, shapes[0], shapes[1]);
  }
  else {
    Box newBox = mergeBoxes(shapes);
    vec3 midPoint = newBox.center();
    vector<Shape *> left, right;
    int axis = longestAxis(newBox);
    partition(shapes, midPoint, axis, left, right);
    BVHnode *l, *r;
    l = createBVHtree(left);
    r = createBVHtree(right);
    return new BVHnode(newBox, l, r);
  }
}

