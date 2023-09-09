#include "ActorInteractiv.h"

#include "CoreMotor/MotorGrafic.h"
#include "Utilitati.h"
#include "Interfete\InformatieInteractiuni.h"

#include "reactphysics3d\reactphysics3d.h" 

ActorInteractiv::ActorInteractiv(InformatieInteractiuni* informatieInteractiuni) : ActorInteractiv(informatieInteractiuni, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)) { }

ActorInteractiv::ActorInteractiv(InformatieInteractiuni* informatieInteractiuniNoua, glm::vec3 locatie, glm::vec3 rotatie, glm::vec3 scala)
{
	initializat = false;
	this->vectorLocatie = locatie;
	this->vectorRotatieEuler = rotatie;
	this->vectorScala = scala;
	tipCorpFizic = reactphysics3d::BodyType::STATIC;
	informatieInteractiuni = informatieInteractiuniNoua;

	corpFizic = NULL;
	informatieInteractiuniInterna = false;
	if (informatieInteractiuni) {
		informatieInteractiuni->adaugaCallbackColliderConstruit([this]() {
			construiesteInformatieColiziuniInterna();
			});
	}
}

ActorInteractiv::~ActorInteractiv()
{
	if (informatieInteractiuniInterna)
		delete informatieInteractiuni;
}

reactphysics3d::RigidBody* ActorInteractiv::obtineCorpFizic()
{
	return corpFizic;
}

void ActorInteractiv::seteazaLocatie(glm::vec3 locatieNoua)
{
	vectorLocatie = locatieNoua;
	if (initializat) {
		reimprospateazaTransformareColiziuni();
	}
}

void ActorInteractiv::seteazaRotatie(glm::vec3 rotatieNoua)
{
	vectorRotatieEuler = rotatieNoua;
	if (initializat) {
		reimprospateazaTransformareColiziuni();
	}
}

void ActorInteractiv::seteazaScala(glm::vec3 scalaNoua)
{
	vectorScala = scalaNoua;
	if (initializat) {
		if (!informatieInteractiuniInterna) {
			informatieInteractiuni = informatieInteractiuni->copiaza();
			informatieInteractiuniInterna = true;
		}
		informatieInteractiuni->scaleaza(scalaNoua);
	}
}

void ActorInteractiv::reimprospateazaTransformareColiziuni()
{
	if (initializat) {
		reactphysics3d::Transform transformareNoua(Utilitati::convertesteVectorGlmLaReact3D(vectorLocatie), Utilitati::convertesteRotatieEulerLaReact3D(vectorRotatieEuler));
		corpFizic->setTransform(transformareNoua);
	}
}

void ActorInteractiv::construiesteInformatieColiziuniInterna()
{
	if (vectorScala == glm::vec3(1.f) || informatieInteractiuni == NULL) {
		informatieInteractiuniInterna = false;
	}
	else {
		informatieInteractiuni = informatieInteractiuni->copiaza();
		informatieInteractiuni->scaleaza(vectorScala);
		informatieInteractiuniInterna = true;
	}
	reactphysics3d::Transform transformare(Utilitati::convertesteVectorGlmLaReact3D(vectorLocatie), Utilitati::convertesteRotatieEulerLaReact3D(vectorRotatieEuler));

	MotorGrafic* motor = MotorGrafic::obtineMotorGrafic();
	auto lumeColiziuni = motor->obtineLumeColiziuni();

	corpFizic = lumeColiziuni->createRigidBody(transformare);
	corpFizic->setType(tipCorpFizic);
	if (informatieInteractiuni) {
		for (auto coliziuneCurenta : informatieInteractiuni->obtineCollidereReact()) {
			corpFizic->addCollider(coliziuneCurenta->formaGeometrica, coliziuneCurenta->pozitieFormaGeometrica);
		}
	}
	initializat = true;
}
