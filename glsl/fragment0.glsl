#version 410 core
out vec4 FragColor;

in vec3 outColor; //input variable from vertex shader (same name and type

void main()
{
    FragColor = vec4(outColor, 1.0);
}
