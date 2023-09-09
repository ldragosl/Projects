#include "TextRandabil.h"

#include <GL/glew.h>

void TextRandabil::randare()
{
    if (esteUtilizabila()) {
        // informam openGL ca vor fii transmise catre shadere 4 atribute
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        //ordinea atributelor este aceeasi cu cea in care au fost declarate atributele in vertex shader

        //coordonatele punctelor 3D
        glBindBuffer(GL_ARRAY_BUFFER, bufferPuncte3D);//aici datele sunt 2d defapt
        glVertexAttribPointer(
            0,                  // nr atribut
            2,                  // numarul de componente al fiecarei coordonate 2D
            GL_FLOAT,           // tipul datelor din buffer
            GL_FALSE,           // datele nu sunt normalizate
            0,                  // stride - 0 deoarece vom randa toate punctele din buffer
            NULL				// array buffer offset
        );

        //bufferul de coordonate UV (maparea suprafetelor 3D la texturi 2D)
        glBindBuffer(GL_ARRAY_BUFFER, bufferUV);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);


        // transmitem OpenGL indecsii punctelor ce alcatuiesc triunghiurile ce urmeaza a fii randate
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferTriunghiuri);

        // cerem OpenGL sa rendeze obiectul utilizand shaderele selectate si informatia buffer-uita
        glDrawElements(
            GL_TRIANGLES,							// modul de randare
            numarPuncte,	//numarul de varfuri de triunghi (nr triunghiuri * 2)
            GL_UNSIGNED_INT,						//tipul indecsilor este int
            NULL									// nu avem offset
        );

        //materialul a fost randat: curatam atributele utilizate pentru a putea randa alte shadere
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
}

void TextRandabil::incarcaResursa()
{
    elibereazaMemorie();

    //nu putem trimite un buffer gol catre openGL -> va rezulta intr-un crash
    if (idResursa == "")
        idResursa = " ";

    int lungimeText = idResursa.length();
    for (unsigned int i = 0; i < lungimeText; i++) {
        // adaugam 4 puncte
        puncte2D.push_back(glm::vec2(pozitieX + i * marimeText, pozitieY + marimeText));
        puncte2D.push_back(glm::vec2(pozitieX + i * marimeText + marimeText, pozitieY + marimeText));
        puncte2D.push_back(glm::vec2(pozitieX + i * marimeText + marimeText, pozitieY));
        puncte2D.push_back(glm::vec2(pozitieX + i * marimeText, pozitieY));

        // adaugam 4 uv-uri
        float pozitieUV_x = (idResursa[i] % 16) / 16.0f;
        float pozitieUV_y = (idResursa[i] / 16 - 2.f) / 16.0f;
        uv.push_back(glm::vec2(pozitieUV_x, 1.0f - pozitieUV_y));
        uv.push_back(glm::vec2(pozitieUV_x + 1.0f / 16.0f, 1.0f - pozitieUV_y));
        uv.push_back(glm::vec2(pozitieUV_x + 1.0f / 16.0f, 1.0f - (pozitieUV_y + 1.0f / 16.0f)));
        uv.push_back(glm::vec2(pozitieUV_x, 1.0f - (pozitieUV_y + 1.0f / 16.0f)));

        // adaugam 2 triunghiuri, formate prin conectarea celor 4 puncte
        // cele 2 triunghiuri au o latura comuna, iar toate celelalte laturi sunt egale -> e format un patrat pe care e randata litera ca si o textura
        indiciTriunghiuri.push_back(i * 4 + 0);
        indiciTriunghiuri.push_back(i * 4 + 3);
        indiciTriunghiuri.push_back(i * 4 + 1);

        indiciTriunghiuri.push_back(i * 4 + 2);
        indiciTriunghiuri.push_back(i * 4 + 1);
        indiciTriunghiuri.push_back(i * 4 + 3);
    }

    numarPuncte = indiciTriunghiuri.size();

    resursaIncarcata.store(true);

    initializeazaResursa();
}

void TextRandabil::initializeazaResursa()
{
    if (bufferTriunghiuri == bufferPuncte3D == bufferUV == 0) {
        //Incarcam punctele 3D intr-un buffer
        glGenBuffers(1, &bufferPuncte3D);
        glBindBuffer(GL_ARRAY_BUFFER, bufferPuncte3D);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * puncte2D.size(), &puncte2D[0], GL_STATIC_DRAW);
        puncte2D.clear();

        //Incarcam triunghiurile intr-un buffer
        glGenBuffers(1, &bufferTriunghiuri);
        glBindBuffer(GL_ARRAY_BUFFER, bufferTriunghiuri);
        glBufferData(GL_ARRAY_BUFFER, sizeof(int) * indiciTriunghiuri.size(), &indiciTriunghiuri[0], GL_STATIC_DRAW);
        indiciTriunghiuri.clear();

        //la final, punem si uv-urile intr-un buffer
        glGenBuffers(1, &bufferUV);
        glBindBuffer(GL_ARRAY_BUFFER, bufferUV);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uv.size(), &uv[0], GL_STATIC_DRAW);
        uv.clear();

        resursaInitializata.store(true);

        for (auto functieCallbackCurenta : callbackResursaIncarcata) {
            functieCallbackCurenta();
        }
        callbackResursaIncarcata.clear();
    }
}

TextRandabil::TextRandabil(std::string text, float pozitieX, float pozitieY, float marimeText)
{
    this->pozitieX = pozitieX;
    this->pozitieY = pozitieY;
    this->marimeText = marimeText;
    idResursa = text;
    incarcaResursa();
}

void TextRandabil::schimbaText(std::string textNou)
{
    idResursa = textNou;
    incarcaResursa();
}

void TextRandabil::elibereazaMemorie()
{
    resursaInitializata.store(false);
    resursaIncarcata.store(false);
    if (bufferPuncte3D != 0) {
        //trebuie sa eliberam toate bufferele
        GLuint buffereDeSters[] = { bufferPuncte3D, bufferTriunghiuri, bufferUV };

        glDeleteBuffers(3, buffereDeSters);
    }
    bufferPuncte3D = 0;
    bufferTriunghiuri = 0;
    bufferUV = 0;
}

TextRandabil::~TextRandabil()
{
    elibereazaMemorie();
}
