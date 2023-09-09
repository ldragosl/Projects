//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#include "Harta.h"

#include <GL\glew.h>
#include <algorithm>

#include "ActorRandabil.h"
#include "directivePreprocesare.h"
#include "CoreMotor/MotorGrafic.h"
#include "InteractiuneFizica\ActorInteractiv.h"

Harta::~Harta()
{
	//curatam memoria inainte de a termina executia
	for (Actor* obiectCurent : actori) {
		delete obiectCurent;
	}
}

void Harta::adaugaActor(Actor* Actor)
{
	if (std::find(actori.begin(), actori.end(), Actor) == actori.end()) {
		actori.push_back(Actor);
		//actorul poate fii fie randabil, fie interactiv, fie ambele.

		// verificam daca actorul e randabil
		ActorRandabil* testRandabil = dynamic_cast<ActorRandabil*>(Actor);
		if (testRandabil) {
			obiecteDeRandat.emplace(testRandabil);
		}

		//verificam daca obiectul e interactiv
		ActorInteractiv* testInteractiv = dynamic_cast<ActorInteractiv*>(Actor);
		if (testInteractiv) {
			obiecteColiziune.push_back(testInteractiv);
		}
	}
}

void Harta::stergeActor(Actor* Actor)
{
	for (auto iteratorActor = actori.begin(); iteratorActor != actori.end(); iteratorActor++) {
		if (*iteratorActor == Actor) {
			actori.erase(iteratorActor);
			break;
		}
	}
	//actorul poate fii fie randabil, fie interactiv, fie ambele.

	// verificam daca actorul e randabil
	ActorRandabil* testRandabil = dynamic_cast<ActorRandabil*>(Actor);
	if (testRandabil) {
		obiecteDeRandat.erase(testRandabil);
	}

	//verificam daca obiectul e interactiv
	ActorInteractiv* testInteractiv = dynamic_cast<ActorInteractiv*>(Actor);
	if (testInteractiv) {
		for (auto iteratorObInteractiv = obiecteColiziune.begin(); iteratorObInteractiv != obiecteColiziune.end(); iteratorObInteractiv++) {
			if (*iteratorObInteractiv == testInteractiv) {
				obiecteColiziune.erase(iteratorObInteractiv);
				break;
			}
		}
	}
}

ActorInteractiv* Harta::obtineActorInteractivDinCorp(reactphysics3d::RigidBody* corpColiziune)
{
	for (ActorInteractiv* actorCurent : obiecteColiziune) {
		if (actorCurent->obtineCorpFizic() == corpColiziune)
			return actorCurent;
	}
	return nullptr;
}

glm::vec3 Harta::obtinePozitieLumina()
{
	return pozitieLumina;
}

float Harta::obtineIntensitateLumina()
{
	return intensitateLumina;
}

glm::vec3 Harta::obtineCuloareLumina()
{
	return culoareLumina;
}

Harta::Harta()
{
	pozitieLumina = glm::vec3(0.f);
	culoareLumina = glm::vec3(1.f);
	intensitateLumina = 1.f;
}


void Harta::randeazaHarta(double timpRandareCadru)
{
	frameUrmator(timpRandareCadru);
	//curatam bufferul de culoare si cel de adancime (folosit pentru a asigura randarea obiectelor mai aproape de camera peste celalte)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//randam mesh-urile
	//facem o optimizare: nu trimitem catre placa video din nou toate informatiile daca acestea sunt deja acolo (adica nu s-a schimbat materialul randat)
	int indexMaterialAnterior = -1;
	for (ActorRandabil* curent : obiecteDeRandat) {
		curent->randeaza(timpRandareCadru, curent->obtineIndexMaterial() != indexMaterialAnterior);
		indexMaterialAnterior = curent->obtineIndexMaterial();
	}
}

void Harta::tick(double timpRandareCadru)
{
	for (auto obiectCurent : actori) {
		obiectCurent->tick(timpRandareCadru);
	}
}
