#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

enum Type{
	PERSPECTIVE,
	ORTHOGONAL,
};

class Camera{
	public:
		float fov;
		float Near;
		float Far;
		float yaw;
		float pitch;
		float roll;
		mat4 view;
		mat4 projection;
		vec3 position;
		vec3 direction;
		vec3 up;
		enum Type projectionType;
		Camera(){
			fov = 45.0f;
			position = vec3(0.0f,0.0f,0.0f);
			direction = vec3(0.0f,0.0f,-1.0f);
			up = vec3(0.0f,1.0f,0.0f);
			view = mat4(1.0f);
			projection = mat4(1.0f);
			projectionType = PERSPECTIVE;
			Near = 0.1f;
			Far = 100.0f;
			yaw = pitch = roll = 0.0f;
			yaw = -90.0f;
		}
		void updateProjection(int w,int h,Shader& program)
		{
			//Update projection matrix according to the projection type
			if(projectionType==PERSPECTIVE)
				projection = perspective(radians(fov),(float)w/(float)h,Near,Far);
			else if (projectionType==ORTHOGONAL)
				projection = ortho(0.0f,(float)w,0.0f,(float)h,Near,Far);
			//Update the projection uniform
			program.setMatrix4f(projection,"projection");
		}
		void updateView(Shader& program){
			view = lookAt(position,position+direction,up);
			program.setMatrix4f(view,"view");
		}
		void spectateMode(GLFWwindow *w)
		{
			float steps = 0.1f;

			if(glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS)
				yaw -= steps * 50;
			if(glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS)
				yaw += steps * 50;
			if(glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS){
				pitch += steps * 50;
			}
			if(glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS){
				pitch -= steps * 50;
			}

			if(pitch > 89.0f)
				pitch =  89.0f;
			if(pitch < -89.0f)
				pitch = -89.0f;
			//direction rotation here
			direction.x = cos(radians(yaw)) * cos(radians(pitch));
			direction.y = sin(radians(pitch));
			direction.z = sin(radians(yaw)) * cos(radians(pitch));
			direction = normalize(direction);

			if(glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
				position += (direction * steps);
			if(glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
				position -= (direction * steps);
			if(glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
				position += ((cross(direction,up)) * steps);
			if(glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
				position -= ((cross(direction,up)) * steps);
			if(glfwGetKey(w, GLFW_KEY_E) == GLFW_PRESS)
				position.y += steps;
			if(glfwGetKey(w, GLFW_KEY_Q) == GLFW_PRESS)
				position.y -= steps;
		}
};

#endif
