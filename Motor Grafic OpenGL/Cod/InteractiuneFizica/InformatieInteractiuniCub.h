#pragma once
#include "Interfete\InformatieInteractiuni.h"

class ObiectStatic;

class InformatieInteractiuniCub : public InformatieInteractiuni
{
public:
	InformatieInteractiuniCub(InformatieInteractiuniCub* copieInitiala);
	InformatieInteractiuniCub(ObiectStatic* obiectBaza);
	~InformatieInteractiuniCub();
	virtual void construiesteInformatieInteractiune() override;
	virtual std::vector< ShapeColiziuneCuPozitie* > obtineCollidereReact() override;
	virtual InformatieInteractiuni* copiaza() override;
	virtual void scaleaza(glm::vec3 scalaNoua) override;
private:
	ShapeColiziuneCuPozitie* colliderCub;

	//dimensiunile cubului, fara scalari
	reactphysics3d::Vector3 dimensiuniCub;
};

