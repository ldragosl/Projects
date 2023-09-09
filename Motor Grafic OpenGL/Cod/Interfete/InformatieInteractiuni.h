#pragma once
#include <vector>
#include <functional>
#include <glm/gtx/transform.hpp>
#include <reactphysics3d\mathematics\Transform.h>

namespace reactphysics3d {
	class CollisionShape;
}

class ObiectStatic;

struct ShapeColiziuneCuPozitie {
	ShapeColiziuneCuPozitie(reactphysics3d::CollisionShape* formaGeometrica, reactphysics3d::Transform& pozitieFormaGeometrica);
	ShapeColiziuneCuPozitie();
	reactphysics3d::CollisionShape* formaGeometrica;
	reactphysics3d::Transform pozitieFormaGeometrica;
};

class InformatieInteractiuni {
public:
	virtual void construiesteInformatieInteractiune() = 0;
	virtual std::vector<ShapeColiziuneCuPozitie*> obtineCollidereReact() = 0;
	virtual InformatieInteractiuni* copiaza() = 0;
	virtual void scaleaza(glm::vec3 scalaNoua) = 0;

	bool obtineEsteInitializat();

	void adaugaCallbackColliderConstruit(std::function<void()> callback);
protected:
	InformatieInteractiuni();
	ObiectStatic* obiectBazaColiziuni;
	bool esteInitializat;

	std::vector<std::function<void()>> callbackColliderConstruit;
};