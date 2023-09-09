#include "ObiectDebugareColiziuni.h"

#include <reactphysics3d\reactphysics3d.h>
#include <GL/glew.h>
#include <map>

#include "CoreMotor/MotorGrafic.h"
#include "Utilitati.h"

ObiectDebugareColiziuni* ObiectDebugareColiziuni::referintaSingleton = NULL;

ObiectDebugareColiziuni::ObiectDebugareColiziuni()
{
}

ObiectDebugareColiziuni::~ObiectDebugareColiziuni()
{
	elibereazaMemorie();
}

ObiectDebugareColiziuni* ObiectDebugareColiziuni::obtineObiectDebugareColiziuni()
{
	if (!referintaSingleton)
		referintaSingleton = new ObiectDebugareColiziuni();
	return referintaSingleton;
}

void ObiectDebugareColiziuni::reimprospatare()
{
	incarcaResursa();
}

void ObiectDebugareColiziuni::incarcaResursa()
{
	elibereazaMemorie();
	struct ComparatorLocatie3d {
		ComparatorLocatie3d(glm::vec3 locatie3D) : locatie3D(locatie3D) {}
		glm::vec3 locatie3D;

		// operatorul de comparatie e necesar pentru a plasa in map struct-ul
		bool operator<(const ComparatorLocatie3d comparat) const {
			return memcmp((void*)this, (void*)&comparat, sizeof(ComparatorLocatie3d)) > 0;
		};
	};

	reactphysics3d::DebugRenderer& debugator = MotorGrafic::obtineMotorGrafic()->obtineLumeColiziuni()->getDebugRenderer();
	unsigned int nrTriunghiuri = debugator.getNbTriangles();
	if (nrTriunghiuri == 0)
		return;
	auto triunghiuri = debugator.getTrianglesArray();

	std::vector<glm::vec3> puncteNeindexate;

	for(int i = 0; i < nrTriunghiuri; i++) {
		puncteNeindexate.push_back(Utilitati::convertesteVectorReact3DLaGlm(triunghiuri[i].point1));
		puncteNeindexate.push_back(Utilitati::convertesteVectorReact3DLaGlm(triunghiuri[i].point2));
		puncteNeindexate.push_back(Utilitati::convertesteVectorReact3DLaGlm(triunghiuri[i].point3));
	}

	// prin indexare este micsorata cantitatea de memorie parcursa pentru fiecare frame

	//trebuie sa comparam fiecare punct cu fiecare punct
	// putem reduce complexitatea de la O(n^2) la O(n*log(n)) folosind un map deoarece
	//intern, map foloseste arbori balansati (de obicei, arbori rosu-negru)
	//astfel, cautarea are loc in log(n) pasi
	std::map<ComparatorLocatie3d, int> mapIndexareRapida;

	for (unsigned int i = 0; i < puncteNeindexate.size(); i++) {
		ComparatorLocatie3d punct(puncteNeindexate[i]);

		//verificam daca exista un punct identic 		
		std::map<ComparatorLocatie3d, int>::iterator it = mapIndexareRapida.find(punct);

		//daca exista deja, folosim indexul sau 
		if (it != mapIndexareRapida.end()) {
			indiciTriunghiuri.push_back(it->second);
		}
		else {
			//Daca nu am gasit un punct identic, inseamna ca salvam punctul e nou si il salvam
			puncte3D.push_back(puncteNeindexate[i]);
			int indexNou = (int)puncte3D.size() - 1;
			indiciTriunghiuri.push_back(indexNou);
			mapIndexareRapida[punct] = indexNou;
		}
	}

	numarPuncte = indiciTriunghiuri.size();

	resursaIncarcata.store(true);

	initializeazaResursa();
}

void ObiectDebugareColiziuni::initializeazaResursa()
{
	//Incarcam punctele 3D intr-un buffer
	glGenBuffers(1, &bufferPuncte3D);
	glBindBuffer(GL_ARRAY_BUFFER, bufferPuncte3D);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * puncte3D.size(), &puncte3D[0], GL_STATIC_DRAW);
	puncte3D.clear();

	//Incarcam triunghiurile intr-un buffer
	glGenBuffers(1, &bufferTriunghiuri);
	glBindBuffer(GL_ARRAY_BUFFER, bufferTriunghiuri);
	glBufferData(GL_ARRAY_BUFFER, sizeof(int) * indiciTriunghiuri.size(), &indiciTriunghiuri[0], GL_STATIC_DRAW);
	indiciTriunghiuri.clear();

	resursaInitializata.store(true);
}

void ObiectDebugareColiziuni::elibereazaMemorie()
{
	resursaIncarcata.store(false);
	resursaInitializata.store(false);
	if (bufferPuncte3D != 0) {
		glDeleteBuffers(1, &bufferPuncte3D);
		bufferPuncte3D = 0;
	}
	if (bufferTriunghiuri != 0) {
		glDeleteBuffers(1, &bufferTriunghiuri);
		bufferTriunghiuri = 0;
	}
	if (bufferUV != 0) {
		glDeleteBuffers(1, &bufferUV);
		bufferUV = 0;
	}
}

void ObiectDebugareColiziuni::randare()
{
	// informam openGL ca vor fii transmise catre shadere 4 atribute
	glEnableVertexAttribArray(0);

	//ordinea atributelor este aceeasi cu cea in care au fost declarate atributele in vertex shader

	//coordonatele punctelor 3D
	glBindBuffer(GL_ARRAY_BUFFER, bufferPuncte3D);
	glVertexAttribPointer(
		0,                  // nr atribut
		3,                  // numarul de componente al fiecarei coordonate 3D
		GL_FLOAT,           // tipul datelor din buffer
		GL_FALSE,           // datele nu sunt normalizate
		0,                  // stride - 0 deoarece vom randa toate punctele din buffer
		NULL				// array buffer offset
	);

	// transmitem OpenGL indecsii punctelor ce alcatuiesc triunghiurile ce urmeaza a fii randate
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferTriunghiuri);

	// cerem OpenGL sa rendeze obiectul utilizand shaderele selectate si informatia buffer-uita
	glDrawElements(
		GL_TRIANGLES,		// modul de randare
		numarPuncte,		//numarul de varfuri de triunghi (nr triunghiuri * 3)
		GL_UNSIGNED_INT,	//tipul indecsilor este int
		NULL				// nu avem offset
	);

	//materialul a fost randat: curatam atributele utilizate pentru a putea randa alte shadere
	glDisableVertexAttribArray(0);
}
