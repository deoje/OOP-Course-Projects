/*
* Titre : membrePremium.h - Travail Pratique #3
* Date : 20 Septembre 2019
* Auteur : Jeffrey Lavallee
*/


#ifndef MEMBRE_PREMIUM_H
#define MEMBRE_PREMIUM_H


#include "membreRegulier.h"
#include "def.h"

class MembrePremium : public MembreRegulier {
public:
	MembrePremium(const string& nom);

	//setters
	void setJourRestants(unsigned int joursRestants);
	void modifierPointsCumules(unsigned int pointCumulee);

	//getters
	unsigned int getJourRestants() const;
	unsigned int getpointsCumulee() const;

	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol);
	void acheterCoupon(Coupon* coupon);

	//à faire
	friend ostream& operator<<(ostream& os, const MembrePremium& membrePremium);

private:
	unsigned int joursRestants_;
	unsigned int pointsCumules_;

};

#endif