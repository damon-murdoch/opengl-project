#include "shader.h"

Shader::Shader(){
}

Shader::Shader(const char*vertex_path,const char*fragment_path){
	Shader::load(vertex_path,fragment_path);
}

void Shader::use(){
	glUseProgram(Shader::ID);
}

void Shader::set_bool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}
void Shader::set_int(const std::string &name, int value) const{
	glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}
void Shader::set_float(const std::string &name, float value) const{
	glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}

void Shader::load(const GLchar * vertex_path , const GLchar * fragment_path){

	std::string vertex_code , fragment_code;
	
	std::ifstream v_shader_file , f_shader_file;

	v_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	f_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	try {

		v_shader_file.open(vertex_path);
		f_shader_file.open(fragment_path);

		std::stringstream v_shader_stream , f_shader_stream;

		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();

		v_shader_file.close();
		f_shader_file.close();

		vertex_code = v_shader_stream.str();
		fragment_code = f_shader_stream.str();

	}
	catch (std::ifstream::failure e) {
		printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
		printf("%s,%s",vertex_path,fragment_path);
	}

	printf("Vertex Shader: %s\nFragment Shader: %s",fragment_code,vertex_code);

	const char * v_shader_code = vertex_code.c_str();
	const char * f_shader_code = fragment_code.c_str();

	GLuint vertex, fragment;

	GLint success;

	char info_log[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex,1,&v_shader_code,NULL);
	
	glCompileShader(vertex);
	
	glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
	
	if(!success){
		glGetShaderInfoLog(vertex,512,NULL,info_log);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n",info_log );
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragment,1,&f_shader_code,NULL);
	
	glCompileShader(fragment);
	
	glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
	
	if(!success){
		glGetShaderInfoLog(vertex,512,NULL,info_log);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %s\n",info_log );
	};

	Shader::ID = glCreateProgram();

	glAttachShader(ID,vertex);
	glAttachShader(ID,fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID,GL_LINK_STATUS,&success);
	if(!success){
		glGetProgramInfoLog(ID,512,NULL,info_log);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n",info_log );
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}