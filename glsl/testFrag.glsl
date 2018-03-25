#version 410 core
out vec4 FragColor;

void main()
{
    vec2 shiftedCoord = gl_PointCoord-vec2(0.5, 0.5);
    FragColor = vec4(1.0, length(shiftedCoord), 1.0, pow(1.0 - (length(shiftedCoord)*2), 3.0));
}
