#ifndef INCLUDE_SHADER_H
#define INCLUDE_SHADER_H

#include "common.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int ID;
	
	Shader::Shader();

	Shader::Shader(const GLchar * vertex_path, const GLchar * fragment_path);
	
	VOID Shader::use();

	void Shader::load(const char*vertex_path,const char*fragment_path);

	void Shader::set_bool(const std::string &name, bool value) const;
	void Shader::set_int(const std::string &name, int value) const;
	void Shader::set_float(const std::string &name, float value) const;
};

#endif