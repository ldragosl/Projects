#include "Actor.h"

glm::vec3 Actor::obtineLocatie()
{
    return vectorLocatie;
}

void Actor::seteazaLocatie(glm::vec3 locatieNoua)
{
    vectorLocatie = locatieNoua;
}

glm::vec3 Actor::obtineRotatie()
{
    return vectorRotatieEuler;
}

void Actor::seteazaRotatie(glm::vec3 rotatieNoua)
{
    vectorRotatieEuler = rotatieNoua;
}

glm::vec3 Actor::obtineScala()
{
    return vectorScala;
}

void Actor::seteazaScala(glm::vec3 scalaNoua)
{
    vectorScala = scalaNoua;
}
