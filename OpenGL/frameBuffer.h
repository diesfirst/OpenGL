//
//  frameBuffer.h
//  OpenGL
//
//  Created by Michael Buckley on 3/16/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#ifndef frameBuffer_h
#define frameBuffer_h

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>
#include "userFunctions.hpp"

class Framebuffer{

private:
    
    unsigned int FBO;
    unsigned int texture_color;
    unsigned int texture_depth;
    
public:
    
    Framebuffer(){
        //GenerateFBO(800, 600); //initial width and height;
    }
    
    ~Framebuffer(){
        destroy();
    }
    
private:
    
    void destroy()
    {
        glDeleteFramebuffers(1, &FBO);
        glDeleteTextures(1, &texture_color);
        glDeleteTextures(1, &texture_depth);
    }
    
    //generate an empty color texture with 4 channels (RGBA8) using bilinear filtering
    void GenerateColorTexture(unsigned int width, unsigned int height)
    {
        glGenTextures(1, &texture_color);
        glBindTexture(GL_TEXTURE_2D, texture_color);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    }
    
    void GenerateDepthTexture(unsigned int width, unsigned int height)
    {
        glGenTextures(1, &texture_depth);
        glBindTexture(GL_TEXTURE_2D, texture_depth);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    }
    
public:
    
    void GenerateFBO(unsigned int width, unsigned int height)
    {
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        
        GenerateColorTexture(width, height);
        GenerateDepthTexture(width, height);
        
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_color, 0);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_depth, 0);
        
//        drawbuffer.push_back(GL_COLOR_ATTACHMENT0 + attachment_index_color_texture);
//        glDrawBuffers(drawbuffer.size(), &drawbuffer[0]);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            std::cout << "ERROR GOOD SIR! Frame buffer is not complete! D:" << std::endl;
            std::cin.get();
            std::terminate();
        }
        
        //unbind framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    //return color texture from the framebuffer
    unsigned int getColorTexture()
    {
        return texture_color;
    }
    
    //return depth texture from the framebuffer
    unsigned int getDepthTexture()
    {
        return texture_depth;
    }
    
    //resize window
    void resize(unsigned int width, unsigned int height)
    {
        destroy();
        GenerateFBO(width, height);
    }
    
    //bind framebuffer to pipeline. We will  call this method in the render loop
    void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        //this can be moved in GenerateFBO function but
        //we have to put here in case of a MRT functionality
    }

    //unbind framebuffer from pipeline. We will call this method in the render loop
    void unbind()
    {
        //0 is the default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    
};


#endif /* frameBuffer_h */






