//
//  mathShapes.hpp
//  OpenGL
//
//  Created by Michael Buckley on 3/11/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#ifndef mathShapes_hpp
#define mathShapes_hpp

#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "userFunctions.hpp"
#include "shaders.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <cmath>


int mathShape();
int sphereSurf();
int simplePoints();
int fboTest();
int fboAnimSphere();
int fboAnimSphere_copy();
float* makePod(float resolution, bool toCart=true);
float* makeSphere(float resolution, float radius);
float* makeSurf(float uLimit, float vLimit, float uRes, float vRes);
std::vector<glm::vec3> sphereToCart(std::vector<float> radii, std::vector<float> phis, std::vector<float> thetas);




#endif /* mathShapes_hpp */
