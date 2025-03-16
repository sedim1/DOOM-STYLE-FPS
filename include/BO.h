#ifndef BO_H
#define BO_H

#include <iostream>
#include <glad/glad.h>
#include <vector>

using namespace std;

//For a mesh
struct Vertex{
	vector<float> position;
	vector<float> Normal;
	vector<float> TexCoord;
};

class VAO{
	private:
		unsigned int id = 0;
	public:
		VAO(){
			glGenVertexArrays(1,&id);
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
		void Attrib(int layout,int n,int stride,int start){ //Manual assignment
			glVertexAttribPointer(layout,n,GL_FLOAT,GL_FALSE,stride * sizeof(float),(void*)(start * sizeof(float)));
			glEnableVertexAttribArray(layout);
		}
		void AttribMesh(vector<Vertex>& vertices){ //When using the vertex struct is fixed for setting a mesh
			//Positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
			//Normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(offsetof(Vertex,Normal)));
			//Texture Coordinates
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(offsetof(Vertex,TexCoord)));
		}
};

class VBO{
	private:
		unsigned int id = 0;
	public:
		VBO(){
			glGenBuffers(1,&id);
		}
		void Data(vector<float>& vertices){//MANUAL DATA SET BY USER
			glBindBuffer(GL_ARRAY_BUFFER,id);
			glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),&vertices[0],GL_STATIC_DRAW);
			//std::cout<<id<<std::endl;
		}
		void MeshData(vector<Vertex>vertices){ //when passing mesh data
			glBindBuffer(GL_ARRAY_BUFFER,id);
			glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);
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
		EBO(){
			glGenBuffers(1,&id);
		}
		void IndexData(vector<unsigned int>& indices){
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
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
