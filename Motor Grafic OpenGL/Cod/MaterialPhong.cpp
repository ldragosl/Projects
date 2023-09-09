//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once

#include "MaterialPhong.h"

#include <GL/glew.h>

#include "Interfete\CameraJucator.h"
#include "Utilitati.h"
#include "Interfete\Textura.h"
#include "Shader.h"
#include "CoreMotor/MotorGrafic.h"
#include "Interfete\Harta.h"
#include "directivePreprocesare.h"

MaterialPhong::MaterialPhong(Shader* shader, Textura* texturaDifuza, Textura* texturaNormala)
{
	this->shader = shader;
	shaderIntern = false;
	intensitateSpeculara = 20.f;

	this->texturaDifuza = texturaDifuza;
	this->texturaNormala = texturaNormala;
}

MaterialPhong::MaterialPhong(const char* caleFisierShaderVertex, const char* caleFisierShaderFragment, Textura* texturaDifuza, Textura* texturaNormala)
{
	shader = new Shader(caleFisierShaderVertex, caleFisierShaderFragment);
	shaderIntern = true;
	intensitateSpeculara = 20.f;

	this->texturaDifuza = texturaDifuza;
	this->texturaNormala = texturaNormala;
}

MaterialPhong::MaterialPhong(Textura* texturaDifuza, Textura* texturaNormala)
{
	shader = new Shader(ShaderPredefinit("ShaderVertexPhong.glsl"), ShaderPredefinit("ShaderFragmentPhong.glsl"));
	shaderIntern = true;
	intensitateSpeculara = 20.f;

	this->texturaDifuza = texturaDifuza;
	this->texturaNormala = texturaNormala;
}

MaterialPhong::~MaterialPhong()
{
	//nu stergem shaderul decat daca a fost generat de aceasta clasa
	if(shaderIntern)
		delete shader;
}

void MaterialPhong::randeazaMaterial(glm::mat4 matriceModel, glm::vec2 scalaUV, bool schimbareMaterial)
{
	if (texturaDifuza->esteUtilizabila() && texturaNormala->esteUtilizabila()) {
		if (schimbareMaterial)
			glUseProgram(shader->obtineBufferProgram());

		// obtinem referinte catre atributele shader
		GLuint atributTextura = glGetUniformLocation(shader->obtineBufferProgram(), "SamplerTextura");
		GLuint atributTexturaNormala = glGetUniformLocation(shader->obtineBufferProgram(), "SamplerTexturaNormala");
		GLuint atributMatriceModelVizualizareProiectie = glGetUniformLocation(shader->obtineBufferProgram(), "matMVP");
		GLuint atributMatriceModel = glGetUniformLocation(shader->obtineBufferProgram(), "matModel");
		GLuint atributMatriceVizualizare = glGetUniformLocation(shader->obtineBufferProgram(), "matVizualizare");
		GLuint atributPozitieLumina = glGetUniformLocation(shader->obtineBufferProgram(), "PozitieBec");
		GLuint atributCuloareLumina = glGetUniformLocation(shader->obtineBufferProgram(), "CuloareLumina");
		GLuint atributIntensitateLumina = glGetUniformLocation(shader->obtineBufferProgram(), "IntensitateLumina");
		GLuint atributMatriceModelVizualizare = glGetUniformLocation(shader->obtineBufferProgram(), "MV");
		GLuint atributScalaUV = glGetUniformLocation(shader->obtineBufferProgram(), "scalaUV");
		GLuint atributIntensitateSpeculara = glGetUniformLocation(shader->obtineBufferProgram(), "IntensitateReflexie");

		if (schimbareMaterial) {
			// punem textura difuza (de culoare) in unitatea de texturare nr 0 a placii video
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturaDifuza->obtineBufferImagine());
			glUniform1i(atributTextura, 0);

			// punem textura normala in unitatea de texturare nr 1 a placii video
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texturaNormala->obtineBufferImagine());
			glUniform1i(atributTexturaNormala, 1);
		}

		//calculam matricile neceare shaderului
		glm::mat4 matriceVizualizare = MotorGrafic::obtineMotorGrafic()->obtineMatriceVizualizare();
		glm::mat4 matriceModelVizualizare = matriceVizualizare * matriceModel;
		glm::mat4 matriceModelVizualizareProiectie = MotorGrafic::obtineMotorGrafic()->obtineMatriceProiectie() * matriceModelVizualizare;
		//matricea MVP este una 4x4 - anumite parti ale shaderului au nevoie doar de coltul stanga sus
		glm::mat3 matriceModelVizualizareFaraTranslatie = glm::mat3(matriceModelVizualizare);

		//trimitem catre shader matricile calculate
		glUniformMatrix4fv(atributMatriceModelVizualizareProiectie, 1, GL_FALSE, &matriceModelVizualizareProiectie[0][0]);
		glUniformMatrix4fv(atributMatriceModel, 1, GL_FALSE, &matriceModel[0][0]);
		glUniformMatrix4fv(atributMatriceVizualizare, 1, GL_FALSE, &matriceVizualizare[0][0]);
		glUniformMatrix3fv(atributMatriceModelVizualizare, 1, GL_FALSE, &matriceModelVizualizareFaraTranslatie[0][0]);

		glUniform2fv(atributScalaUV, 1, &scalaUV[0]);

		Harta* hartaActiva = MotorGrafic::obtineMotorGrafic()->obtineHarta();

		glm::vec3 pozitieLumina = hartaActiva->obtinePozitieLumina();
		glUniform3fv(atributPozitieLumina, 1, &pozitieLumina[0]);

		glm::vec3 culoareLumina = hartaActiva->obtineCuloareLumina();
		glUniform3fv(atributCuloareLumina, 1, &culoareLumina[0]);

		float intensitateLumina = hartaActiva->obtineIntensitateLumina();
		glUniform1f(atributIntensitateLumina, intensitateLumina);

		glUniform1f(atributIntensitateSpeculara, intensitateSpeculara);
	}
}

void MaterialPhong::seteazaIntensitateSpeculara(float intensitate)
{
	intensitateSpeculara = intensitate;
}
