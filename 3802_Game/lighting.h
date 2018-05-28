#ifndef _INCLUDE_LIGHTING
#define _INCLUDE_LIGHTING

#include "common.h"

class Light{
public:
	GLfloat ambient_light[4];
	GLfloat diffuse_light[4];
	GLfloat specular_light[4];
	GLfloat position[4];

	Light::Light();
	Light::Light(GLfloat ambient_light[4],GLfloat diffuse_light[4],GLfloat specular_light[4],GLfloat position[4]);
	void Light::Bind(GLint light);
	void Light::Initialise(GLfloat ambient_light[4],GLfloat diffuse_light[4],GLfloat specular_light[4],GLfloat position[4]);

};

#endif