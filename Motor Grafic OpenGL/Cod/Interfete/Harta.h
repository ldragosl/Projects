//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once

#include <set>
#include <vector>
#include "glm\gtx\transform.hpp"

#include "ActorRandabil.h"

namespace reactphysics3d {
	class RigidBody;
}

class ActorInteractiv;
class Actor;

class Harta
{
public:
	~Harta();

	//Chemat o singura data de catre engine
	virtual void incepereHarta() = 0;
	//Chemat o singura data per frame
	virtual void frameUrmator(double timpRandareCadru) = 0;

	virtual void adaugaActor(Actor* Actor);
	virtual void stergeActor(Actor* Actor);

	ActorInteractiv* obtineActorInteractivDinCorp(reactphysics3d::RigidBody* corpColiziune);

	glm::vec3 obtinePozitieLumina();
	float obtineIntensitateLumina();
	glm::vec3 obtineCuloareLumina();
protected:
	glm::vec3 pozitieLumina;
	glm::vec3 culoareLumina;
	float intensitateLumina;

	Harta();
private:
	std::multiset<ActorRandabil*, ComparatorActoriRandabili> obiecteDeRandat;
	std::vector<ActorInteractiv*> obiecteColiziune;
	std::vector<Actor*> actori;

	void randeazaHarta(double timpRandareCadru);

	void tick(double timpRandareCadru);

	friend class MotorGrafic;
};

