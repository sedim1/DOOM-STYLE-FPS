#ifndef SHADER_H
#define SHADER_H

#include <stdlib.h>
#include <iostream>
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

char* loadShaderFile(char *filePath)
{
	char *shader = NULL;
	//OPEN FILE
	FILE *fp = fopen(filePath,"r");
	if(fp)
	{
		//Get the size of the shader file
		fseek(fp,0,SEEK_END);
		int size = ftell(fp);
		rewind(fp);
		//printf("FileSize: %d\n",size);
		//Read the shader file
		shader = (char*)malloc(sizeof(char)*size+1);
		if(!shader)
			return NULL;
		fread(shader,1,size,fp);
		shader[size] = '\0';
		//printf("ShaderFile Loaded:\n%s",shader);
		fclose(fp);
	}
	return shader;
}


class Shader{
	private:
		unsigned int id;
	public:
		Shader(){}
		Shader(std::string v,std::string f){
			int success;
			char infoLog[512];
			const char* vertexSource = loadShaderFile(v.data());
			const char* fragmentSource = loadShaderFile(f.data());
			if(vertexSource == NULL && fragmentSource == NULL){
				std::cout<<"ERROR::FILES NOT LOCATED::"<<std::endl;
			}
			unsigned int vertexShader = createShader(vertexSource,GL_VERTEX_SHADER);
			unsigned int fragmentShader = createShader(fragmentSource,GL_FRAGMENT_SHADER);
			id = glCreateProgram();
			glAttachShader(id,vertexShader);
			glAttachShader(id,fragmentShader);
			glLinkProgram(id);
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if(!success){
				glGetProgramInfoLog(id, 512, NULL, infoLog);
				std::cout<<"LINKING::ERROR::"<<infoLog<<std::endl;
			}
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}
		~Shader(){
			glDeleteProgram(id);
		}
		unsigned int createShader(const char* path,GLenum type){
			int success;
			char infoLog[512];
			unsigned int s = glCreateShader(type);
			glShaderSource(s,1,&path,NULL);
			glCompileShader(s);
			glGetShaderiv(s, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(s, 512, NULL, infoLog);
    				std::cout << "ERROR::SHADER::COMPILATION_FAILED::" << infoLog << std::endl;
			}
			return s;
		}
		void use(){
			glUseProgram(id);
		}
		//UniformVariables
		void setMatrix4f(glm::mat4 matrix,const char* uniform){
			use();
			int location = glGetUniformLocation(id,uniform);
			glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(matrix));
		}
		void setInt(int x,const char* uniform){
			use();
			int location = glGetUniformLocation(id,uniform);
			glUniform1i(location,x);
		}
};

#endif
