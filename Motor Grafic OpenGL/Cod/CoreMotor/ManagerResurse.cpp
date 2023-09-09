#include "ManagerResurse.h"

#include <thread>

#include "Interfete\Textura.h"
#include "ObiectStatic.h"

#include <iostream>

ManagerResurse* ManagerResurse::referintaSingleton = NULL;

ManagerResurse* ManagerResurse::obtineManagerResurse()
{
    if (referintaSingleton == NULL)
        referintaSingleton = new ManagerResurse();
    return referintaSingleton;
}

void ManagerResurse::_incarcaResursaAsincron(Resursa* resursa) {
    resursa->incarcaResursa();
    resursa->resursaIncarcata.store(true);
}

Textura* ManagerResurse::adaugaTextura(Textura* texturaNoua)
{
    auto texturaGasita = texturi.find(texturaNoua->obtineIdResursa());
    if (texturaGasita != texturi.end()) {
        delete texturaNoua;
        return texturaGasita->second;
    }
    else {
        resurseInAsteptare.push_back(texturaNoua);
        texturi[texturaNoua->obtineIdResursa()] = texturaNoua;
        std::thread threadIncarcareResursa(&ManagerResurse::_incarcaResursaAsincron, this, texturaNoua);
        //texturaNoua->incarcaResursa();
        threadIncarcareResursa.detach();
        return texturaNoua;
    }
}

Textura* ManagerResurse::obtineTextura(std::string idTextura)
{
    auto texturaGasita = texturi.find(idTextura);
    if (texturaGasita != texturi.end())
        return texturaGasita->second;
    return NULL;
}

ObiectStatic* ManagerResurse::obtineObiectStatic(std::string idObiect)
{
    auto obiectGasit = obiecteStatice.find(idObiect);
    if (obiectGasit != obiecteStatice.end())
        return  obiectGasit->second;
    return NULL;
}

ObiectStatic* ManagerResurse::adaugaObiectStatic(ObiectStatic* obiectNou)
{
    auto obiectGasit = obiecteStatice.find(obiectNou->obtineIdResursa());
    if (obiectGasit != obiecteStatice.end()) {
        for (auto functieCallbackCurenta : obiectNou->callbackResursaIncarcata) {
            functieCallbackCurenta();
        }
        delete obiectNou;
        return obiectGasit->second;
    }
    else {
        resurseInAsteptare.push_back(obiectNou);
        obiecteStatice[obiectNou->obtineIdResursa()] = obiectNou;
        std::thread threadIncarcareResursa(&ManagerResurse::_incarcaResursaAsincron, this, obiectNou);
        //obiectNou->incarcaResursa();
        threadIncarcareResursa.detach();
        //obiectNou->initializeazaResursa();
        //std::thread threadIncarcareResursa(&ManagerResurse::_incarcaTexturaAsync, this, texturaNoua);
        //texturaNoua->incarcaResursa();
        //threadIncarcareResursa.join();
        return obiectNou;
    }
}

void ManagerResurse::actualieazaResurse()
{
    std::vector<Resursa*>::iterator resursaCurenta = resurseInAsteptare.begin();
    while (resursaCurenta != resurseInAsteptare.end())
    {
        if ((*resursaCurenta)->resursaIncarcata.load()){
            (*resursaCurenta)->initializeazaResursa();
            (*resursaCurenta)->resursaInitializata.store(true);
            for (auto functieCallbackCurenta : (*resursaCurenta)->callbackResursaIncarcata) {
                functieCallbackCurenta();
            }
            (*resursaCurenta)->callbackResursaIncarcata.clear();
            resursaCurenta = resurseInAsteptare.erase(resursaCurenta);
        }
        else
        {
            ++resursaCurenta;
        }
    }
}

ManagerResurse::ManagerResurse()
{
}
