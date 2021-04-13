#include "robotprac.h"

void Draw_Cube(float x,float y, float z){
	glPushMatrix();
	glBegin(GL_POLYGON);
	{
		// Top Face
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,-1.0f);
		glVertex3f(-1.0f,0.0f,-1.0f);
		glVertex3f(-1.0f,0.0f,0.0f);

		// Front Face
		glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, 0.0f);

		// Right Face
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, -1.0f);
        glVertex3f(0.0f, 0.0f, -1.0f);

        // Left Face
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);

        // Bottom Face
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);

        // Back Face
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(0.0f, -1.0f, -1.0f);
	}
	glEnd();
	glPopMatrix();
}

void Draw_Arm(float x, float y, float z){
	glPushMatrix();
	{
		glColor3f(1.0f,0.0f,0.0f);
		glTranslatef(x,y,z);
		glScalef(1.0f,4.0f,1.0f);
		Draw_Cube(0.0f,0.0f,0.0f);
	}
	glPopMatrix();
}

void Draw_Head(float x, float y, float z){
	glPushMatrix();
	{
		glColor3f(1.0f,1.0f,1.0f);
		glTranslatef(x,y,z);
		glScalef(2.0f,2.0f,2.0f);
		Draw_Cube(0.0f,0.0f,0.0f);
	}
	glPopMatrix();
}

void Draw_Torso(float x, float y, float z)
{
    glPushMatrix();
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glTranslatef(x, y, z);
		glScalef(3.0f, 5.0f, 1.0f);
		Draw_Cube(0.0f, 0.0f, 0.0f);
	}
	glPopMatrix();
}

void Draw_Leg(float x, float y, float z)
{
    glPushMatrix();
	{
		glColor3f(1.0f, 1.0f, 0.0f);
        glTranslatef(x, y, z);
		glScalef(1.0f, 5.0f, 1.0f);
        Draw_Cube(0.0f, 0.0f, 0.0f);
	}
    glPopMatrix();
}