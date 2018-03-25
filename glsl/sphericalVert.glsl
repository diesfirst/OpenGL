#version 410 core
layout (location = 0) in vec2 uv; //the position variable has attribute position 0

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float freq;
const float maxRad = 0.8;

vec3 sphereToCart(vec3 sCoords);
vec3 getRad(vec2 uv);

out vec4 vPos;

void main()
{
    vec3 sCoords = getRad(uv);
    vec3 cCoords = sphereToCart(sCoords);
    vPos = model * vec4(cCoords, 1.0);
    gl_Position = vPos;
    gl_PointSize = 10.0;

}

vec3 sphereToCart(vec3 sCoords)
{
    float x = sCoords.x * sin(sCoords.y) * cos(sCoords.z);
    float y = sCoords.x * cos(sCoords.y);
    float z = sCoords.x * sin(sCoords.y) * sin(sCoords.z);
    return vec3(x, y, z);
}

vec3 getRad(vec2 uv)
{
    float r = maxRad * cos(uv[0] * freq);
    return vec3(r, uv[0], uv[1]);
}









