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
			char* vertexSource = loadShaderFile(v.data());
			char* fragmentSource = loadShaderFile(f.data());
			if(vertexSource == NULL && fragmentSource == NULL){
				std::cout<<"ERROR::FILES NOT LOCATED::"<<std::endl;
				return;
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
				return;
			}
			std::cout<<"::SHADER PROGRAM CREATED SUCCESSFULLY::"<<std::endl;
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			free(vertexSource);
			free(fragmentSource);
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
			if(location!=-1)
				glUniform1i(location,x);
			else{
				std::cout<<"ERROR::Could not assign "<<x<<" to "<<uniform<<" because it is not found::"<<std::endl;
			}
		}
		void setBool(bool x,const char* uniform){
			use();
			int location = glGetUniformLocation(id,uniform);
			if(x == true)
				glUniform1i(location,1);
			else
				glUniform1i(location,0);
		}
		void setVector4f(glm::vec4 v,const char* uniform){
			use();
			int location = glGetUniformLocation(id,uniform);
			glUniform4f(location,v.x,v.y,v.z,v.w);
		}
};

#endif
