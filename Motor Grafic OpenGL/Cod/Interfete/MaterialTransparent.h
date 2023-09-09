#include "Material.h"

class MaterialTransparent : public Material {
protected:
	MaterialTransparent();
private:
	// materialele transparente vor avea alt tip de indexare: ele trebuie sa fie ultimele!
	static int indexUltimMaterialTransparent;
};