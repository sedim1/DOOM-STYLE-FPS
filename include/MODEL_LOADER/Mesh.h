#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include "BO.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;

class Mesh{
	private:
		VAO vao;
		VBO vbo;
		EBO ebo;
	public:
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
		Mesh(vector<Vertex>& vertices,vector<unsigned int>& indices,vector<Texture>& textures){
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;
			setUpMesh();
		}
		void drawMesh(Shader& program){
			for(int i = 0; i < textures.size();i++){
				string uniform = "texture" + to_string(i);
				textures[i].texUnit(program,uniform.data(),i);
				textures[i].BindTexture(program);
			}
			vao.Bind();
			glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
			vao.Unbind();
		}
};

#endif
