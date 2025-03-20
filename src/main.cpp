#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "BO.h"
#include "MODEL_LOADER/Mesh.h"
#include "MODEL_LOADER/Model.h"
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 640;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

    std::vector<float>vertices = {
	    //Position	     UV
	    -0.5f,0.5f,0.0f, 0.0f,0.0f,//top-left
	    0.5f,0.5f,0.0f, 1.0f,0.0f,//top-right
	    -0.5f,-0.5f,0.0f, 0.0f,1.0f,//bottom-left
	    0.5f,-0.5f,0.0f, 1.0f,1.0f,//top-left
    };
    std::vector<unsigned int>indices = {  // note that we start from 0!
        0, 1, 2,  // first Triangle
        1, 2, 3,   // second Triangle
    };

    Shader program = Shader("SHADERS/vertex.vs","SHADERS/fragment.fs");
    Shader primitive = Shader("SHADERS/primitive.vs","SHADERS/primitive.fs");

    Model Luigi("MODELS/Rouge/Rouge.gltf");
    //Cube cube(5.0f,5.0f,5.0);

    Camera camera = Camera();
    camera.position.z = -1.5f;
    camera.position.y = 1.0f;
    camera.updateProjection(SCR_WIDTH,SCR_HEIGHT,program);
    camera.updateProjection(SCR_WIDTH,SCR_HEIGHT,primitive);

    glEnable(GL_DEPTH_TEST);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        camera.spectateMode(window);
        // render
        // ------
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
	program.use();
        camera.updateView(program);
        Luigi.Draw(program);
        primitive.use();
        camera.updateView(primitive);
        //cube.drawMesh(primitive);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
