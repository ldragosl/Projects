#include "Textura.h"

#include "CoreMotor\ManagerResurse.h"

Textura* Textura::incarca()
{
	ManagerResurse* manager = ManagerResurse::obtineManagerResurse();
	return manager->adaugaTextura(this);
}