#pragma once
#include "ObiectStaticOBJ.h"

class ObiectStaticIdentificabil : public ObiectStaticOBJ
{
public:
	std::string obtineEticheta();
protected:
	ObiectStaticIdentificabil(std::string cale) : ObiectStaticOBJ(cale) {}

	virtual void calculeazaEticheta(std::string caleObiect) = 0;
	virtual void incarcaResursa() override;
	std::string eticheta;
};

