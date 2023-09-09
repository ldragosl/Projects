#include "InformatieInteractiuniCub.h"

#include <limits>
#include <reactphysics3d\reactphysics3d.h>

#include "CoreMotor/MotorGrafic.h"
#include "ObiectStatic.h"

InformatieInteractiuniCub::InformatieInteractiuniCub(InformatieInteractiuniCub* copieInitiala)
{
	obiectBazaColiziuni = copieInitiala->obiectBazaColiziuni;
	if (copieInitiala->esteInitializat) {
		ShapeColiziuneCuPozitie* copieColliderCub = new ShapeColiziuneCuPozitie();
		copieColliderCub->pozitieFormaGeometrica = copieInitiala->colliderCub->pozitieFormaGeometrica;
		dimensiuniCub = copieInitiala->dimensiuniCub;
		copieColliderCub->formaGeometrica = MotorGrafic::obtineMotorGrafic()->obtineGestionatorColiziuni()->createBoxShape(copieInitiala->dimensiuniCub);

		colliderCub = copieColliderCub;
		esteInitializat = true;
	}
	else {
		colliderCub = NULL;
		obiectBazaColiziuni->adaugaCallabackResursaUtilizabila([this]() {
			this->construiesteInformatieInteractiune();
		});
	}
}

InformatieInteractiuniCub::InformatieInteractiuniCub(ObiectStatic* obiectBaza)
{
	obiectBazaColiziuni = obiectBaza;

	colliderCub = NULL;
	obiectBazaColiziuni->adaugaCallabackResursaUtilizabila([this]() {
		this->construiesteInformatieInteractiune(); 
	});
}

InformatieInteractiuniCub::~InformatieInteractiuniCub()
{
	reactphysics3d::BoxShape* referintaCutie = static_cast<reactphysics3d::BoxShape*>(colliderCub->formaGeometrica);
	MotorGrafic::obtineMotorGrafic()->obtineGestionatorColiziuni()->destroyBoxShape(referintaCutie);
	delete colliderCub;
} 

void InformatieInteractiuniCub::construiesteInformatieInteractiune()
{
	constexpr float nrMax = std::numeric_limits<float>::max();
	//cautam cel mai sus punct si cel mai jos punct, pe toate axele, pentru a putea stabili dimensiunea cutiei ce va inconjura obiectul
	reactphysics3d::Vector3 pozitieMinima(nrMax, nrMax, nrMax);
	reactphysics3d::Vector3 pozitieMaxima;
	for (glm::vec3 vectorCurent : *obiectBazaColiziuni->obtinePuncte3D()) {
		if (pozitieMaxima.x < vectorCurent.x)
			pozitieMaxima.x = vectorCurent.x;
		if (pozitieMaxima.y < vectorCurent.y)
			pozitieMaxima.y = vectorCurent.y;
		if (pozitieMaxima.z < vectorCurent.z)
			pozitieMaxima.z = vectorCurent.z;

		if (pozitieMinima.x > vectorCurent.x)
			pozitieMinima.x = vectorCurent.x;
		if (pozitieMinima.y > vectorCurent.y)
			pozitieMinima.y = vectorCurent.y;
		if (pozitieMinima.z > vectorCurent.z)
			pozitieMinima.z = vectorCurent.z;
	}
	dimensiuniCub = (pozitieMaxima - pozitieMinima) / 2.f;
	reactphysics3d::Vector3 centruCub = (pozitieMaxima + pozitieMinima) / 2.f;
	reactphysics3d::CollisionShape* coliziuneCub = MotorGrafic::obtineMotorGrafic()->obtineGestionatorColiziuni()->createBoxShape(dimensiuniCub);
	reactphysics3d::Transform locatie(centruCub, reactphysics3d::Quaternion::identity());
	colliderCub = new ShapeColiziuneCuPozitie(coliziuneCub, locatie);

	esteInitializat = true;

	for (auto callbackCurent : callbackColliderConstruit) {
		callbackCurent();
	}
	callbackColliderConstruit.clear();
}

std::vector<ShapeColiziuneCuPozitie*> InformatieInteractiuniCub::obtineCollidereReact()
{
	std::vector<ShapeColiziuneCuPozitie*> collidere;
	collidere.push_back(colliderCub);
	return collidere;
}

InformatieInteractiuni* InformatieInteractiuniCub::copiaza()
{
	return new InformatieInteractiuniCub(this);
}

void InformatieInteractiuniCub::scaleaza(glm::vec3 scalaNoua)
{
	reactphysics3d::BoxShape* referintaCutie = static_cast<reactphysics3d::BoxShape*>(colliderCub->formaGeometrica);
	reactphysics3d::Vector3 copieExtent = dimensiuniCub;
	copieExtent.x *= scalaNoua.x;
	copieExtent.y *= scalaNoua.y;
	copieExtent.z *= scalaNoua.z;
	referintaCutie->setHalfExtents(copieExtent);
}
