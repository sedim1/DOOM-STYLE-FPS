#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include "BO.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;

class Mesh{
	public:
		VAO vao;
		VBO vbo;
		EBO ebo;
		vector<Vertex>vertices;
		vector<unsigned int>indices;
		vector<Texture>textures;
		void setUpMesh(){
			vao.Bind();
			vbo.MeshData(vertices);
			ebo.IndexData(indices);
			vao.AttribMesh(vertices);
			vao.Unbind();
			vbo.Unbind();
			ebo.Unbind();
		}
		Mesh(){}
		Mesh(vector<Vertex>& vertices,vector<unsigned int>& indices,vector<Texture>& textures){
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;
			setUpMesh();
		}
		void drawMesh(Shader& program){
			if(textures.size()!=0){
				for(int i = 0; i < textures.size();i++){
					string uniform = "texture" + to_string(i);
					textures[i].texUnit(program,uniform.data(),i);
					textures[i].BindTexture(program);
				}
			}
			vao.Bind();
			glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
			vao.Unbind();
		}
};

//Mesh Primitives - this primitives are just for testing and debuggging
//Primitive buffer structure (Positions UV), so basically these primitives will only have position and texture
class Plane : public Mesh{
	public:
		vector<float>buffer={
			//Positions       //TexCoords
			-1.0f,0.0f,1.0f,   0.0f, 0.0f,
			 1.0f,0.0f,1.0f,   1.0f, 0.0f,
			-1.0f,0.0f,-1.0f,  0.0f, 1.0f,
			 1.0f,0.0f,-1.0f,  1.0f, 1.0f, 
		};
		Plane(float x,float z){
			//Set indices
			vector<unsigned int> faces = {0,1,2,1,2,3};
			indices = faces;
			//Define buffer data
			for(int i = 0; i < buffer.size();i += 5){
				buffer[i] *= x;
				buffer[i+2] *= z;
			}
			textures.push_back(Texture("TEXTURES/sampler.jpg",0,0));
			setUpMesh();
		}

		void setUpMesh(){
			vao.Bind();
			vbo.Data(buffer);
			ebo.IndexData(indices);
			vao.Attrib(0,3,5,0);
			vao.Attrib(1,2,5,3);
			vao.Unbind();
			vbo.Unbind();
			ebo.Unbind();
		}
};
#endif
