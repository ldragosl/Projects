#version 330 core

//intrare
in vec2 UV;

//iesire
out vec4 color;

uniform sampler2D samplerTextura;

void main(){
    vec4 culoare = texture( samplerTextura, UV );
    if((culoare.x < 0.5 && culoare.y < 0.5 && culoare.z < 0.5) && culoare.a == 1)
        color = vec4(0);
    
    else{
        color = culoare;
    }
}