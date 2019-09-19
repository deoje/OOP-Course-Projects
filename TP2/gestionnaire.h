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
	Membre** getMembres() const;
	int getNbMembres() const;
	int getCapaciteMembres() const;
	Coupon** getCoupons() const;
	int getNbCoupons() const;
	int getCapaciteCoupons() const;

	void ajouterMembre(const string& nomMembre);
	void ajouterCoupon(const string& code, double rabais, int cout);

	Membre* trouverMembre(const string& nomMembre) const;
	void assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon);
	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(const string& nomMembre);

	// TODO: Remplacer cette methode par l'operateur <<
	void afficherInfos() const;
private:
	// TODO: Convertir membres_ en vecteur
	Membre** membres_;
	int nbMembres_;
	int capaciteMembres_;
	// TODO: Convertir coupons_ en vecteur
	Coupon** coupons_;
	int nbCoupons_;
	int capaciteCoupons_;
};
#endif // !GESTIONNAIRE_H



