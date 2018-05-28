#ifndef _VECTOR3D_C
#define _VECTOR3D_C

class Vector3D{
public:
	float x,y,z;
	Vector3D::Vector3D();
	Vector3D::Vector3D(float x, float y, float z);

	bool Vector3D::operator=(Vector3D other);

	Vector3D Vector3D::operator+(Vector3D other);
	Vector3D Vector3D::operator-(Vector3D other);
	Vector3D Vector3D::operator*(Vector3D other);
	Vector3D Vector3D::operator/(Vector3D other);

	Vector3D Vector3D::operator*(float f);
	Vector3D Vector3D::operator/(float f);

	float Vector3D::get_len();
	float Vector3D::get_square_len();

	Vector3D Vector3D::get_unit();

	Vector3D Vector3D::get_interpolation(Vector3D other, float ratio);

	Vector3D Vector3D::get_reflection(Vector3D surface_normal);

	Vector3D Vector3d::get_rotation_euler(Vector3D 

};

#endif // _VECTOR3D_C
