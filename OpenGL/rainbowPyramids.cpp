//
//  rainbowPyramids.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/11/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#include "rainbowPyramids.hpp"

int rainbowPyramids(){
    glfwInit();
    GLFWwindow* window = initWindow(width, height);
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    Shader ourShader("../glsl/vertex0.glsl", "../glsl/fragment0.glsl");
    
    float vertices[]{
        //positions         //colors
        0.5f, -0.5f, 0.0f,  0.9, 0.2, 0.6,
        -0.5f, -0.5f, 0.0f, 0.5, 0.15, 0.9,
        -0.5f, 0.5f, 0.0f,  0.7, 0.7, 0.3,
        0.0f, 0.0f, -0.5f,  0.2, 0.5, 0.9
    };
    
    //create indices
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
        0, 2, 3,
        0, 1, 2
    };
    
    glm::vec3 tetPositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //bind the vertex array object first, then bind and set vertex buffers, and then configure vertex attributes
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    glEnable(GL_DEPTH_TEST);
    
    
    //render loop
    //-----------
    while (!glfwWindowShouldClose(window))
    {
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //input
        processInput(window);
        
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //activate shader
        ourShader.use();
        
        //view matrix
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMatrix("view", view);
        
        //projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
        ourShader.setMatrix("projection", projection);
        
        //render geometry
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, tetPositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMatrix("model", model);
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        }
        
        //swap buffer windows and poll io events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    //clear all previously allocated glfw resources
    glfwTerminate();
    return 0;
}






