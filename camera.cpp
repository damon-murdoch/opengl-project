#include "camera.h"

void Camera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
							  float view_x, float view_y, float view_z,
							  float up_x,   float up_y,   float up_z)
{
	m_pos	= tVector3(pos_x,  pos_y,  pos_z );
	m_view	= tVector3(view_x, view_y, view_z);
	m_up		= tVector3(up_x,   up_y,   up_z  );	
}

void Camera::Move_Camera(float speed)
{
	tVector3 vVector = m_view - m_pos;

	m_pos.x  = m_pos.x  + vVector.x * speed;
	m_pos.z  = m_pos.z  + vVector.z * speed;
	m_view.x = m_view.x + vVector.x * speed;
	m_view.z = m_view.z + vVector.z * speed;
}

void Camera::Rotate_View(float speed)
{
	tVector3 vVector = m_view - m_pos;

	m_view.z = (float)(m_pos.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	m_view.x = (float)(m_pos.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}

void Camera::Strafe_Camera(float speed)
{
	tVector3 vVector = m_view - m_pos;
	tVector3 vOrthoVector;

	vOrthoVector.x = -vVector.z;
	vOrthoVector.z =  vVector.x;

	m_pos.x  = m_pos.x  + vOrthoVector.x * speed;
	m_pos.z  = m_pos.z  + vOrthoVector.z * speed;
	m_view.x = m_view.x + vOrthoVector.x * speed;
	m_view.z = m_view.z + vOrthoVector.z * speed;
}

void Camera::Mouse_Move(int wndWidth, int wndHeight)
{
	POINT mousePos;	
	int mid_x = wndWidth  >> 1;	
	int mid_y = wndHeight >> 1;	
	float angle_y  = 0.0f;				
	float angle_z  = 0.0f;							
	
	GetCursorPos(&mousePos);				
	
	if( (mousePos.x == mid_x) && (mousePos.y == mid_y) ) return;

	SetCursorPos(mid_x, mid_y);				

	angle_y = (float)( (mid_x - mousePos.x) ) / 1000;		
	angle_z = (float)( (mid_y - mousePos.y) ) / 1000;

	m_view.y += angle_z * 2;

	if((m_view.y - m_pos.y) > 8)  m_view.y = m_pos.y + 8;
	if((m_view.y - m_pos.y) <-8)  m_view.y = m_pos.y - 8;
	
	Rotate_View(-angle_y);
}