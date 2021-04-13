#ifndef _INCLUDE_SKYBOX
#define _INCLUDE_SKYBOX

#include "common.h"
#include "image.h"

class Skybox{
public:
	GLuint Front,Back,Left,Right,Up,Down;
	float x,y,z,width,height,length;

	Skybox::Skybox();
	Skybox::Skybox(float x,float y, float z, float width, float height, float length);

	void Skybox::Assign_Front(Image img);
	void Skybox::Assign_Back(Image img);
	void Skybox::Assign_Left(Image img);
	void Skybox::Assign_Right(Image img);
	void Skybox::Assign_Up(Image img);
	void Skybox::Assign_Down(Image img);

	void Skybox::Render();

};

#endif // _INCLUDE_SKYBOX