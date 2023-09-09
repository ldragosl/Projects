#pragma once
#include "Interfete\CameraJucator.h"
#include <string>

class DetectorColiziuniLinie;
class ActorStatic;

class CameraClasificator : public CameraJucator
{
public:
	virtual void procesareInput(float timpRandareCadru) override;
protected:
	CameraClasificator();
	void efectueazaClasificare();
	void afiseazaClasificare();
private:
	DetectorColiziuniLinie* coliziuneLinie;
	ActorStatic* actorTextAfisat;
};

