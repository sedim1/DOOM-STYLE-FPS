#ifndef BO_H
#define BO_H

#include <iostream>
#include <glad/glad.h>
#include <vector>

using namespace std;

class VAO{
	private:
		unsigned int id = 0;
	public:
		VAO(){
			glGenVertexArrays(1,&id);
			std::cout<<id<<std::endl;
		}
		void Delete(){
			glDeleteVertexArrays(1,&id);
		}
		void Bind(){
			glBindVertexArray(id);
		}
		void Unbind(){
			glBindVertexArray(0);
		}
		void Attrib(int layout,int n,int stride,int start){
			glVertexAttribPointer(layout,n,GL_FLOAT,GL_FALSE,stride * sizeof(float),(void*)(start * sizeof(float)));
			glEnableVertexAttribArray(layout);
		}
};

class VBO{
	private:
		unsigned int id = 0;
	public:
		VBO(vector<float>& vertices){
			glGenBuffers(1,&id);
			glBindBuffer(GL_ARRAY_BUFFER,id);
			glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),&vertices[0],GL_STATIC_DRAW);
			std::cout<<id<<std::endl;
		}
		void Delete(){
			glDeleteBuffers(1,&id);
		}
		void Bind(){
			glBindBuffer(GL_ARRAY_BUFFER,id);
		}
		void Unbind(){
			glBindBuffer(GL_ARRAY_BUFFER,0);
		}
};

class EBO{
	private:
		unsigned int id = 0;
	public:
		EBO(vector<unsigned int>& indices){
			glGenBuffers(1,&id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
			std::cout<<id<<std::endl;
		}
		void Delete(){
			glDeleteBuffers(1,&id);
		}
		void Bind(){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
		}
		void Unbind(){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		}
};


#endif
