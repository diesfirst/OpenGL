
//
//  mathShapeMain.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/11/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//
#include "mathShapes.hpp"

int mathShape(){
    glfwInit();
    GLFWwindow* window = initWindow(width, height);
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glewExperimental  = GL_TRUE;
    glewInit();
    
    Shader ourShader("../glsl/simpleMatrixVert.glsl", "../glsl/simpleFrag.glsl");

    const float res = 0.005;
    
    float* pod = makePod(res);
    //float* sphere = makeSphere(res, 1.0);
    int size = (int)(3 * 1.0/(res*res));
    float verts[size];
    int i = 0;
    while (i <= size)
    {
        verts[i] = pod[i];
        i++;
    }

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
    
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame;
        lastFrame = currentFrame;
        
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ourShader.use();
        
        //view matrix
//        glm::mat4 view = camera.GetViewMatrix();
//        ourShader.setMatrix("view", view);
//
//        //projection matrix
//        glm::mat4 projection = glm::perspe    ctive(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
//        ourShader.setMatrix("projection", projection);
//
     //   glm::mat4 model = glm::rotate(model, glm::radians(currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 model;
        model = glm::rotate(model, glm::radians(10*currentFrame), glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMatrix("model", model);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, size/3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);
    
    glfwTerminate();
    return 0;
}






