#pragma once
#include "ObiectStatic.h"
class TextRandabil : public ObiectStatic
{
	float pozitieX;
	float pozitieY;
	float marimeText;
	virtual void incarcaResursa() override;
	virtual void initializeazaResursa() override;

	std::vector< glm::vec2 > puncte2D;
	std::vector< glm::vec2 > uv;
	std::vector< int > indiciTriunghiuri;
public:
	virtual void randare();

	TextRandabil(std::string text, float pozitieX, float pozitieY, float marimeText);

	void schimbaText(std::string textNou);

	void elibereazaMemorie();
	~TextRandabil();
};

