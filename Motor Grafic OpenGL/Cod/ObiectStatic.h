//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Interfete/Resursa.h"

class ActorStatic;
class Material;
class InformatieInteractiuni;

typedef unsigned int GLuint;

class ObiectStatic : public Resursa
{
public:
	virtual void randare() = 0;

	std::vector<glm::vec3>* obtinePuncte3D();

	ObiectStatic* incarca();
protected:
	ObiectStatic();

	//referinte catre informatia 3d stocata in placa video

	//aici sunt stocatele punctele 3d (vectori 3-dimensionali) ce constituie obiectul 3D
	GLuint bufferPuncte3D;
	//aici sunt stocati indecsii punctelor 3D ce alcatuiesc triunghiurile
	GLuint bufferTriunghiuri;
	//uv-urile mapeaza texturile 2d la obiectele 3D
	GLuint bufferUV;

	//referinte catre informatia 3d stocata in RAM (pentru coliziuni de exemplu)
	std::vector<glm::vec3> puncte3D;

	int numarPuncte;
};

