#include "DetectorColiziuniLiniar.h"

#include <reactphysics3d\reactphysics3d.h>

#include "CoreMotor/MotorGrafic.h"
#include "ActorInteractiv.h"

DetectorColiziuniLinie::DetectorColiziuniLinie(const reactphysics3d::Vector3& locatieStart, const reactphysics3d::Vector3& locatieFinala)
{
    obiectLovit = NULL;
    reactphysics3d::Ray linieTestare(locatieStart, locatieFinala);
    MotorGrafic::obtineMotorGrafic()->obtineLumeColiziuni()->raycast(linieTestare, this);
}

reactphysics3d::CollisionBody* DetectorColiziuniLinie::obtineObiectLovit()
{
    return obiectLovit;
}

reactphysics3d::decimal DetectorColiziuniLinie::notifyRaycastHit(const reactphysics3d::RaycastInfo& informatieColiziune)
{
    obiectLovit = informatieColiziune.body;
    return reactphysics3d::decimal(0.f);
}
