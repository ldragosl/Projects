#include "MaterialTransparent.h"

int MaterialTransparent::indexUltimMaterialTransparent = ~(1<<31);//0x7FFFFFFF;

MaterialTransparent::MaterialTransparent()
{
	--indexUltimMaterial;
	indexMaterial = indexUltimMaterialTransparent--;
}
