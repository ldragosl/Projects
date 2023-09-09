#pragma once
#include <map>
#include <string>
#include <vector>

class Textura;
class Material;
class ObiectStatic;
class Resursa;

//singleton
class ManagerResurse
{
public:
	static ManagerResurse* obtineManagerResurse();

	Textura* adaugaTextura(Textura* texturaNoua);
	Textura* obtineTextura(std::string idTextura);


	ObiectStatic* obtineObiectStatic(std::string idObiect);
	ObiectStatic* adaugaObiectStatic(ObiectStatic* obiectNou);

	void actualieazaResurse();

private:
	ManagerResurse();

	static ManagerResurse* referintaSingleton;

	std::map<std::string, Textura*> texturi;
	std::map<std::string, ObiectStatic*> obiecteStatice;

	std::vector<Resursa*> resurseInAsteptare;

	//functia e apelata asincron
	//folosim acest wrapper deoarece vrem sa apelam functia corecta, aceasta functie fiind virtuala!
	void _incarcaResursaAsincron(Resursa* resursa);
};

