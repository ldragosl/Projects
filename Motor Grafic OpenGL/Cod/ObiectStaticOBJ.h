#pragma once
#include "ObiectStaticNormale.h"
class ObiectStaticOBJ : public ObiectStaticNormale
{
public:
	ObiectStaticOBJ(std::string pathFisier);

	~ObiectStaticOBJ();
	void elibereazaMemorie();
protected:
	virtual void incarcaResursa() override;
	virtual void initializeazaResursa() override;
private:
	std::vector< glm::vec2 > uv;
	std::vector< glm::vec3 > normale;
	std::vector< glm::vec3 > tangente;
	std::vector< glm::vec3 > bitangente;
	std::vector< int > indiciTriunghiuri;
};