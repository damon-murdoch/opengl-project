#ifndef _INCLUDE_MODELS
#define _INCLUDE_MODELS

#include "common.h"
//#include "OBJ_Loader.h"

class GameObject{
public:
	
	bool active;

	float weight;

	tBoundingBox bounding_box;
	//objl::Loader model;

	GameObject::GameObject();
	GameObject::GameObject(char*filename);

	void GameObject::Generate_Bounding_Box();
	void GameObject::Render();

};

#endif // _INCLUDE_MODELS