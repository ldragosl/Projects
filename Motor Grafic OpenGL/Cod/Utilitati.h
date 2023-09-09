//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once

#include <glm/gtx/transform.hpp>
#include <string>
#include "reactphysics3d\mathematics\Vector3.h"

class CameraJucator;
struct GLFWwindow;
struct GLFWmonitor;
typedef unsigned int GLuint;
namespace reactphysics3d {
	struct Quaternion;
}

namespace Utilitati{
	void convertireRGB(float &rosu, float &verde, float& albastru);
	inline float convertireCanalRGB(const float& canalRGB);

	glm::mat4 conversieRotatieEulerLaMatrice(glm::vec3);

	/**
		Numar aleator intre 0 si 1
	*/
	float numarAleator();
	/**
		Numar aleator intre a si b
	*/
	template<class T>
	float numarAleator(T a, T b) { return numarAleator() * (b - a) + a; }

	reactphysics3d::Vector3 convertesteVectorGlmLaReact3D(const glm::vec3& vectorGl);
	reactphysics3d::Quaternion convertesteRotatieEulerLaReact3D(const glm::vec3& rotatieEuler);

	glm::vec3 convertesteVectorReact3DLaGlm(const reactphysics3d::Vector3& vectorReact);

	std::string locatieEngine();
};