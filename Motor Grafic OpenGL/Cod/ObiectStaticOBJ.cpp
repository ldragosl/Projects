#define _CRT_SECURE_NO_WARNINGS
#include "ObiectStaticOBJ.h"

#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <GL/glew.h>

#include "directivePreprocesare.h"
#include "Interfete\InformatieInteractiuni.h"
#ifdef Debugare
#include <chrono>
#endif

ObiectStaticOBJ::ObiectStaticOBJ(std::string pathFisier){
	idResursa = pathFisier;
}

ObiectStaticOBJ::~ObiectStaticOBJ()
{
	elibereazaMemorie();
}

void ObiectStaticOBJ::elibereazaMemorie()
{
	if (bufferPuncte3D != 0) {
		//trebuie sa eliberam toate bufferele
		GLuint buffereDeSters[] = {bufferPuncte3D, bufferTriunghiuri, bufferNormale,  bufferTangente, bufferBitangente, bufferUV};

		glDeleteBuffers(6, buffereDeSters);
	}
	bufferPuncte3D = 0;
	bufferTriunghiuri = 0;
	bufferNormale = 0;
	bufferTangente = 0;
	bufferBitangente = 0;
	bufferUV = 0;
}

void ObiectStaticOBJ::incarcaResursa()
{
	if (!resursaIncarcata.load()) {
#ifdef Debugare
		auto t1 = std::chrono::high_resolution_clock::now();
#endif

		//unicul scop al acestei clase interne este acela de a putea compara rapid informatia 3D in timpul indexarii
		struct Informatie3DCompleta {
			Informatie3DCompleta(glm::vec3 locatie3D, glm::vec2 uvPunct, glm::vec3 normalaPunct) : locatie3D(locatie3D), uvPunct(uvPunct), normalaPunct(normalaPunct) {}
			glm::vec3 locatie3D;
			glm::vec2 uvPunct;
			glm::vec3 normalaPunct;

			// operatorul de comparatie e necesar pentru a plasa in map struct-ul
			bool operator<(const Informatie3DCompleta comparat) const {
				return memcmp((void*)this, (void*)&comparat, sizeof(Informatie3DCompleta)) > 0;
			};
		};

		std::vector< unsigned int > indiciPuncte, indiciUV, indiciNormale;
		std::vector< glm::vec3 > tempPct;
		std::vector< glm::vec2 > tempUV;
		std::vector< glm::vec3 > tempNormale;

		std::vector<glm::vec3> puncteNeindexate;
		std::vector<glm::vec2> uvNeindexate;
		std::vector<glm::vec3> normaleNeindexate;

		//PASUL 1  - CITIRE DIN FISIER

		std::ifstream fisier(idResursa, std::ios::in);
		if (!fisier.good())
			throw std::invalid_argument(std::string("Nu exista fisierul OBJ ") + idResursa);

		while (!fisier.eof()) {
			char linie[128];
			fisier.getline(linie, 128);
			char* tipLinie = strtok(linie, " /");

			if (tipLinie == NULL)
				continue;

			if (std::strcmp(tipLinie, "v") == 0) {// v = punct 3D
				glm::vec3 punctCurent;
				punctCurent.x = std::stof(strtok(NULL, " /"));
				punctCurent.y = std::stof(strtok(NULL, " /"));
				punctCurent.z = std::stof(strtok(NULL, " /"));
				tempPct.push_back(punctCurent);
			}
			else if (std::strcmp(tipLinie, "vt") == 0) {// vt = informatie UV
				glm::vec2 uvCurent;
				uvCurent.x = std::stof(strtok(NULL, " /"));
				uvCurent.y = std::stof(strtok(NULL, " /"));
				tempUV.push_back(uvCurent);
			}
			else if (std::strcmp(tipLinie, "vn") == 0) {// vn - normala unui punct 3D
				glm::vec3 normalaCurenta;
				normalaCurenta.x = std::stof(strtok(NULL, " /"));
				normalaCurenta.y = std::stof(strtok(NULL, " /"));
				normalaCurenta.z = std::stof(strtok(NULL, " /"));
				tempNormale.push_back(normalaCurenta);
			}
			else if (std::strcmp(tipLinie, "f") == 0) {// f - un poligon
				// importerul acesta functioneaza doar pentru poligoane ce pot fii trimise direct catre placa video - adica triunghiuri
				unsigned int indexPunct[3], indexUV[3], indexNormala[3];
				for (int i = 0; i < 3; i++) {
					indexPunct[i] = std::stoi(strtok(NULL, " /"));
					indexUV[i] = std::stoi(strtok(NULL, " /"));
					indexNormala[i] = std::stoi(strtok(NULL, " /"));
				}
				indiciPuncte.push_back(indexPunct[0]);
				indiciPuncte.push_back(indexPunct[1]);
				indiciPuncte.push_back(indexPunct[2]);
				indiciUV.push_back(indexUV[0]);
				indiciUV.push_back(indexUV[1]);
				indiciUV.push_back(indexUV[2]);
				indiciNormale.push_back(indexNormala[0]);
				indiciNormale.push_back(indexNormala[1]);
				indiciNormale.push_back(indexNormala[2]);
			}
		}
		fisier.close();

		//PASUL 2 - ASEZAM PUNCTELE IN ORDINEA IN CARE SUNT TRIUNGHIURILE

		// (adica, primele 3 puncte, uv-uri si normale apartin primului triunghi, urmatoarele 3 celui de-al doilea etc
		// in acest mod sunt create totusi duplicate. Ele vor fii eliminate ulterior
		for (unsigned int i = 0; i < indiciPuncte.size(); i++) {
			puncteNeindexate.push_back(tempPct[indiciPuncte[i] - 1]);
		}
		for (unsigned int i = 0; i < indiciUV.size(); i++) {
			uvNeindexate.push_back(tempUV[indiciUV[i] - 1]);
		}
		for (unsigned int i = 0; i < indiciNormale.size(); i++) {
			normaleNeindexate.push_back(tempNormale[indiciNormale[i] - 1]);
		}

		//PASUL 3 - calculare TANGENTE SI BITANGENTE

		std::vector<glm::vec3> tangenteNeindexate;
		std::vector<glm::vec3> bitangenteNeindexate;
		//calculam tangenta si bitangenta fiecarui punct. Mergem din 3 in 3 deoarece un triunghi are 3 varfuri
		for (int i = 0; i < puncteNeindexate.size(); i += 3) {

			// tangentele si bitangentele sunt o infinitate: insa standardul este utilizarea celor ce se alinieaza cu UV-urile.
			// rescriem laturile triunghiurilor ca o combinatie liniara a tangentelor si bitangentelor

			// trebuie sa rezolvam sistemul urmator:
			//deltaPos1 = (u1 - u0) * Tangenta + (v1 - v0) * Bitangenta
			//deltaPos2 = (u2 - u0) * Tangenta + (v2 - v0) * Bitangenta

			// 2 dintre laturile triunghiului
			glm::vec3 latura1 = puncteNeindexate[i + 1] - puncteNeindexate[i];
			glm::vec3 latura2 = puncteNeindexate[i + 2] - puncteNeindexate[i];

			//uv1.x = u1 - u0, uv1.y = v1 - v0
			glm::vec2 uv1 = uvNeindexate[i + 1] - uvNeindexate[i];
			glm::vec2 uv2 = uvNeindexate[i + 2] - uvNeindexate[i];

			//rezolvam sistemul cu regula lui Cramer
			float delta = (uv1.x * uv2.y - uv1.y * uv2.x);
			glm::vec3 tangentaCurenta = (latura1 * uv2.y - latura2 * uv1.y) / delta;
			glm::vec3 bitangentaCurenta = (latura2 * uv1.x - latura1 * uv2.x) / delta;

			// tangentele si bitangentele unui poligon sunt aceleasi pentru fiecare varf
			tangenteNeindexate.push_back(tangentaCurenta);
			tangenteNeindexate.push_back(tangentaCurenta);
			tangenteNeindexate.push_back(tangentaCurenta);

			bitangenteNeindexate.push_back(bitangentaCurenta);
			bitangenteNeindexate.push_back(bitangentaCurenta);
			bitangenteNeindexate.push_back(bitangentaCurenta);
		}


		//PASUL 4 - INDEXARE
		// prin indexare este micsorata cantitatea de memorie parcursa pentru fiecare frame

		//trebuie sa comparam fiecare punct cu fiecare punct
		// putem reduce complexitatea de la O(n^2) la O(n*log(n)) folosind un map deoarece
		//intern, map foloseste arbori balansati (de obicei, arbori rosu-negru)
		//astfel, cautarea are loc in log(n) pasi
		std::map<Informatie3DCompleta, int> mapIndexareRapida;

		for (unsigned int i = 0; i < puncteNeindexate.size(); i++) {
			Informatie3DCompleta punct(puncteNeindexate[i], uvNeindexate[i], normaleNeindexate[i]);

			//verificam daca exista un punct identic 		
			std::map<Informatie3DCompleta, int>::iterator it = mapIndexareRapida.find(punct);

			//daca exista deja, folosim indexul sau 
			if (it != mapIndexareRapida.end()) {
				indiciTriunghiuri.push_back(it->second);

				// Pentru a obtine colturi fine, creem o medie a tangentelor si bitangentelor
				//nu e necesara impartirea la nr de puncte deoarece acestea sunt normalizate
				tangente[it->second] += tangenteNeindexate[i];
				bitangente[it->second] += bitangenteNeindexate[i];
			}
			else {
				//Daca nu am gasit un punct identic, inseamna ca salvam punctul e nou si il salvam
				puncte3D.push_back(puncteNeindexate[i]);
				uv.push_back(uvNeindexate[i]);
				normale.push_back(normaleNeindexate[i]);
				tangente.push_back(tangenteNeindexate[i]);
				bitangente.push_back(bitangenteNeindexate[i]);

				int indexNou = (int)puncte3D.size() - 1;
				indiciTriunghiuri.push_back(indexNou);
				mapIndexareRapida[punct] = indexNou;
			}
		}
		resursaIncarcata.store(true);
#ifdef Debugare
		auto t2 = std::chrono::high_resolution_clock::now();
		std::cout << "Am incarcat un obiect 3D: " << idResursa << ", timp: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
		std::cout << "Indexare efectuata, reducere de la " << puncteNeindexate.size() << " la " << puncte3D.size() << std::endl;
#endif
	}
}

void ObiectStaticOBJ::initializeazaResursa()
{
	if (!resursaInitializata.load()) {
		//PASUL 5 - incarcare date citite in buffere

		//Incarcam punctele 3D intr-un buffer
		glGenBuffers(1, &bufferPuncte3D);
		glBindBuffer(GL_ARRAY_BUFFER, bufferPuncte3D);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * puncte3D.size(), &puncte3D[0], GL_STATIC_DRAW);

		//Incarcam triunghiurile intr-un buffer
		glGenBuffers(1, &bufferTriunghiuri);
		glBindBuffer(GL_ARRAY_BUFFER, bufferTriunghiuri);
		glBufferData(GL_ARRAY_BUFFER, sizeof(int) * indiciTriunghiuri.size(), &indiciTriunghiuri[0], GL_STATIC_DRAW);
		numarPuncte = indiciTriunghiuri.size();
		indiciTriunghiuri.clear();

		//Punem normalele, tangentele, binormalele si uv-urile fiecarui punct 3d intr-un buffer
		glGenBuffers(1, &bufferNormale);
		glBindBuffer(GL_ARRAY_BUFFER, bufferNormale);
		glBufferData(GL_ARRAY_BUFFER, normale.size() * sizeof(glm::vec3), &normale[0], GL_STATIC_DRAW);
		normale.clear();

		glGenBuffers(1, &bufferTangente);
		glBindBuffer(GL_ARRAY_BUFFER, bufferTangente);
		glBufferData(GL_ARRAY_BUFFER, tangente.size() * sizeof(glm::vec3), &tangente[0], GL_STATIC_DRAW);
		tangente.clear();

		glGenBuffers(1, &bufferBitangente);
		glBindBuffer(GL_ARRAY_BUFFER, bufferBitangente);
		glBufferData(GL_ARRAY_BUFFER, bitangente.size() * sizeof(glm::vec3), &bitangente[0], GL_STATIC_DRAW);
		bitangente.clear();

		glGenBuffers(1, &bufferUV);
		glBindBuffer(GL_ARRAY_BUFFER, bufferUV);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uv.size(), &uv[0], GL_STATIC_DRAW);
		uv.clear();

		resursaInitializata.store(true);
	}
}
