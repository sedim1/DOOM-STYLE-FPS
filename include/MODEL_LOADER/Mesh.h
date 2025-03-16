#ifndef MESH_H
#define MESH_H

#include <vector>
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
		Texture texture;
		void setUpMesh(){
			vao.Bind();
			vbo.MeshData(vertices);
			ebo.IndexData(indices);
			vao.AttribMesh(vertices);
			vao.Unbind();
			vbo.Unbind();
			ebo.Unbind();
		}
		Mesh(vector<Vertex>& vertices,vector<unsigned int>& indices,Texture& texture){
			this->vertices = vertices;
			this->indices = indices;
			this->texture = texture;
			setUpMesh();
		}
		void drawMesh(Shader& program){
			program.use();
			texture.ViewTextures(program);
			vao.Bind();
			glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
			vao.Unbind();
		}
};

#endif
