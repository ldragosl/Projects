//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once

#include "Resursa.h"

typedef unsigned int GLuint;

class Textura : public Resursa {
public:
	virtual void elibereazaMemorie() = 0;

	Textura(std::string caleFisier) { idResursa = caleFisier; bufferImagine = 0; }

	Textura* incarca();

	GLuint obtineBufferImagine() { return bufferImagine; };
protected:
	GLuint bufferImagine;
};