#version 330 core

// Date de intrare din c++
layout(location = 0) in vec3 pozitiePunct3D;

// Matricea de conversie din baza locala modelului (baza in care este fisierul asa cum a fost el importat) in baza proiectiei (a ecranului)
uniform mat4 matMVP;

void main(){
    // Pozitia punctului 3D, convertit din baza modelului in baza proiectiei pe ecran
    gl_Position =  matMVP * vec4(pozitiePunct3D,1);

}