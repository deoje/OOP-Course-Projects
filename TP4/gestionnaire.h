/*
* Titre : gestionnaire.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe C�T�-MORNEAULT
*/

#ifndef GESTIONNAIRE_H
#define	GESTIONNAIRE_H

#include <vector>

#include "membrePremium.h"
#include "solde.h"
#include "debogageMemoire.hpp"

class Gestionnaire {
public:
	// Constructeur
	Gestionnaire();

	~Gestionnaire();

	// Getters
	vector<Membre*> getMembres() const;
	vector<Coupon*> getCoupons() const;

	void ajouterMembre(Membre* membre);
	void ajouterCoupon(Coupon* coupon);

	Membre* trouverMembre(const string& nomMembre) const;
	void assignerBillet(Billet* billet, const string& nomMembre, bool utiliserCoupon);
	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(const string& nomMembre);
	double calculerRevenu();
	int calculerNombreBilletsEnSolde();

	void afficher(ostream& o);
private:
	vector<Membre*> membres_;
	vector<Coupon*> coupons_;
};
#endif // !GESTIONNAIRE_H



