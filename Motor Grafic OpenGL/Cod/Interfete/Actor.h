#pragma once
#include <glm/glm.hpp>

class Actor {
public:
	Actor() : Actor(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)) {}
	Actor(glm::vec3 vectorLocatie, glm::vec3 vectorRotatieEuler, glm::vec3 vectorScala) : vectorLocatie(vectorLocatie), vectorRotatieEuler(vectorRotatieEuler), vectorScala(vectorScala) {};
	
	glm::vec3 obtineLocatie();
	virtual void seteazaLocatie(glm::vec3 locatieNoua);

	glm::vec3 obtineRotatie();
	virtual void seteazaRotatie(glm::vec3 rotatieNoua);

	glm::vec3 obtineScala();
	virtual void seteazaScala(glm::vec3 scalaNoua);

	virtual void tick(float deltaTimp) {}
protected:
	glm::vec3 vectorLocatie;
	glm::vec3 vectorRotatieEuler;
	glm::vec3 vectorScala;
};