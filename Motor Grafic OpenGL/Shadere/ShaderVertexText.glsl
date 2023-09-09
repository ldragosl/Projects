#version 330 core

// Date de intrare din c++
layout(location = 0) in vec2 pozitiePunct2D;
layout(location = 1) in vec2 uvPunct;

// Acestea vor fii interpolate pentru fiecare fragment
out vec2 UV;

void main(){
    gl_Position =  vec4(pozitiePunct2D,0,1);

    UV = uvPunct;
}