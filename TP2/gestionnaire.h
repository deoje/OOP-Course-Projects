/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#ifndef GESTIONNAIRE_H
#define	GESTIONNAIRE_H

#include <vector>

#include "membre.h"

class Gestionnaire {
public:
	// Constructeurs
	Gestionnaire();

	~Gestionnaire();

	// Getters
	vector<Membre*> getMembres() const;
	int getNbMembres() const;
	int getCapaciteMembres() const;
	vector<Coupon*> getCoupons() const;
	int getNbCoupons() const;
	int getCapaciteCoupons() const;

	void ajouterMembre(const string& nomMembre);
	void ajouterCoupon(const string& code, double rabais, int cout);

	Membre* trouverMembre(const string& nomMembre) const;
	void assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon);
	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(const string& nomMembre);

	friend ostream& operator<< (ostream& os, const Gestionnaire& gestionnaire);

private:
	vector<Membre*> membres_;
	vector<Coupon*> coupons_;
};
#endif // !GESTIONNAIRE_H



