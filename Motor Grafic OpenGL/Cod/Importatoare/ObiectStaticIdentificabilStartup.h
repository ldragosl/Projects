#pragma once
#include "ObiectStaticIdentificabil.h"
class ObiectStaticIdentificabilStartup : public ObiectStaticIdentificabil
{
public:
	ObiectStaticIdentificabilStartup(std::string caleFisier);
protected:
	virtual void incarcaResursa() override;
	virtual void calculeazaEticheta(std::string caleFisier) override;
};

