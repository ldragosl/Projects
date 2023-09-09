#pragma once

#include "ObiectStatic.h"

class ObiectStaticNormale : public ObiectStatic {
public:
	virtual void randare() override;
protected:
	ObiectStaticNormale();

	//normalele, tangentele si bitangentele sunt folosite pentru a "falsifica" mai mult detaliu prin adaugarea de texturi "normale"
	GLuint bufferNormale;
	GLuint bufferTangente;
	GLuint bufferBitangente;
};