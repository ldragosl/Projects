#pragma once

typedef unsigned int GLuint;

//nu e necesara o interfata: shaderele pot fii doar GLSL
class Shader
{
public:
	Shader(const char* caleFisierShaderVertex, const char* caleFisierShaderFragment);
	GLuint incarcaShader(const char* caleFisierShaderVertex, const char* caleFisierShaderFragment);

	GLuint obtineBufferProgram();

	~Shader();
	void elibereazaMemorie();

private:
	static char* citesteCodSursaShader(const char* cale);
	static void verificareEroriCompilareShader(GLuint shader, bool legare = false);

	GLuint shaderCompilat;
};

