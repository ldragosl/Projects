//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include "Actor.h"
#include "glm/gtx/transform.hpp"

class Material;

class ActorRandabil : virtual public Actor{
public:
	virtual void randeaza(double timpRandareCadru, bool schimbareMaterial) = 0;

	int obtineIndexMaterial() const;
protected:
	ActorRandabil() : material(NULL) {};
	ActorRandabil(Material* material, glm::vec3 vectorLocatie, glm::vec3 vectorRotatieEuler, glm::vec3 vectorScala);
	Material* material;
};

class ComparatorActoriRandabili {
public:
	bool operator()(const ActorRandabil* actor1, const ActorRandabil* actor2) const;
};