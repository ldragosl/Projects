#include "ObiectStaticIdentificabilStartup.h"

ObiectStaticIdentificabilStartup::ObiectStaticIdentificabilStartup(std::string caleFisier) : ObiectStaticIdentificabil(caleFisier)
{
}

void ObiectStaticIdentificabilStartup::incarcaResursa()
{
	calculeazaEticheta(idResursa);
	ObiectStaticIdentificabil::incarcaResursa();
}

void ObiectStaticIdentificabilStartup::calculeazaEticheta(std::string caleFisier)
{
	caleFisier = caleFisier.substr(0, caleFisier.find_last_of('.')) + ".pth";

	char bufferEticheta[64];
	FILE* pipe = _popen(("python inferenta.py " + caleFisier).c_str(), "r");
	if (NULL != fgets(bufferEticheta, sizeof(bufferEticheta), pipe))
		eticheta = bufferEticheta;
	_pclose(pipe);
}
