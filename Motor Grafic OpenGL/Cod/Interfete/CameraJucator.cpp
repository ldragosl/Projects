//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include "CameraJucator.h"

#include <GLFW/glfw3.h>
#include "Utilitati.h"
#include "CoreMotor/MotorGrafic.h"
#include "reactphysics3d\reactphysics3d.h"

CameraJucator::CameraJucator()
{
	matriceProiectie = glm::perspective(glm::radians(fov), (float)(glfwGetVideoMode(glfwGetPrimaryMonitor())->width) / (float)(glfwGetVideoMode(glfwGetPrimaryMonitor())->height), 0.1f, 10000.0f);

	//initializari
	pozitieCamera = glm::vec3(0.f, 1.6f, 0.f);
	unghiCameraOrizontal = glm::pi<float>();
	unghiCameraVertical = 0.0f;
}

//implementam formulele standard pentru a transforma rotatia intr-un vector normalizat
glm::vec3 CameraJucator::obtineVectorInainte() {
	return glm::vec3(cos(unghiCameraVertical) * sin(unghiCameraOrizontal), sin(unghiCameraVertical), cos(unghiCameraVertical) * cos(unghiCameraOrizontal));
}

glm::vec3 CameraJucator::obtineVectorDreapta() {
	return glm::vec3(sin(unghiCameraOrizontal - glm::pi<float>() / 2.0f), 0, cos(unghiCameraOrizontal - glm::pi<float>() / 2.0f));
}

glm::vec3 CameraJucator::obtineVectorSus() {
	//vectorul "sus" este perpendicular pe "dreapta" si "inainte": asa ca il calculam ca si produs vectorial
	return glm::cross(obtineVectorDreapta(), obtineVectorInainte());
}

glm::vec3 CameraJucator::obtineLocatieCamera()
{
	return pozitieCamera;
}

void CameraJucator::seteazaLocatieCamera(const glm::vec3& locatieNoua)
{
	pozitieCamera = locatieNoua;
}

glm::mat4 CameraJucator::obtineMatriceProiectie()
{
	return matriceProiectie;
}

glm::mat4 CameraJucator::obtineMatriceVizualizare()
{
	return glm::lookAt(pozitieCamera, pozitieCamera + obtineVectorInainte(), obtineVectorSus());
}