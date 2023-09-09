//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include "ObiectStatic.h"
#include "CoreMotor\ManagerResurse.h"

std::vector<glm::vec3>* ObiectStatic::obtinePuncte3D()
{
	return &puncte3D;
}

ObiectStatic* ObiectStatic::incarca()
{
	ManagerResurse* manager = ManagerResurse::obtineManagerResurse();
	return manager->adaugaObiectStatic(this);
}

ObiectStatic::ObiectStatic()
{
	bufferPuncte3D = 0;
	bufferTriunghiuri = 0;
	bufferUV = 0;
	numarPuncte = 0;
}