#include "ObiectStaticIdentificabil.h"

void ObiectStaticIdentificabil::incarcaResursa()
{
	ObiectStaticOBJ::incarcaResursa();
}

std::string ObiectStaticIdentificabil::obtineEticheta()
{
	return eticheta;
}
