#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <cmath>
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
		void setUpPrimitive(vector<float>& data,vector<unsigned int>& faces){
			vao.Bind();
			vbo.Data(data);
			ebo.IndexData(faces);
			vao.Attrib(0,3,5,0); //Positions
			vao.Attrib(1,2,5,3); //Texture Coordinates
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
			setUpPrimitive(buffer,indices);
		}
};

class Cube : public Mesh{
	public:
		vector<float>buffer={
		       -1.0f,1.0f,1.0f,  0.0f, 0.0f,
		        1.0f,1.0f,1.0f,  1.0f, 0.0f,
		       -1.0f,-1.0f,1.0f, 0.0f, 1.0f,
		        1.0f,-1.0f,1.0f, 1.0f, 1.0f,
		       -1.0f,1.0f,-1.0f, 0.0f, 0.0f,
		       -1.0f,1.0f, 1.0f, 1.0f, 0.0f,
		       -1.0f,-1.0f,-1.0f, 0.0f, 1.0f,
		       -1.0f,-1.0f,1.0f, 1.0f, 1.0f,
		       1.0f,1.0f,-1.0f, 0.0f, 0.0f,
		       1.0f,1.0f, 1.0f, 1.0f, 0.0f,
		       1.0f,-1.0f,-1.0f, 0.0f, 1.0f,
		       1.0f,-1.0f,1.0f, 1.0f, 1.0f,
		       -1.0f,1.0f,-1.0f,  0.0f, 0.0f,
		        1.0f,1.0f,-1.0f,  1.0f, 0.0f,
		       -1.0f,-1.0f,-1.0f, 0.0f, 1.0f,
		        1.0f,-1.0f,-1.0f, 1.0f, 1.0f,
		       -1.0f,1.0f,-1.0f,  0.0f, 0.0f,
		        1.0f,1.0f,-1.0f,  1.0f, 0.0f,
		       -1.0f,1.0f,1.0f,  0.0f, 1.0f,
		        1.0f,1.0f,1.0f,   1.0f, 1.0f,
		       -1.0f,-1.0f,-1.0f,  0.0f, 0.0f,
		        1.0f,-1.0f,-1.0f,  1.0f, 0.0f,
		       -1.0f,-1.0f,1.0f,   0.0f, 1.0f,
		        1.0f,-1.0f,1.0f,   1.0f, 1.0f
		};

		Cube(float x, float y, float z){
			vector<unsigned int>faces = {
				0,1,2,
				1,2,3,
				4,5,6,
				5,6,7,
				8,9,10,
				9,10,11,
				12,13,14,
				13,14,15,
				16,17,18,
				17,18,19,
				20,21,22,
				21,22,23,
			};
			for(int i = 0; i < buffer.size();i+=5){
				buffer[i] *= x;
				buffer[i+1] *= y;
				buffer[i+2] *= z;
			}
			indices = faces;
			textures.push_back(Texture("TEXTURES/sampler.jpg",0,0));
			setUpPrimitive(buffer,indices);
		}
};

class UvSphere : public Mesh{
	public:
		vector<float>buffer;
		UvSphere(float radious,int nSlices,int nStacks){ //Slices = longitudes, Stacks += latitudes
			float stackStep = 1.0f/(float)nStacks;
			float sliceStep = 1.0f/(float)nSlices;
			float angleStep = 90.0f/(float)nStacks;
			float angleDegree = 0.0f;
			vector<float> uv;
			vector<float>topVertex = {0.0f,1.0f,0.0f};
			vector<float>bottomBottom = {0.0f,-1.0f,0.0f};
			vector<float> top;
			vector<float> bottom;
			//Generate the vertices the sphere is going to have (vertices of top and botom stacks)
			for(float y = 0.0f; y < 1.0f; y += stackStep)
			{
				//Calculate radious
				float nRadius;
				if(y == 0.0f){
					nRadius = 1.0f;
				}
				else{
					nRadious = y / tan(radians(angleDegree));
				}
				//Calculate vertices of current stack with parametric ecuation of the circle
				for(float t = 0; t < 1.0f;t += sliceStep){
					float x = (cos(t) * nRadius) * radious;
					float z = (sin(t) * nRadius) * radious;
					top.push_back(x);top.push_back(y);top.push_back(z);
					bottom.push_back(-x);bottom.push_back(-y);bottom.push_back(-z);
				}
				angleDegree+=angleStep;
			}
		}
};
#endif
