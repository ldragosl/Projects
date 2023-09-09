#include "CameraClasificator.h"

#include "InteractiuneFizica\DetectorColiziuniLiniar.h"
#include "Utilitati.h"
#include "TextRandabil.h"
#include "MaterialText.h"
#include "ActorObiectStatic.h"
#include "CoreMotor/MotorGrafic.h"
#include "Interfete\Harta.h"
#include "Importatoare\ObiectStaticIdentificabil.h"
#include "InteractiuneFizica\ActorStaticInteractiv.h"
#include "reactphysics3d\reactphysics3d.h"


void CameraClasificator::procesareInput(float timpRandareCadru)
{
    efectueazaClasificare();
    afiseazaClasificare();
}

CameraClasificator::CameraClasificator()
{
    coliziuneLinie = NULL;
    actorTextAfisat = NULL;
}

void CameraClasificator::efectueazaClasificare()
{
    if (coliziuneLinie)
        delete coliziuneLinie;
    reactphysics3d::Vector3 vectorStart = Utilitati::convertesteVectorGlmLaReact3D(obtineLocatieCamera());
    reactphysics3d::Vector3 vectorFinal = Utilitati::convertesteVectorGlmLaReact3D(obtineLocatieCamera() + obtineVectorInainte() * 20000.f);
    coliziuneLinie = new DetectorColiziuniLinie(vectorStart, vectorFinal);
}

void CameraClasificator::afiseazaClasificare()
{
    auto corpRigid = dynamic_cast<reactphysics3d::RigidBody*>(coliziuneLinie->obtineObiectLovit());
    Harta* referintaHarta = MotorGrafic::obtineMotorGrafic()->obtineHarta();
    if (coliziuneLinie && corpRigid) {
        ActorStaticInteractiv* actorLovit = dynamic_cast<ActorStaticInteractiv*>(referintaHarta->obtineActorInteractivDinCorp(corpRigid));
        if (actorLovit) {
            ObiectStaticIdentificabil* componentaIdentificabilaLovita = dynamic_cast<ObiectStaticIdentificabil*>(actorLovit->obtineObiectStaticBaza());
            if (componentaIdentificabilaLovita) {
                std::string clasificare = componentaIdentificabilaLovita->obtineEticheta();
                if (!actorTextAfisat) {
                    actorTextAfisat = new ActorStatic(new TextRandabil(clasificare , -1.f, -0.8f, 0.15f), new MaterialText());
                    referintaHarta->adaugaActor(actorTextAfisat);
                }
                else ((TextRandabil*)(actorTextAfisat->obtineObiectStaticBaza()))->schimbaText(clasificare);
                return;
            }
        }
    }
    if (actorTextAfisat)
        ((TextRandabil*)(actorTextAfisat->obtineObiectStaticBaza()))->schimbaText("");
}
