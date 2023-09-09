//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include "Utilitati.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <reactphysics3d\reactphysics3d.h>

void Utilitati::convertireRGB(float& rosu, float& verde, float& albastru)
{
	rosu = convertireCanalRGB(rosu);
	verde = convertireCanalRGB(verde);
	albastru = convertireCanalRGB(albastru);
}

float Utilitati::convertireCanalRGB(const float& canalRGB)
{
	return canalRGB / 255.f;
}

glm::mat4 Utilitati::conversieRotatieEulerLaMatrice(glm::vec3 rotatieEuler)
{
	glm::quat quaternion = rotatieEuler;
	return glm::toMat4(quaternion);
}

float Utilitati::numarAleator()
{
	return float(rand()) / float(RAND_MAX);
}

reactphysics3d::Vector3 Utilitati::convertesteVectorGlmLaReact3D(const glm::vec3& vectorGl)
{
	return reactphysics3d::Vector3(vectorGl.x, vectorGl.y, vectorGl.z);
}

reactphysics3d::Quaternion Utilitati::convertesteRotatieEulerLaReact3D(const glm::vec3& rotatieEuler)
{
	glm::quat quaternionGl = rotatieEuler;
	return reactphysics3d::Quaternion(quaternionGl.x, quaternionGl.y, quaternionGl.z, quaternionGl.w);
}

glm::vec3 Utilitati::convertesteVectorReact3DLaGlm(const reactphysics3d::Vector3& vectorReact)
{
	return glm::vec3(vectorReact.x, vectorReact.y, vectorReact.z);
}

std::string Utilitati::locatieEngine()
{
	std::string fisierUtilitati = __FILE__;
	std::string parinte = fisierUtilitati.substr(0, fisierUtilitati.find_last_of("/\\"));
	parinte = parinte.substr(0, parinte.find_last_of("/\\")) + "\\";
	return parinte;
}
