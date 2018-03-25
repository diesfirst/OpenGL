#version 410 core
layout (location = 0) in vec3 aPos; //the position variable has attribute position 0

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vPos;

void main()
{
    vPos = vec4(aPos, 1.0);
    gl_Position = vPos;
    gl_PointSize = 100.0;
}
