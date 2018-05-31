#ifndef _INCLUDE_MODELS
#define _INCLUDE_MODELS

#include "common.h"
#include "files.h"
#include "image.h"
#include "tinyobjloader.h"

#include <iostream>

typedef struct {
	GLuint vb;
	int num_triangles;
	size_t material_id;
} DrawObject;

class Model{
public:
	std::vector<DrawObject> DrawObjects;
	
	float bmin[3],bmax[3];

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t>shapes;
	std::string filename;
	std::map<std::string,GLuint>textures;
	std::vector<tinyobj::material_t>materials;

	Model::Model();
	Model::Model(std::string filename);
	int Model::Load(std::string filename);
	void Model::load_mtl(std::string filename);
	void Model::Render();
	void Model::Calc_Normal(float N[3], float v0[3], float v1[3], float v2[3]);
};

#endif // _INCLUDE_MODELS