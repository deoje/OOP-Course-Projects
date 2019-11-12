/********************************************
* Titre: Travail pratique #5 - foncteur.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/
#pragma once

#include <string>
#include <vector>
#include <map>

#include "coupon.h"
#include "membrePremium.h"

class AjouterCoupon
{
public:
	AjouterCoupon(vector<Coupon*>& conteneur): conteneur_(conteneur) {};
	vector<Coupon*> operator()(Coupon* coupon) {
		//TODO
		return nullptr;
	};

private:
	vector<Coupon*>& conteneur_;
};


class AjouterMembre
{
public:
	AjouterMembre(map<string, Membre*>& conteneur) : conteneur_(conteneur) {};
	void operator()(pair < string, Membre* membre >) {
		//TODO
		return;
	}

private:
	map<string, Membre*>& conteneur_;
};

class IntervallePrixBillet
{
public:
	IntervallePrixBillet(double borneInf, double borneSup) : borneInf_(borneInf), borneSup_(borneSup) {};
	bool operator()(Billet* billet) {
		//TODO
		return false;
	}

private:
	double borneInf_;
	double borneSup_;
};