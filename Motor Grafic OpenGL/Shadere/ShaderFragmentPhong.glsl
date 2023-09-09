#version 330 core

// valorile acestea sunt interpolate automat dupa outputurile vertex shader-ului
in vec2 UV;
//pozitia camerei - vectorul de la fragment la camera normalizat
in vec3 PozitieCamera;
//directia luminii - vectorul de la fragment la lumina normalizat
in vec3 DirectieLumina;
in float DistantaLumina;

// Ca si iesire avem valorile de intensitate ale pixelului ce corespunde acestui fragment
out vec4 color;

// Aceste valori raman constante pentru tot apelul de randare
uniform sampler2D SamplerTextura;
uniform sampler2D SamplerTexturaNormala;
uniform float IntensitateLumina;
uniform vec3 CuloareLumina = vec3(1,1,1);
uniform vec3 IntensitateLuminaAmbient = vec3(0.4);
uniform vec3 CuloareReflexie = vec3(1,1,1);
uniform float IntensitateReflexie = 20.f;

//lumina se degradeaza odata cu distanta, insa nu exista un singur mod de a decide rapididatea
float functieDegradareLuminaExponentiala(float Distanta){
    float DistantaPatrata = Distanta * Distanta;
    return 1.0 / DistantaPatrata;
}
float functieDegradareLuminaLiniara(float Distanta){
    return 1.0 / Distanta;
}

void main(){
    // normala, asa cum este ea citita din textura, adusa pe toate cele 3 axe in spatiul (-1, 1)
    vec3 VecNormal = normalize(texture( SamplerTexturaNormala, UV ).rgb * 2.0 - 1.0);

    // cei 2 vectori sunt normalizati -> produsul lor scalar este cosinusul dintre cei 2 vectori.
    // daca lumina "bate" perpendicular pe obiect, rezultatul va fii mai aproape de 1. In caz contrar, 
    // cu cat unghiul cu care lovesc razele de lumina obiectul este mai mic, cu atat produsul se apropie de 0
    float UnghiLuminaPeSuprafata = clamp( dot( VecNormal, DirectieLumina ), 0,1 );

    vec3 DirectieCamera = normalize(PozitieCamera);

    vec3 ReflexieLumina = reflect(-DirectieLumina, VecNormal);

    // daca jucatorul se uita direct in directia reflexiei, valoarea produsului vectorial al camerei cu raza de soare reflectata va fii 1
    // daca jucatorul se uita intr-o directie perpendiculara reflexiei razei luminoase, valoarea produsului vectorial al camerei cu raza de soare reflectata va fii 0 
    // cei 2 vectori sunt normalizati -> produsul lor scalar este cosinusul dintre cei 2 vectori.
    float UnghiCameraReflexie = clamp( dot( DirectieCamera, ReflexieLumina ), 0,1 );

    // culoarea bruta, asa cum este ea stocata in textura, pentru acest punct
    vec3 CuloareBaza = texture( SamplerTextura, UV ).rgb;
    // culoarea de "baza", care e afisata in locurile unde nu exista lumina deloc
    vec3 CuloareAmbientala = IntensitateLuminaAmbient * CuloareBaza;

    color = vec4(CuloareAmbientala +
        CuloareBaza * CuloareLumina * IntensitateLumina * UnghiLuminaPeSuprafata * functieDegradareLuminaExponentiala(DistantaLumina) + // difuza
        CuloareReflexie * CuloareLumina * IntensitateReflexie * pow(UnghiCameraReflexie,5) * functieDegradareLuminaExponentiala(DistantaLumina), 1); // specularitatea
}