//Copyright Tudor Dragos Bogdan 2022-2023. All rights reserved.
#pragma once
#include "Utilitati.h"

//Stergem linia asta daca nu dorim log
#define Debugare

//Stergem linia aceasta daca nu dorim desenarea coliziunilor (efect asupra performantei semnificativ)
//#define DebugareColiziuni


#define PathMotor (char*)Utilitati::locatieEngine().c_str()
#define ShaderPredefinit(path) (char*)(Utilitati::locatieEngine() + "Shadere\\" + path).c_str()
#define FormaPredefinita(path) (char*)(Utilitati::locatieEngine() + "FormePredefinite\\" + path).c_str()