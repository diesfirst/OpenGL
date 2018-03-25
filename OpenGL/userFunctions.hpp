//
//  userFunctions.hpp
//  OpenGL
//
//  Created by Michael Buckley on 3/10/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#ifndef userFunctions_hpp
#define userFunctions_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "frameBuffer.h"
#include <iostream>

extern unsigned int width;
extern unsigned int height;

extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;

//timing
extern float deltaTime;
extern float lastFrame;

extern Framebuffer fbo;

extern GLFWwindow* initWindow(int scr_width, int scr_height);
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);
extern void processInput(GLFWwindow *window);

#endif /* userFunctions_hpp */


