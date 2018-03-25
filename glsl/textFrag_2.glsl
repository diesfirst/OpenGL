#version 410 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

float offset = 1.0 / 500.0;
const int size = 5;
const int len = size*size;

float depth(vec2 offsets);
float[len] fillDepthArray();
float getArrayMean(float[len] array);

void main()
{
    float currDepth = depth(vec2(0.0, 0.0));
    
    vec4 currColor = texture(colorTexture, TexCoords);
    
    float depths[len] = fillDepthArray();
    float mean = getArrayMean(depths);
    if (mean < 0.0)
        mean = 0.0;
    
    mean = 4*(0.0 - mean);
    
    vec3 color  = vec3(currColor.r + mean, currColor.g + mean, currColor.b + mean);
//    vec3 color  = vec3(1.0+mean, 1.0+mean, 1.0+mean);
//    vec3 color = vec3(currColor.xyz);
    
    FragColor = vec4(color, 1.0);
}

float depth(vec2 offsets)
{
    float v = pow(texture(depthTexture, TexCoords + offsets).r, 1);
    return v;
}

//fill array column by column
// could incorporate mean getting into this,
// but better to just make that an entirely different function
float[len] fillDepthArray()
{
    float[len] array;
    int mid = size/2;
    float currDepth = depth(vec2(0.0));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int xFactor = i - mid;
            int yFactor = mid - j;
            float relDepth = depth(vec2(xFactor * offset, yFactor * offset)) - currDepth;
            int index = size * i + j;
            array[index] = relDepth;
        }
    }
    return array;
}

float getArrayMean(float[len] array)
{
    float sum = 0.0;
    for (int i = 0; i < len; i++)
    {
        sum += array[i];
    }
    float mean = sum / len;
    return mean;
}










