//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include <glm/gtx/transform.hpp>

struct GLFWwindow;
class ActorInteractiv;

//singleton
class CameraJucator {
public:
	CameraJucator();

	glm::mat4 obtineMatriceProiectie();
	glm::mat4 obtineMatriceVizualizare();

	//aceasta functie trebuie chemata in fiecare update
	virtual void procesareInput(float timpRandareCadru) = 0;

	// cei 3 vectori ai camerei
	inline glm::vec3 obtineVectorInainte();
	inline glm::vec3 obtineVectorDreapta();
	inline glm::vec3 obtineVectorSus();

	glm::vec3 obtineLocatieCamera();
	void seteazaLocatieCamera(const glm::vec3& locatieNoua);

	float vitezaMiscareJucator = 10.0f; // in metri / secunda
	float senzitivitateMouse = 0.4f; // in radiani / secunda

protected:
	glm::vec3 pozitieCamera;

	float unghiCameraOrizontal;
	float unghiCameraVertical;

	glm::mat4 matriceProiectie;

	// Unghiul de vizualizare (Field of View)
	const float fov = 60.0f;
};