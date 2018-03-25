//
//  userFunctions.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/10/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#include "userFunctions.hpp"

unsigned int width = 800;
unsigned int height = 600;
//
////camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = width / 2.0f;
float lastY = width / 2.0f;
bool firstMouse = true;

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//fbo
Framebuffer fbo;

GLFWwindow* initWindow(int scr_width, int scr_height)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Make Window object
    GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, "The babies are eating", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        }
    
    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int scr_width, int scr_height)
{
    glViewport(0, 0, scr_width, scr_height);
    fbo.resize(scr_width, scr_height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}





