//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include "Interfete\MaterialTransparent.h"

class Textura;
class Shader;

class MaterialText : public MaterialTransparent
{
public:
	MaterialText();
	~MaterialText();

	virtual void randeazaMaterial(glm::mat4 matriceModel, glm::vec2 scalaUV, bool schimbareMaterial) override;

private:
	Shader* shader;
	Textura* texturaFont;
};

