#version 330 core

// Date de intrare din c++
layout(location = 0) in vec3 pozitiePunct3D;
layout(location = 1) in vec2 uvPunct;
layout(location = 2) in vec3 normalaPunct;
layout(location = 3) in vec3 tangentaPunct;
layout(location = 4) in vec3 bitangentaPunct;

// Acestea vor fii interpolate pentru fiecare fragment
out vec2 UV;
out vec3 DirectieLumina;
out vec3 PozitieCamera;
out float DistantaLumina;

// Aceste valori raman constante pentru tot apelul de randare

// Matricea de conversie din baza locala modelului (baza in care este fisierul asa cum a fost el importat) in baza proiectiei (a ecranului) (Model-Vizualizare-Proiectie)
uniform mat4 matMVP;
// Matricea vizualizare face conversia de la baza canonica (centrul scenei) la baza in care este localizata camera
uniform mat4 matVizualizare;
// Matricea model face tranzitia de la baza modelului 3D la baza canonica (centrul scenei)
uniform mat4 matModel;
// Pozitia sursei de lumina
uniform vec3 PozitieBec;
// Coltul dreapta-sus al matricei MVP (adica matricea MV fara translatie)
uniform mat3 MV;
// Pentru distorsionarea UV-ului
uniform vec2 scalaUV;

void main(){
    // Pozitia punctului 3D, convertit din baza modelului in baza proiectiei pe ecran
    gl_Position =  matMVP * vec4(pozitiePunct3D,1);
    UV = uvPunct * scalaUV;

    //la importarea din fisierul obj, normalele, tangentele si bitangentele nu au fost normalizate (vezi implementarea importatorului obj)
    vec3 vertexNormal_cameraspace = MV * normalize(normalaPunct);
    vec3 vertexTangent_cameraspace = MV * normalize(tangentaPunct);
    vec3 vertexBitangent_cameraspace = MV * normalize(bitangentaPunct);

    // acum ca acestea au fost normalizate, creem matricea Tangenta-Bitangenta-Normala
    // aceasta este deasemenea o matrice de schimbare de baza
    mat3 TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    ));

    // distanta de la punctul 3D la sursa de lumina
    DistantaLumina = distance((matModel * vec4(pozitiePunct3D,1)).xyz, PozitieBec);

    // Trecem punctul 3D din spatiul (baza) modelului 3D in baza locatiei camerei (fara proiectare pe ecran)
    vec3 PozitiePunctFataDeCamera = ( matVizualizare * matModel * vec4(pozitiePunct3D,1)).xyz;
    // Aici e stocat vectorul ce arata de la camera la punctul 3D procesat in acest moment
    vec3 PozitieCameraFataDePunct = vec3(0,0,0) - PozitiePunctFataDeCamera;

    PozitieCamera =  TBN * PozitieCameraFataDePunct;

    // Trecem punctul din spatiul bazei canonice in spatiul bazei camerei
    // Pozitia becului este data deja in coordonatele bazei canonice, nu avem nevoie sa o convertim in aceasta baza (nu e necesara o matrice model)
    vec3 PozitieBecFataDeCamera = ( matVizualizare * vec4(PozitieBec,1)).xyz;
    // Folosim regula triunghiului pentru adunare de vectori si obtinem pozitia becului fata de camera jucatior
    vec3 PozitieBecFataDePunct =  PozitieBecFataDeCamera + PozitieCameraFataDePunct ;

    DirectieLumina = normalize(TBN * PozitieBecFataDePunct);
}