#include "MaterialText.h"

#include <GL/glew.h>

#include "Shader.h"
#include "TexturaBMP.h"
#include "directivePreprocesare.h"
#include "CoreMotor\ManagerResurse.h"

MaterialText::MaterialText()
{
	shader = new Shader(ShaderPredefinit("ShaderVertexText.glsl"), ShaderPredefinit("ShaderFragmentText.glsl"));
	texturaFont = ManagerResurse::obtineManagerResurse()->adaugaTextura(new TexturaBMP(ShaderPredefinit("Font.bmp")));
}

MaterialText::~MaterialText()
{
	delete shader;
}

void MaterialText::randeazaMaterial(glm::mat4 matriceModel, glm::vec2 scalaUV, bool schimbareMaterial)
{
	if (schimbareMaterial) {
		glUseProgram(shader->obtineBufferProgram());

		// obtinem referinte catre atributele shader
		GLuint atributTextura = glGetUniformLocation(shader->obtineBufferProgram(), "samplerTextura");

		// punem textura difuza (de culoare) in unitatea de texturare nr 0 a placii video
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturaFont->obtineBufferImagine());
		glUniform1i(atributTextura, 0);
	}
}
