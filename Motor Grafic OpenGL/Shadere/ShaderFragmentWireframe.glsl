#version 330 core

uniform vec3 culoareWireframe = vec3(1, 0, 0);

// Ca si iesire avem valorile de intensitate ale pixelului ce corespunde acestui fragment
out vec4 color;

void main(){
    color = vec4(culoareWireframe, 1);
}