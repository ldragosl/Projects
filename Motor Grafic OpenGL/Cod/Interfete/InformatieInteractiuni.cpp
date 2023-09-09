#include "InformatieInteractiuni.h"

#include "reactphysics3d\reactphysics3d.h"
#include "CoreMotor/MotorGrafic.h"

ShapeColiziuneCuPozitie::ShapeColiziuneCuPozitie(reactphysics3d::CollisionShape* formaGeometrica, reactphysics3d::Transform& pozitieFormaGeometrica)
{
	this->formaGeometrica = formaGeometrica;
	this->pozitieFormaGeometrica = pozitieFormaGeometrica;
}

ShapeColiziuneCuPozitie::ShapeColiziuneCuPozitie()
{
	formaGeometrica = NULL;
}

bool InformatieInteractiuni::obtineEsteInitializat()
{
	return esteInitializat;
}

void InformatieInteractiuni::adaugaCallbackColliderConstruit(std::function<void()> callback)
{
	if (esteInitializat)
		callback();
	else {
		callbackColliderConstruit.push_back(callback);
	}
}

InformatieInteractiuni::InformatieInteractiuni()
{
	obiectBazaColiziuni = NULL;
	esteInitializat = false;
}
