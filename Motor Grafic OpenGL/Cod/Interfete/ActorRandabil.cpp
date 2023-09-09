#include "ActorRandabil.h"

#include "Material.h"

bool ComparatorActoriRandabili::operator()(const ActorRandabil* actor1, const ActorRandabil* actor2) const
{
	return actor1->obtineIndexMaterial() < actor2->obtineIndexMaterial();
}

int ActorRandabil::obtineIndexMaterial() const
{
	return material->obtineIndexMaterial();
}

ActorRandabil::ActorRandabil(Material* material, glm::vec3 vectorLocatie, glm::vec3 vectorRotatieEuler, glm::vec3 vectorScala) : Actor(vectorLocatie, vectorRotatieEuler, vectorScala), material(material)
{
}
