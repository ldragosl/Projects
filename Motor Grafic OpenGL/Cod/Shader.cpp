#include "Shader.h"

#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "directivePreprocesare.h"

Shader::Shader(const char* caleFisierShaderVertex, const char* caleFisierShaderFragment)
{
	//declararea aceasta nu e o greseala; functia verifica daca shaderCompilat este 0 inainte sa se execute. 
	shaderCompilat = 0;
	incarcaShader(caleFisierShaderVertex, caleFisierShaderFragment);
}

Shader::~Shader()
{
	elibereazaMemorie();
}

GLuint Shader::obtineBufferProgram()
{
	return shaderCompilat;
}

void Shader::elibereazaMemorie()
{
	if (shaderCompilat != 0) {
		glDeleteProgram(shaderCompilat);
	}
	shaderCompilat = 0;
}


char* Shader::citesteCodSursaShader(const char* cale) {
	//deschidem fisierul de la final, in mod binar
	std::ifstream fisierIntrare(cale, std::ios::binary | std::ios::ate);
	if (!fisierIntrare.good())
		throw std::invalid_argument(std::string("Nu exista fisierul shader ") + cale);
	//pentru ca fisierul e deschis de la final, putem afla imediat dimensiunea acestuia
	int dimensiuneFisier = fisierIntrare.tellg();
	//acum ca stim dimensiunea, ne intoarcem la inceput pentru a-l citi propriu-zis
	fisierIntrare.clear();
	fisierIntrare.seekg(0);

	//alocam memorie suficienta pentru a citi fisierul + 1 pentru null-ul de inchidere
	char* codSursa = (char*)malloc(sizeof(char) * (dimensiuneFisier + 1));
	//citim codul sursa si il incheiem cu "null" 
	fisierIntrare.read(codSursa, dimensiuneFisier);
	codSursa[dimensiuneFisier] = '\0';

	fisierIntrare.close();

	return codSursa;
}

void Shader::verificareEroriCompilareShader(GLuint shader, bool legare) {
	int dimensiuneLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dimensiuneLog);
	if (dimensiuneLog > 0) {
		char* mesajEroare = (char*)malloc(dimensiuneLog + 1);
		if (legare)
			glGetProgramInfoLog(shader, dimensiuneLog, NULL, mesajEroare);
		else glGetShaderInfoLog(shader, dimensiuneLog, NULL, mesajEroare);
		mesajEroare[dimensiuneLog] = '\0';
		std::cout << mesajEroare << std::endl;
		free(mesajEroare);
		throw std::invalid_argument("Eroare la compilare shader.");
	}
}

GLuint Shader::incarcaShader(const char* caleFisierShaderVertex, const char* caleFisierShaderFragment) {
	elibereazaMemorie();

	//cream shaderul OpenGL
	GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
	//citim codul sursa din fisierul dat ca parametru
	char* codSursaVertex = citesteCodSursaShader(caleFisierShaderVertex);

	//trimitem sursa catre OpenGL
	glShaderSource(shaderVertex, 1, &codSursaVertex, NULL);
	//compilam sursa trimisa
	glCompileShader(shaderVertex);
	//eliberam memoria creata
	free(codSursaVertex);

#ifdef Debugare
	std::cout << "Se compileaza shaderul: " << caleFisierShaderVertex << std::endl;
	verificareEroriCompilareShader(shaderVertex);
#endif

	// Compile Fragment Shader
	GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
	char* codSursaFragment = citesteCodSursaShader(caleFisierShaderFragment);

	glShaderSource(shaderFragment, 1, &codSursaFragment, NULL);
	glCompileShader(shaderFragment);
	//eliberam memoria creata
	free(codSursaFragment);
#ifdef Debugare
	std::cout << "Se compileaza shaderul: " << caleFisierShaderFragment << std::endl;
	verificareEroriCompilareShader(shaderFragment);
#endif

	GLuint programGL = glCreateProgram();
	glAttachShader(programGL, shaderVertex);
	glAttachShader(programGL, shaderFragment);
	glLinkProgram(programGL);
#ifdef Debugare
	std::cout << "Se leaga shaderul\n";
	verificareEroriCompilareShader(programGL, true);
#endif

	// Shaderele au fost compilate si salvate in program, nu mai este nevoie sa le tinem in memorie
	glDetachShader(programGL, shaderVertex);
	glDetachShader(programGL, shaderFragment);
	glDeleteShader(shaderVertex);
	glDeleteShader(shaderFragment);

	shaderCompilat = programGL;

	return programGL;
}