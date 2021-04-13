#include "lighting.h"

Light::Light(){
	for(int i=0;i<4;i++){
		Light::ambient_light[i]=0;
		Light::diffuse_light[i]=0;
		Light::specular_light[i]=0;
		Light::position[i]=0;
	}
}

Light::Light(GLfloat ambient_light[4],GLfloat diffuse_light[4],GLfloat specular_light[4],GLfloat position[4]){
	Light::Initialise(ambient_light,diffuse_light,specular_light,position);
}

void Light::Initialise(GLfloat ambient_light[4],GLfloat diffuse_light[4],GLfloat specular_light[4],GLfloat position[4]){
	for(int i=0;i<4;i++){
		Light::ambient_light[i]=ambient_light[i];
		Light::diffuse_light[i]=diffuse_light[i];
		Light::specular_light[i]=specular_light[i];
		Light::position[i]=position[i];
	}
}

void Light::Bind(GLint light){
	glEnable(GL_LIGHT0);
	glLightfv(light,GL_AMBIENT,Light::ambient_light);
	glLightfv(light,GL_DIFFUSE,Light::diffuse_light);
	glLightfv(light,GL_SPECULAR,Light::specular_light);
	glLightfv(light,GL_POSITION,Light::position);
}