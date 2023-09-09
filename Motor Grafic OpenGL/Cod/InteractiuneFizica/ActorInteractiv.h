#pragma once

#include "Interfete\Actor.h"
#include <vector>
#include <reactphysics3d\components\RigidBodyComponents.h>

namespace reactphysics3d {
	class RigidBody;
}

class InformatieInteractiuni;

class ActorInteractiv : virtual public Actor
{
public:
	ActorInteractiv(InformatieInteractiuni* informatieInteractiuni);
	ActorInteractiv(InformatieInteractiuni* informatieInteractiuni, glm::vec3 locatie, glm::vec3 rotatie, glm::vec3 scala);
	~ActorInteractiv();

	reactphysics3d::RigidBody* obtineCorpFizic();

	virtual void seteazaLocatie(glm::vec3 locatieNoua) override;
	virtual void seteazaRotatie(glm::vec3 rotatieNoua) override;
	virtual void seteazaScala(glm::vec3 scalaNoua) override;
protected:
	void reimprospateazaTransformareColiziuni();

	reactphysics3d::RigidBody* corpFizic;
	InformatieInteractiuni* informatieInteractiuni;
	bool informatieInteractiuniInterna;
	bool initializat;
	reactphysics3d::BodyType tipCorpFizic;

	void construiesteInformatieColiziuniInterna();
};

