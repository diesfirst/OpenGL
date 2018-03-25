//
//  camera.h
//  OpenGL
//
//  Created by Michael Buckley on 3/10/18.
//  Copyright © 2018 Michael Buckley. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

//defines several options for camera movement. used as an abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

//default camera values
const float YAW         = -90.0f;
const float PITCH       = 0.0f;
const float SPEED       = 0.05f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

using namespace glm;

class Camera
{
public:
    //camera attributes
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    //euler angles
    float Yaw;
    float Pitch;
    //camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    //constructor with vectors
    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
    }
    
    //returns the view matrix calculated user Euler Angles and Lookat Matrix
    mat4 GetViewMatrix()
    {
        return lookAt(Position, Position + Front, Up);
    }
    
    //process keyboard input
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed + deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }
    
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        
        Yaw += xoffset;
        Pitch += yoffset;
        
        //make sure when pitch is out of bounds screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        
        //Update Front, Right, and Up Vectors usings the updated Euler angles
        updateCameraVectors();
    }
    
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }
    
private:
    // calculates the front vector from the camera's updated euler angles
    void updateCameraVectors()
    {
        //calculate the new front vector
        vec3 front;
        front.x = cos(radians(Yaw)) * cos(radians(Pitch));
        front.y = sin(radians(Pitch));
        front.z = sin(radians(Yaw)) * cos(radians(Pitch));
        Front = normalize(front);
        //also recalc Right and Up
        Right = normalize(cross(Front, WorldUp));
        Up = normalize(cross(Right, Front));
    }
};


#endif /* camera_h */
