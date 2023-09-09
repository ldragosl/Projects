
#include "TexturaBMP.h"

#include "directivePreprocesare.h"

#include <fstream>
#include <GL/glew.h>

#ifdef Debugare
#include <iostream>
#include <chrono>
#endif



TexturaBMP::TexturaBMP(std::string caleFisier) : Textura(caleFisier)
{
	latime = inaltime = 0;
	informatieRGB = NULL;
}

TexturaBMP::~TexturaBMP()
{
	elibereazaMemorie();
}

void TexturaBMP::incarcaResursa()
{
	if (!resursaIncarcata.load()) {
#ifdef Debugare
		auto t1 = std::chrono::high_resolution_clock::now();
#endif
		char capFisier[54];

		std::ifstream fisier;
		fisier.open(idResursa, std::ios::binary);
		if (!fisier.good())
			throw std::invalid_argument(std::string("Nu exista fisierul imagine ") + idResursa);

		fisier.read(capFisier, 54);

		latime = *(int*)&(capFisier[18]);
		inaltime = *(int*)&(capFisier[22]);
		unsigned int dimensiuneTotalaImagine = *(int*)&(capFisier[34]);
		if (dimensiuneTotalaImagine == 0)
			dimensiuneTotalaImagine = latime * inaltime * 3;

		informatieRGB = (char*)malloc(sizeof(char) * dimensiuneTotalaImagine);

		fisier.read(informatieRGB, dimensiuneTotalaImagine);

		fisier.close();


#ifdef Debugare
		auto t2 = std::chrono::high_resolution_clock::now();
		std::cout << "Am incarcat o textura: " << idResursa << ", timp: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
#endif
		resursaIncarcata.store(true);
	}
}

void TexturaBMP::initializeazaResursa()
{
	if (!resursaInitializata.load()) {
		//generam un buffer de textura
		GLuint bufferTextura;
		glGenTextures(1, &bufferTextura);
		glBindTexture(GL_TEXTURE_2D, bufferTextura);

		// trimitem imaginea propriu-zisa catre bufferul creat
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, latime, inaltime, 0, GL_BGR, GL_UNSIGNED_BYTE, informatieRGB);

		free(informatieRGB);
		informatieRGB = NULL;

		// cand facem zoom in sau zoom out, si informatia e fie prea multa, fie prea putina pentru a umple un pixel, realizam o interpolare liniara
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// generam mip-maps pentru cand textura este vizibila de la distanta
		glGenerateMipmap(GL_TEXTURE_2D);

		bufferImagine = bufferTextura;

		resursaInitializata.store(true);
	}
}

void TexturaBMP::elibereazaMemorie()
{
	if (bufferImagine != 0) {
		glDeleteTextures(1, &bufferImagine);
	}
	bufferImagine = 0;
	resursaIncarcata = false;
}