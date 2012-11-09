#if !defined(SCENE_H)
#define SCENE_H

#include <vector>

// To account for C++ namespace issues
#define vector std::vector  
//typedef vector<Point> Pvector;

// The basic curve class.  The basic element is a vector of Points, 
// which is the Pvector.  
// The class has methods for drawing adding, deleting, moving, updating, 
// and so forth.  More details are in Curve.cpp 
// The draw method is virtual since it is over-ridden by the specific 
// curve (Bspline, Bezier, Bezier2 etc.).  

// points is the actual vector of points used.  
// The iterator into this (look up C++ iterators) is activePoint 
// The bool isactive indicates if there is currently any active point 
// (In previous versions, we did this by setting activePoint to null, but 
// this is no longer allowed in modern C++)


class Scene  
{
	private:
		vector<Surface> surfaces;

	public:
		Scene();
		virtual ~Scene();
		virtual void draw(int levelOfDetail);
};

#endif

