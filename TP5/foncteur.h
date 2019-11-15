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
		if (find(conteneur_.begin(), conteneur_.end(), coupon) != conteneur_.end()) {
			return conteneur_;
		}
		else {
			conteneur_.push_back(coupon);
			return conteneur_;
		}
	};

private:
	vector<Coupon*>& conteneur_;
};


class AjouterMembre
{
public:
	AjouterMembre(map<string, Membre*>& conteneur) : conteneur_(conteneur) {};
	void operator()(pair<string, Membre*> membre) {
		conteneur_.insert(membre);
	}

private:
	map<string, Membre*>& conteneur_;
};

class IntervallePrixBillet
{
public:
	IntervallePrixBillet(pair<double, double> extrema) : borneInf_(extrema.first), borneSup_(extrema.second) {};
	bool operator()(Billet* billet) const {
		return billet->getPrix() <= borneSup_ && billet->getPrix() >= borneInf_;
	}

private:
	double borneInf_;
	double borneSup_;
};