//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include "Interfete\Material.h"

class CameraJucator;
class Textura;
class Shader;

class MaterialPhong : public Material
{
public:
	MaterialPhong(Shader* shader, Textura* texturaDifuza, Textura* texturaNormala);
	MaterialPhong(const char* caleFisierShaderVertex, const char* caleFisierShaderFragment, Textura* texturaDifuza, Textura* texturaNormala);
	MaterialPhong(Textura* texturaDifuza, Textura* texturaNormala);
	~MaterialPhong();

	virtual void randeazaMaterial(glm::mat4 matriceModel, glm::vec2 scalaUV, bool schimbareMaterial) override;

	void seteazaIntensitateSpeculara(float intensitate);

private:
	bool shaderIntern;

	float intensitateSpeculara;

	Textura* texturaDifuza;
	Textura* texturaNormala;
};

