//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include "ActorObiectStatic.h"

#include "ObiectStatic.h"
#include "Interfete/Material.h"
#include "Utilitati.h"

ActorStatic::ActorStatic(ObiectStatic* meshBaza, Material* material) : ActorStatic(meshBaza, material, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)) {}

ActorStatic::ActorStatic(ObiectStatic* meshBaza, Material* material, glm::vec3 vectorLocatie, glm::vec3 vectorRotatieEuler, glm::vec3 vectorScala) : ActorRandabil(material, vectorLocatie, vectorRotatieEuler, vectorScala)
{
	obiectStaticBaza = meshBaza;
	scalaUV = glm::vec2(1.f);
}

ActorStatic::~ActorStatic()
{
	delete obiectStaticBaza;
	delete material;
}

void ActorStatic::randeaza(double timpRandareCadru, bool schimbareMaterial)
{
	//daca nu avem informatie 3D, nu avem ce randa.
	if (obiectStaticBaza && obiectStaticBaza->esteUtilizabila() && material) {
		//calculam cele 3 matrici ce vor constitui matricea "model"
		glm::mat4 matriceTranslatare = glm::translate(vectorLocatie);
		glm::mat4 matriceScalare = glm::scale(vectorScala);
		glm::mat4 matriceRotatie = Utilitati::conversieRotatieEulerLaMatrice(vectorRotatieEuler);

		//cream matricea model si o pasam materialului pentru a pregati texturile ce vor fii utilizate la randarea modelului
		material->randeazaMaterial(matriceTranslatare * matriceRotatie * matriceScalare, scalaUV, schimbareMaterial);

		obiectStaticBaza->randare();

		material->ruleazaPostRandare();
	}
}

ObiectStatic* ActorStatic::obtineObiectStaticBaza()
{
	return obiectStaticBaza;
}

void ActorStatic::seteazaObiectStaticBaza(ObiectStatic* obiectNou)
{
	obiectStaticBaza = obiectNou;
}
