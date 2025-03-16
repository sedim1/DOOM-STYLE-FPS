#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "stb_image.h"
#include "Shader.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Texture{
	private:
		vector<unsigned int> id;
	public:
		Texture(){}
                ~Texture(){
                        for(int i = 0;i < id.size();i++)
                                glDeleteTextures(1,&id[i]);
                        id.clear();
                }
		void createTexture(const char* path,int e){
			unsigned int tex;
			//GenTexture
			glGenTextures(1,&tex);
			glBindTexture(GL_TEXTURE_2D,tex);
			//Set expansion mode
			if (e == 0)
        		{
           		 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        		}
       			else if (e == 1)
        		{
            			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        		}
        		else if (e == 2)
        		{
           	 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        		}
        		else if (e == 3)
       			{
            			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

            			float borderColor[] = { 0.0f,0.0f,0.0f,0.0f };
            			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        		}
			//Setting mipmaps
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//Loading image Texture
			int width, height, nrChannels;
			unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
			stbi_set_flip_vertically_on_load(true);
			 if (data)
        		{
            			GLenum format;
            			if (nrChannels == 1)
                			format = GL_RED;
            			else if (nrChannels == 3)
                			format = GL_RGB;
           			else if (nrChannels == 4)
                			format = GL_RGBA;

            			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            			glGenerateMipmap(GL_TEXTURE_2D);
				id.push_back(tex);
        		}
        		else
       	 		{
            			cout << "ERROR::COULD NOT LOAD TEXTURE "<< path << endl;
        		}
			glBindTexture(GL_TEXTURE_2D,0);
        		stbi_image_free(data);
		}
		void ViewTextures(Shader& program){
			for(int i = 0; i < id.size();i++){
				string uniform = "texture" + to_string(i+1);
				program.setInt(i,uniform.data());
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D,id[i]);
			}
                        glActiveTexture(GL_TEXTURE0);
		}
};

#endif
