#ifndef _INCLUDE_PHYSICS
#define _INCLUDE_PHYSICS

#include "qu3e/q3.h"

class PhysicsEnvironment{
	
	PhysicsEnvironment::q3Scene scene;
	
	PhysicsEnvironment::PhysicsEnvironment();
	PhysicsEnvironment::PhysicsEnvironment(float timestep);
	
	void PhysicsEnvironment::Create_Scene(float timestep);
};

class PhysicsObject {
private:
	q3BodyDef body_def;
	PhysicsEnvironment * environment;
public:
	q3Body * body;
	q3Transform transform;
};

#endif //_INCLUDE_PHYSICS