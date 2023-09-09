#define _CRT_SECURE_NO_WARNINGS
//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#include "CoreMotor/MotorGrafic.h"

#include <reactphysics3d/reactphysics3d.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include "directivePreprocesare.h"
#include "Utilitati.h"
#include "Interfete\CameraJucator.h"
#include "ActorObiectStatic.h"
#include "InteractiuneFizica\ObiectDebugareColiziuni.h"
#include "Interfete\Harta.h"
#include "MaterialWireframe.h"
#include "ManagerResurse.h"

#include <thread>

MotorGrafic* MotorGrafic::referintaSingleton = NULL;

MotorGrafic* MotorGrafic::obtineMotorGrafic()
{
	if (!referintaSingleton)
		referintaSingleton = new MotorGrafic(NULL);

	return referintaSingleton;
}

MotorGrafic::MotorGrafic(Harta* hartaStart, int antialiasing, int versiuneMinora, int versiuneMajora)
{
	debugatorColiziuni = NULL;
	harta = hartaStart;

	if (!glfwInit()) {
		std::cout << "Nu s-a putut initia glfw.";
		exit(-1);
	}

	srand(time(0));

	//antialiasing 
	glfwWindowHint(GLFW_SAMPLES, antialiasing);
	// Folosim OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versiuneMinora);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versiuneMajora);
	// Folosim profilul "modern", nu cel de compatibilitate
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitorPrincipal = glfwGetPrimaryMonitor();
	const GLFWvidmode* modVideo = glfwGetVideoMode(monitorPrincipal);
	//creem o fereastra care va acoperi intreg ecranul primar
	fereastraPrincipala = glfwCreateWindow(modVideo->width, modVideo->height, "Motor grafic", glfwGetPrimaryMonitor(), NULL);
	
	// o fereastra care nu controleaza intreg monitorul e mai usor de debugat
	//fereastraPrincipala = glfwCreateWindow(modVideo->width, modVideo->height, "Motor grafic", NULL, NULL);

	if (fereastraPrincipala == NULL) {
		std::cout << "Nu s-a putut crea o fereastra. Poate trebuie folosita alta versiune OpenGL?";
		glfwTerminate();
		exit(-1);
	}
	//informam glfw ca fereastra creata este cea pe care se va opera
	glfwMakeContextCurrent(fereastraPrincipala);

	if (glewInit() != GLEW_OK) {
		std::cout << "Eroare la initializarea GLEW. ";
		exit(-1);
	}

	//functia glClear() va colora toti pixelii cu un albastru asemanator culorii cerului
	float fundalRosu = 92.f;
	float fundalVerde = 124.f;
	float fundalAlbastru = 231.f;
	Utilitati::convertireRGB(fundalRosu, fundalVerde, fundalAlbastru);
	glClearColor(fundalRosu, fundalVerde, fundalAlbastru, 0.0f);

	//nu lasam mouse-ul sa isi schimbe pozitia de la centru
	//in caz contrar, mouse-ul va putea parasi fereastra
	glfwSetCursorPos(fereastraPrincipala, modVideo->width / 2, modVideo->height / 2);

	//blocam mouse-ul pentru a nu putea iesi din fereastra
	glfwSetInputMode(fereastraPrincipala, GLFW_STICKY_KEYS, GL_TRUE);
	//ascundem cursorul mouse-ului
	glfwSetInputMode(fereastraPrincipala, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// solicitam opengl sa realizeze testul de adancime (adica sa nu randeze triunghiurle mai departate de camera peste cele mai apropiate)
	//daca nu am activa asta, am vedea prin unele obiecte
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// dezactivam randarea dubla a obiectelor. O singura fata a fiecarui poligon va fii randata
	glEnable(GL_CULL_FACE);

	//permitem randarea de obiecte cu sectiuni transparente
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cameraJucator = NULL;

	// am stocat vertecsii intr-un alt buffer - acesta va fii gol. Il initializam totusi deoarece in caz contrar vor aparea erori
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	gestionatorColiziuni = new reactphysics3d::PhysicsCommon();
	lumeColiziuni = gestionatorColiziuni->createPhysicsWorld();

#ifdef DebugareColiziuni
	lumeColiziuni->setIsDebugRenderingEnabled(true);
	reactphysics3d::DebugRenderer& debuggerColiziuni = lumeColiziuni->getDebugRenderer();
	debuggerColiziuni.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
#endif

	timpUltimaRandare = glfwGetTime();
	timpRandareCadru = 0.f;
	timpTotalRulare = 0.f;

	if(harta)
		harta->incepereHarta();
}

void MotorGrafic::_calculareColiziuniAsync()
{
	lumeColiziuni->update(timpRandareCadru);
}

void MotorGrafic::schimbaHarta(Harta* hartaStart)
{
	if(harta)
		delete harta;
	harta = hartaStart;
	harta->incepereHarta();
}

void MotorGrafic::schimbaCamera(CameraJucator* camera)
{
	cameraJucator = camera;
}

bool MotorGrafic::poateContinuaRandarea()
{
	//cat timp tasta "esc" nu este apasata, si nu este inchisa fereastra in alt mod (ex: apasarea alt-f4) continuam 
	return glfwGetKey(fereastraPrincipala, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(fereastraPrincipala) == 0;
}

void MotorGrafic::loopPrincipal()
{
	//daca harta sau camera nu este initializata, nu putem randa harta
	if (harta && cameraJucator) {
		//procesam apasarile de taste
		//este foarte importanta ordinea apelurilor (input lag in alt caz)
		glfwPollEvents();
		double timpActual = glfwGetTime();
		timpRandareCadru = timpActual - timpUltimaRandare;
		timpUltimaRandare = timpActual;
		timpTotalRulare += timpRandareCadru;

		cameraJucator->procesareInput(timpRandareCadru);

		ManagerResurse::obtineManagerResurse()->actualieazaResurse();

		std::thread threadCalculareColiziuni(&MotorGrafic::_calculareColiziuniAsync, this);
		
		harta->randeazaHarta(timpRandareCadru);

		threadCalculareColiziuni.join();

#ifdef DebugareColiziuni
		MotorGrafic::obtineMotorGrafic()->debugareColiziuni();
#endif

		harta->tick(timpRandareCadru);

		//folosim double buffering - cat timp cadrul este randat pe cadrul invizibil, cadrul celalalt este pe ecran.
		glfwSwapBuffers(fereastraPrincipala);
	}
}

glm::mat4 MotorGrafic::obtineMatriceProiectie()
{
	return cameraJucator ? cameraJucator->obtineMatriceProiectie() : glm::mat4();
}

glm::mat4 MotorGrafic::obtineMatriceVizualizare()
{
	return cameraJucator ? cameraJucator->obtineMatriceVizualizare() : glm::mat4();
}

reactphysics3d::PhysicsCommon* MotorGrafic::obtineGestionatorColiziuni()
{
	return gestionatorColiziuni;
}

reactphysics3d::PhysicsWorld* MotorGrafic::obtineLumeColiziuni()
{
	return lumeColiziuni;
}

GLFWwindow* MotorGrafic::obtineFereastraPrincipala()
{
	return fereastraPrincipala;
}

void MotorGrafic::debugareColiziuni()
{
	//adaugam mesh-ul actualizat
	if (debugatorColiziuni == NULL) {
		debugatorColiziuni = new ActorStatic(ObiectDebugareColiziuni::obtineObiectDebugareColiziuni(), new MaterialWireframe());
		harta->obiecteDeRandat.emplace(debugatorColiziuni);
	}
	else {
		ObiectDebugareColiziuni::obtineObiectDebugareColiziuni()->reimprospatare();
	}
}

void MotorGrafic::opresteDebugareColiziuni()
{
	if(debugatorColiziuni != NULL)
		harta->obiecteDeRandat.erase(debugatorColiziuni);
}

Harta* MotorGrafic::obtineHarta()
{
	return harta;
}

CameraJucator* MotorGrafic::obtineCameraJucator()
{
	return cameraJucator;
}

double MotorGrafic::obtineTimpTotalRulare()
{
	return timpTotalRulare;
}
