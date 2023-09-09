#include "ActorStaticInteractiv.h"
#include "Interfete\InformatieInteractiuni.h"
#include "ObiectStatic.h"

ActorStaticInteractiv::ActorStaticInteractiv(ObiectStatic* meshBaza, Material* material, InformatieInteractiuni* informatieInteractiuni) : ActorStatic(meshBaza, material), ActorInteractiv(informatieInteractiuni)
{}

ActorStaticInteractiv::ActorStaticInteractiv(ObiectStatic* meshBaza, Material* material, InformatieInteractiuni* informatieInteractiuni, glm::vec3 vectorLocatie, glm::vec3 vectoraRotatie, glm::vec3 vectorScala)
	: ActorStatic(meshBaza, material, vectorLocatie, vectoraRotatie, vectorScala), ActorInteractiv(informatieInteractiuni, vectorLocatie, vectoraRotatie, vectorScala), Actor(vectorLocatie, vectoraRotatie, vectorScala)
{}
