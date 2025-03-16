#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec2 aTex;
out vec2 texCoord;
  
void main()
{
    gl_Position = vec4(aPos, 1.0f);
    texCoord = aTex;
}   
