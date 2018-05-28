#include "skybox.h"

Skybox::Skybox(){
}

Skybox::Skybox(float x,float y, float z, float width, float height, float length){
	Skybox::x = x - width / 2;
	Skybox::y = y - height / 2;
	Skybox::z = z - length / 2;
	Skybox::width=width;
	Skybox::height=height;
	Skybox::length=length;
}

void Skybox::Assign_Front(Image img){
	glGenTextures(1,&Front);
	glBindTexture(GL_TEXTURE_2D,Front);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,img.x,img.y,GL_RGB,GL_UNSIGNED_BYTE,img.data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}

void Skybox::Assign_Back(Image img){
	glGenTextures(1,&Back);
	glBindTexture(GL_TEXTURE_2D,Back);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,img.x,img.y,GL_RGB,GL_UNSIGNED_BYTE,img.data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}

void Skybox::Assign_Left(Image img){
	glGenTextures(1,&Left);
	glBindTexture(GL_TEXTURE_2D,Left);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,img.x,img.y,GL_RGB,GL_UNSIGNED_BYTE,img.data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}

void Skybox::Assign_Right(Image img){
	glGenTextures(1,&Right);
	glBindTexture(GL_TEXTURE_2D,Right);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,img.x,img.y,GL_RGB,GL_UNSIGNED_BYTE,img.data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}

void Skybox::Assign_Up(Image img){
	glGenTextures(1,&Up);
	glBindTexture(GL_TEXTURE_2D,Up);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,img.x,img.y,GL_RGB,GL_UNSIGNED_BYTE,img.data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}

void Skybox::Assign_Down(Image img){
	glGenTextures(1,&Down);
	glBindTexture(GL_TEXTURE_2D,Down);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3,img.x,img.y,GL_RGB,GL_UNSIGNED_BYTE,img.data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}

void Skybox::Render(){

	glBindTexture(GL_TEXTURE_2D,Skybox::Front);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y+height,z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width,y+height,z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width,y,z+length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Skybox::Back);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width,y,z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width,y+height,z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Skybox::Left);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y+height,z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z);		
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Skybox::Right);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width,y,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width,y,z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width,y+height,z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width,y+height,z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Skybox::Up);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width,y+height,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width,y+height,z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y+height,z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Skybox::Down);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width,y,z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width,y,z);
	glEnd();
}