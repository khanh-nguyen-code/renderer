#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"renderer.h"

namespace renderer {
shader::shader(const std::string& v_shader, const std::string& f_shader) {
	m_vertex_shader = v_shader;
	m_fragment_shader = f_shader;
	m_renderer_id = create_shader();
}
shader::~shader() {
	glDeleteProgram(m_renderer_id);
}


void shader::bind() const {
	glUseProgram(m_renderer_id);
}
void shader::unbind() const {
	glUseProgram(0);
}

void shader::set_uniform_1i(const std::string& name, int value) {
	glUniform1i(get_uniform_location(name), value);
}
void shader::set_uniform_1f(const std::string& name, float value) {
	glUniform1f(get_uniform_location(name), value);
}
void shader::set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

uint32_t shader::create_shader() {
	uint32_t program =  glCreateProgram();
	uint32_t vs = compile_shader(GL_VERTEX_SHADER);
	uint32_t fs = compile_shader(GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	glLinkProgram(program);
	glValidateProgram(program);


	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
uint32_t shader::compile_shader(uint32_t type) {
	uint32_t id = glCreateShader(type);
	const char *src;
	if (GL_VERTEX_SHADER == type)
		src = m_vertex_shader.c_str();
	else if (GL_FRAGMENT_SHADER == type)
		src = m_fragment_shader.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout<<"Failed to compile"<<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<<" shader!"<<std::endl;
		std::cout<<message<<std::endl;
		glDeleteShader(id);
		delete[] message;
		return 0;
	}
	return id;
}
int shader::get_uniform_location(const std::string& name) {
	if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
		return m_uniform_location_cache[name];

	int location = glGetUniformLocation(m_renderer_id, name.c_str());
	if (location == -1)
		std::cout<<"Warning: uniform "<<name<<" does not exist!"<<std::endl;
       
	m_uniform_location_cache[name] = location;	
	return location;
}
}

