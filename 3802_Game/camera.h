#ifndef _CAMERA_CLASS
#define _CAMERA_CLASS

#include <math.h>

#include "common.h"

class Camera{
public:
	
	tVector3 m_pos;
	tVector3 m_view;
	tVector3 m_up;
	
	void Strafe_Camera(float speed);

	void Mouse_Move(int window_width, int window_height);

	void Move_Camera(float speed);

	void Rotate_View(float speed);

	void Position_Camera(float pos_x,float pos_y, float pos_z, float view_x, float view_y, float view_z, float up_x, float up_y, float up_z);

};

#endif // _CAMERA_CLASS