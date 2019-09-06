/*
 * Date : 1 Septembre 2019
 * Auteur : Wassim Khene
 */
#ifndef GESTIONNAIRE_H
#define	GESTIONNAIRE_H

#include "membre.h";

class Gestionnaire {

public:
	// TODO: Implementer toutes les methodes
	Gestionnaire();

	// TODO: Implementer si necessaire
	~Gestionnaire();

	// Getters
	Membre** getMembres();
	int getNbMembres();
	int getCapaciteMembres();
	Coupon** getCoupons();
	int getNbCoupons();
	int getCapaciteCoupons();

	void ajouterMembre(const string& nomMembre);
	void ajouterCoupon(const string& code, double rabais, int cout);

	Membre* trouverMembre(const string& nomMembre);
	void assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon);
	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(const string& nomMembre);

	void afficherInfos();
private:
	Membre** membres_;
	int nbMembres_;
	int capaciteMembres_;
	Coupon** coupons_;
	int nbCoupons_;
	int capaciteCoupons_;
};

#endif // !GESTIONNAIRE_H