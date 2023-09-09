#pragma once
#include "Interfete/Material.h"
class MaterialWireframe : public Material
{
public:
	MaterialWireframe();
	MaterialWireframe(float canalRosu, float canalVerde, float canalAlbastru);
	~MaterialWireframe();

	virtual void randeazaMaterial(glm::mat4 matriceModel, glm::vec2 scalaUV, bool schimbareMaterial) override;
	virtual void ruleazaPostRandare() override;
private:
	glm::vec3 culoareWireframe;
};

