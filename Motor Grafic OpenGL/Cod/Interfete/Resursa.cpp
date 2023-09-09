#include "Resursa.h"
#include "Resursa.h"
#include <cassert>  

Resursa::Resursa()
{
	resursaIncarcata = resursaInitializata = false;
}

std::string Resursa::obtineIdResursa()
{
	return idResursa;
}

void Resursa::adaugaCallabackResursaUtilizabila(std::function<void()> functie)
{
	//assert(!resursaInitializata.load(), "S-a incercat adaugarea unui callback dupa ce obiectul a fost initializat.");
	if (resursaInitializata.load())
		functie();
	else callbackResursaIncarcata.push_back(functie);
}