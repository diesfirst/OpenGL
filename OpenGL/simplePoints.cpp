//
//  simplePoints.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/14/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#include "mathShapes.hpp"

int simplePoints(){
    glfwInit();
    GLFWwindow* window = initWindow(width, height);
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glewExperimental  = GL_TRUE;
    glewInit();
    
    Shader ourShader("../glsl/simpleVert.glsl", "../glsl/testFrag.glsl");
    
    float res = 0.001;
    int nPoints = 1;
    
    float verts[] = {
        0.0, 0.0, 0.0
    };
    
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    
    std::cout << "Point size range: " << GL_POINT_SIZE_RANGE << std::endl;
    
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame;
        lastFrame = currentFrame;
        
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ourShader.use();
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, nPoints);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);
    
    glfwTerminate();
    return 0;
}

