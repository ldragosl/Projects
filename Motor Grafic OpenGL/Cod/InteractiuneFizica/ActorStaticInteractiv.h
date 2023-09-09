#pragma once
#include "ActorInteractiv.h"
#include "ActorObiectStatic.h"

class ActorStaticInteractiv : public ActorStatic, public ActorInteractiv
{
public:
	ActorStaticInteractiv(ObiectStatic* meshBaza, Material* material, InformatieInteractiuni* informatieInteractiuni);
	ActorStaticInteractiv(ObiectStatic* meshBaza, Material* material, InformatieInteractiuni* informatieInteractiuni, glm::vec3 vectorLocatie, glm::vec3 vectoraRotatie = glm::vec3(0.f), glm::vec3 vectorScala = glm::vec3(1.f));
};

