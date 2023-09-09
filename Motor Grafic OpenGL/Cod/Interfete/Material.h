#pragma once
#include <glm/gtx/transform.hpp>

class Shader;

class Material {
public:
	virtual void randeazaMaterial(glm::mat4 matriceModel, glm::vec2 scalaUV, bool schimbareMaterial) = 0;
	virtual void ruleazaPostRandare() {};

	int obtineIndexMaterial();
protected:
	Material();
	Shader* shader;
	int indexMaterial;
	static int indexUltimMaterial;
};