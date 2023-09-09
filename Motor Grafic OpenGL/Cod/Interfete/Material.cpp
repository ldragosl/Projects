#include "Material.h"

int Material::indexUltimMaterial = 0;

int Material::obtineIndexMaterial()
{
	return indexMaterial;
}

Material::Material()
{
	indexMaterial = indexUltimMaterial++;
	shader = NULL;
}
