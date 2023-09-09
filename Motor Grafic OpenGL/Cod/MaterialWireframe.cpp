#include "MaterialWireframe.h"

#include <GL/glew.h>

#include "Utilitati.h"
#include "Shader.h"
#include "CoreMotor/MotorGrafic.h"
#include "directivePreprocesare.h"

MaterialWireframe::MaterialWireframe() : MaterialWireframe(1.f, 0.f, 0.f) {}

MaterialWireframe::MaterialWireframe(float canalRosu, float canalVerde, float canalAlbastru)
{
	shader = new Shader(ShaderPredefinit("ShaderVertexWireframe.glsl"), ShaderPredefinit("ShaderFragmentWireframe.glsl"));
	culoareWireframe = glm::vec3(canalRosu, canalVerde, canalAlbastru);
}

MaterialWireframe::~MaterialWireframe()
{
	delete shader;
}

void MaterialWireframe::randeazaMaterial(glm::mat4 matriceModel, glm::vec2 scalaUV, bool schimbareMaterial)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);
	if (schimbareMaterial)
		glUseProgram(shader->obtineBufferProgram());

	// obtinem referinte catre atributele shader
	GLuint atributMatriceModelVizualizareProiectie = glGetUniformLocation(shader->obtineBufferProgram(), "matMVP");
	GLuint atributCuloare = glGetUniformLocation(shader->obtineBufferProgram(), "culoareWireframe");

	glm::mat4 matriceModelVizualizareProiectie = MotorGrafic::obtineMotorGrafic()->obtineMatriceProiectie() * MotorGrafic::obtineMotorGrafic()->obtineMatriceVizualizare() * matriceModel;

	//trimitem catre shader matricile calculate
	glUniformMatrix4fv(atributMatriceModelVizualizareProiectie, 1, GL_FALSE, &matriceModelVizualizareProiectie[0][0]);


	glUniform3fv(atributCuloare, 1, &culoareWireframe[0]);
}

void MaterialWireframe::ruleazaPostRandare()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
}
