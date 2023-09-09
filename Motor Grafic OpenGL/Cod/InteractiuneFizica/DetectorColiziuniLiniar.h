#pragma once
#include "reactphysics3d\collision\RaycastInfo.h"
#include <reactphysics3d\decimal.h>

class DetectorColiziuniLinie : public reactphysics3d::RaycastCallback
{
public:
	DetectorColiziuniLinie(const reactphysics3d::Vector3& locatieStart, const reactphysics3d::Vector3& locatieFinala);

	reactphysics3d::CollisionBody* obtineObiectLovit();

	virtual reactphysics3d::decimal notifyRaycastHit(const reactphysics3d::RaycastInfo& informatieColiziune) override;
private:
	reactphysics3d::CollisionBody* obiectLovit;
};

