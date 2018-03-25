#version 410 core
out vec4 FragColor;

in vec4 vPos;

void main()
{
    float z = vPos.z;
    float depth = (z + 1.0) / 2.0;
    
    vec2 shiftedCoord = gl_PointCoord-vec2(0.5, 0.5);
    
    FragColor = vec4(0.8, 0.5, 1.0 - depth, pow(1.0 - (length(shiftedCoord)*2), 3.0)*(1-depth));
}
