//
//  mathShapes.cpp
//  OpenGL
//
//  Created by Michael Buckley on 3/11/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#include "mathShapes.hpp"

float* makeSurf(float uLimit, float vLimit, float uRes, float vRes)
{
    std::vector<glm::vec2> coords;
    
    float uStep = uLimit * uRes;
    float vStep = vLimit * vRes;
    float u = 0.0;
    float v = 0.0;
    
    while ( u < uLimit )
    {
        while ( v < vLimit )
        {
            coords.push_back(glm::vec2(u, v));
            v += vStep;
        }
        v = 0.0;
        u += uStep;
    }
    
    float* flatArray = &coords[0].x;
    
    return flatArray;
}


float* makePod(float resolution, bool toCart)
{
    
    std::vector<float> radii;
    std::vector<float> thetas;
    std::vector<float> phis;
    
    float freq = 1.0;
    
    float uStep = M_PI * 2 * resolution;
    float vStep = M_PI * resolution;
    float u = 0.0;
    float v = 0.0;
    while (u < M_PI)
    {
        while (v < 2 * M_PI){
            radii.push_back(sin(u * freq));
            phis.push_back(u);
            thetas.push_back(v);
            v += vStep;
        }
        v = 0.0;
        u += uStep;
    }
    
    std::vector<glm::vec3> cCoords;
    if (toCart)
        cCoords = sphereToCart(radii, phis, thetas);
    else
        for (int i = 0; i < radii.size(); i++)
        {
            cCoords.push_back(glm::vec3(radii[i],thetas[i],phis[i]));
        }

    float* flatArray = &cCoords[0].x;

    return flatArray;
}

float* makeSphere(float resolution, float radius)
{
    std::vector<float> radii;
    std::vector<float> thetas;
    std::vector<float> phis;
    
    float uStep = M_PI * 2 * resolution;
    float vStep = M_PI * resolution;
    float u = 0.0;
    float v = 0.0;
    while (u < (2 * M_PI))
    {
        while (v < M_PI){
            radii.push_back(radius);
            phis.push_back(u);
            thetas.push_back(v);
            v += vStep;
        }
        v = 0.0;
        u += uStep;
    }
    
    std::vector<glm::vec3> cCoords = sphereToCart(radii, phis, thetas);
    
    float* flatArray = &cCoords[0].x;
    
    return flatArray;
    
}

std::vector<glm::vec3> sphereToCart(std::vector<float> radii, std::vector<float> phis, std::vector<float> thetas)
{
    std::vector<glm::vec3> cCoords;
    int i = 0;
    while (i < radii.size())
    {
        float x = radii[i]*sin(thetas[i])*cos(phis[i]);
        float y = radii[i]*cos(thetas[i]);
        float z = radii[i]*sin(thetas[i])*sin(phis[i]);
        cCoords.push_back(glm::vec3(x,y,z));
        i++;
    }
    cCoords.push_back(glm::vec3(NULL,NULL,NULL));
    
    return cCoords;
}










