#if !defined(LIGHT_H)
#define LIGHT_H

#include "Color.h"

class Light{
	protected:
		Color lightColor;
	public:
		Light(){}
		Color getColor(){
			return lightColor;
		}
};

#endif


