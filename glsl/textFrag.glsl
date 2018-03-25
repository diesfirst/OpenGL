#version 410 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

float offset = 1.0 / 300.0;

float depth(vec2 offsets);
//vec3 color();
mat3 getDepthMatrix();
float meanNearDepths(mat3 depthMatrix);

void main()
{
    float currDepth = depth(vec2(0.0, 0.0));
    
    vec4 currColor = texture(colorTexture, TexCoords);
    
    mat3 depths = getDepthMatrix();
    float mean = meanNearDepths(depths);
    if (mean < 0.0)
        mean = 0.0;
    
    mean = 3*(0.0 - mean);
    
//    vec3 color  = vec3(currColor.r + mean, currColor.g + mean, currColor.b + mean);
    vec3 color  = vec3(1.0 + mean, 1.0 + mean, 1.0 + mean);

    
    FragColor = vec4(color, 1.0);
}

float depth(vec2 offsets)
{
    float v = pow(texture(depthTexture, TexCoords + offsets).r, 1);
    return v;
}

mat3 getDepthMatrix()
{
    mat3 depthMatrix;
    float currdepth = depth(vec2(0.0, 0.0));
    depthMatrix[0][0] = depth(vec2(-offset, offset)) - currdepth;
    depthMatrix[0][1] = depth(vec2(-offset, 0.0)) - currdepth;
    depthMatrix[0][2] = depth(vec2(-offset, -offset)) - currdepth;
    depthMatrix[1][0] = depth(vec2(0.0, offset)) - currdepth;
    depthMatrix[1][1] = depth(vec2(0.0, 0.0)) - currdepth;
    depthMatrix[1][2] = depth(vec2(0.0, -offset)) - currdepth;
    depthMatrix[2][0] = depth(vec2(offset, offset)) - currdepth;
    depthMatrix[2][1] = depth(vec2(offset, 0.0)) - currdepth;
    depthMatrix[2][2] = depth(vec2(offset, -offset)) - currdepth;
    return depthMatrix;
}

float meanNearDepths(mat3 depthMatrix)
{
    float sum = 0.0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sum += depthMatrix[i][j];
        }
    }
    float mean = sum / 9.0;
    return mean;
}













