#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<iostream>
#include<GLFW/glfw3.h>
#include<GLAD/glad.h>
#include<string>

std::string get_file_contents(const char* filename);

class Shader {

private: 
public:

	unsigned int ID;
	Shader(const char* vertexfile, const char* fragmentfile);
	~Shader();

	void Activate();
	



};





#endif 


