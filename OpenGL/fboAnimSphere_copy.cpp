//
//  fboAnimSphere_copy.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/17/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

//
//  fboAnimSphere.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/16/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.

#include "mathShapes.hpp"

int fboAnimSphere_copy(){
    glfwInit();
    GLFWwindow* window = initWindow(width, height);
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glewExperimental  = GL_TRUE;
    glewInit();
    
    Shader ourShader("../glsl/sphericalVert.glsl", "../glsl/surfFrag_2.glsl");
    Shader screenShader("../glsl/textVert.glsl", "../glsl/textFrag_2.glsl");
    
    float res = 0.001;
    
    float* uvs = makeSurf(2 * M_PI, M_PI, res, res);
    int size = (int)(2 * 1.0/(res*res));
    float verts[size];
    int i = 0;
    while (i < size){
        verts[i] = uvs[i];
        i++;
        
    }
    
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
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
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
    
    fbo.GenerateFBO(width, height);
    unsigned int textureColorBuffer = fbo.getColorTexture();
    unsigned int textureDepthBuffer = fbo.getDepthTexture();
    
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
        
        //render
        //bind to frame buffer
        
        fbo.bind();
        glEnable(GL_DEPTH_TEST);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ourShader.use();
        
        float freq = 2*(cos(currentFrame/4));
        ourShader.setFloat("freq", freq);
        
        glm::mat4 model;
        model = glm::rotate(model, glm::radians(20*currentFrame), glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMatrix("model", model);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, size/2);
        
        //bind back to default
        fbo.unbind();
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




