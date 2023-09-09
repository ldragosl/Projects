//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include <glm/gtx/transform.hpp>

class Harta;
struct GLFWwindow;
class CameraJucator;
class ActorStatic;
namespace reactphysics3d {
	class PhysicsCommon;
	class PhysicsWorld;
}

//singleton
class MotorGrafic
{
public:
	static MotorGrafic* obtineMotorGrafic();

	void schimbaHarta(Harta* harta);
	void schimbaCamera(CameraJucator* camera);

	virtual bool poateContinuaRandarea();
	virtual void loopPrincipal();

	glm::mat4 obtineMatriceProiectie();
	glm::mat4 obtineMatriceVizualizare();

	reactphysics3d::PhysicsCommon* obtineGestionatorColiziuni();
	reactphysics3d::PhysicsWorld* obtineLumeColiziuni();

	GLFWwindow* obtineFereastraPrincipala();

	void debugareColiziuni();
	void opresteDebugareColiziuni();

	Harta* obtineHarta();
	CameraJucator* obtineCameraJucator();

	double obtineTimpTotalRulare();

private:
	MotorGrafic(Harta* hartaStart, int antialiasing = 2, int versiuneMinoraGL = 3, int versiuneMajoraGL = 3);

	static MotorGrafic* referintaSingleton;

	Harta* harta;

	void _calculareColiziuniAsync();

	double timpUltimaRandare;

	//Timpul pentru calcularea cadrului trecut
	double timpRandareCadru;

	double timpTotalRulare;

	GLFWwindow* fereastraPrincipala;
	CameraJucator* cameraJucator;

	ActorStatic* debugatorColiziuni;

	reactphysics3d::PhysicsCommon* gestionatorColiziuni;
	reactphysics3d::PhysicsWorld* lumeColiziuni;
};

