//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once

#include "Interfete\ActorRandabil.h"

class Material;
class ObiectStatic;

//un obiect static cu material, locatie, rotatie si scala
class ActorStatic : public ActorRandabil
{
public:
	ActorStatic(ObiectStatic* meshBaza, Material* material);
	ActorStatic(ObiectStatic* meshBaza, Material* material, glm::vec3 vectorLocatie, glm::vec3 vectorRotatieEuler, glm::vec3 vectorScala);
	~ActorStatic();

	virtual void randeaza(double timpRandareCadru, bool schimbareMaterial) override;

	ObiectStatic* obtineObiectStaticBaza();
	void seteazaObiectStaticBaza(ObiectStatic* obiectNou);
protected:
	ObiectStatic* obiectStaticBaza;
public:
	glm::vec2 scalaUV;
};

