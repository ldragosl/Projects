#pragma once
#include "Interfete\CameraClasificator.h"
class CameraSpectator : public CameraClasificator
{
public:
	virtual void procesareInput(float timpRandareCadru) override;
};

