#pragma once

#include <string>
#include <atomic>
#include <vector>
#include <functional>

class Resursa {
public:
	Resursa();

	std::string obtineIdResursa();
	inline bool esteUtilizabila() { return resursaIncarcata.load() && resursaInitializata.load(); }

	void adaugaCallabackResursaUtilizabila(std::function<void ()> functie);
protected:
	virtual void incarcaResursa() = 0;
	virtual void initializeazaResursa() = 0;


	std::string idResursa;
	std::atomic<bool> resursaIncarcata;
	std::atomic<bool> resursaInitializata;

	std::vector<std::function<void()>> callbackResursaIncarcata;

	friend class ManagerResurse;
};