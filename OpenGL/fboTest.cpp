//
//  frameBuffer.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/15/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

//
//  simplePoints.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/14/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#include "mathShapes.hpp"

int fboTest(){
    glfwInit();
    GLFWwindow* window = initWindow(width, height);
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glewExperimental  = GL_TRUE;
    glewInit();
    
    Shader ourShader("../glsl/simpleVert.glsl", "../glsl/simpleFrag.glsl");
    Shader screenShader("../glsl/textVert.glsl", "../glsl/textFrag_2.glsl");
    
    float res = 0.001;
    int nPoints = 1;
    
//    float verts[] = {
//        0.0f, 0.0f, 0.0f
//    };
    
    float verts[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    float quadVertices[] = {
        //positions     //texCoords
        -1.0f, 1.0f,    0.0f, 1.0f,
        -1.0f, -1.0f,   0.0f, 0.0f,
        1.0f, -1.0f,    1.0f, 0.0f,
        
        -1.0f, 1.0f,    0.0f, 1.0f,
        1.0f, -1.0f,    1.0f, 0.0f,
        1.0f, 1.0f,     1.0f, 1.0f
    };
    
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    screenShader.use();
    screenShader.setInt("colorTexture", 0);
    screenShader.setInt("depthTexture", 1);
    
    //frame buffer stuff
    //------------------
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
    //create a color attachment texture
    unsigned int textureColorBuffer;
    glGenTextures(1, &textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureColorBuffer, 0);
    
    //creating a depth attachment texture
    unsigned int textureDepthBuffer;
    glGenTextures(1, &textureDepthBuffer);
    glBindTexture(GL_TEXTURE_2D, textureDepthBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);


    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureDepthBuffer, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    std::cout << "Point size range: " << GL_POINT_SIZE_RANGE << std::endl;
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame;
        lastFrame = currentFrame;
        
        processInput(window);
        
        //render
        //bind to frame buffer
        
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ourShader.use();
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        //bind back to default
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureDepthBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);
    
    glfwTerminate();
    return 0;
}


