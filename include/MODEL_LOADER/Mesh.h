#ifndef MESH_H
#define MESH_H

#include <vector>
#include "BO.h"
#include "Texture.h"

using namespace std;

struct Vertex{
	vector<float> position;
	vector<float> Normal;
	vector<float> TexCoord;
};

class Mesh{
	private:
		VAO vao;
		VBO vbo;
		EBO ebo;
	public:
		vector<Vertex>vertices;
		vector<unsigned int>indices;
		Texture texture;
		setUpMesh(){
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
};

#endif
