#ifndef _MATH_3D_H
#define _MATH_3D_H

// Includes
#include <math.h>

// Preprocessor Directives

#define MAX_BOUNDING_BOXES 512

// Structure Declarations

// From apron tutorials
struct tVector3	// Extended 3D Vector Struct
{			
	tVector3() {} // Struct Constructor
	tVector3 (float new_x, float new_y, float new_z) // Init Constructor	 
	{ x = new_x; y = new_y; z = new_z; }
	// overload + operator
	tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
	// overload - operator
	tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
	// overload * operator
	tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
	// overload / operator
	tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}
	
	float x, y, z;						// 3D vector coordinates
};

struct tVector2 {
	float x,y;
};

struct tBoundingBox {
	tVector3 min,max;
};

// Function Declarations

float abs(float n);

tVector3 cross(tVector3 v1,tVector3 v2);

float dot(tVector3 v1, tVector3 v2);

tVector3 normalize(tVector3 n);

tVector3 normal(tVector3 n[]);

float magnitude(tVector3 n);

int collision_bounding_box(tBoundingBox * box_list, int n_bounding_boxes,tVector3 point);

int inside_bounding_box(tBoundingBox box, tVector3 point);

#endif // _MATH_3D_H