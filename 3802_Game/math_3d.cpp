#include "math_3d.h"

tVector3 cross(tVector3 v1,tVector3 v2){
	tVector3 normal;
	normal.x = ((v1.y*v2.z) - (v1.z*v2.y));
	normal.y = ((v1.z*v2.x) - (v1.x*v2.z));
	normal.z = ((v1.x*v2.y) - (v1.y*v2.x));
	return normal;
}

float dot(tVector3 v1, tVector3 v2){
	return ((v1.x * v2.x) + (v1.y*v2.y) + (v1.z * v2.z)); 
}

tVector3 normalize(tVector3 n){
	float m = magnitude(n);
	n.x /= m;
	n.y /= m;
	n.z /= m;
	return n;
}

tVector3 normal(tVector3 vt[]){
	tVector3 v1,v2,normal;
	v1 = vt[2]-vt[0];
	v2 = vt[1]-vt[0];
	normal = cross(v1,v2);
	normal = normalize(normal);
	return normal;
}

float magnitude(tVector3 n){
	return (float)sqrt((n.x*n.x)+(n.y*n.y)+(n.z*n.z));
}

int collision_bounding_box(tBoundingBox * box_list, int n_bounding_boxes,tVector3 point){
	for(int i=0; i<n_bounding_boxes;i++){
		if(inside_bounding_box(box_list[i],point)==1) return i;
	}
	return -1;
}

int inside_bounding_box(tBoundingBox box, tVector3 point){
	if (box.max.x < point.x) return false;
	if (box.min.x > point.x) return false;
	if (box.max.z < point.z) return false;
	if (box.min.z > point.z) return false;
	return true;
}