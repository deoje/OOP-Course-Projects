/*
 * Date : 1 Septembre 2019
 * Auteur : Wassim Khene
 */
#ifndef GESTIONNAIRE_H
#define	GESTIONNAIRE_H

#include "membre.h";

class Gestionnaire {

public:
	// Constructor
	Gestionnaire();

	// Destructor
	~Gestionnaire();

	// Getters
	Membre** getMembres() const;
	int getNbMembres() const;
	int getCapaciteMembres() const;
	Coupon** getCoupons() const;
	int getNbCoupons() const;
	int getCapaciteCoupons() const;

	// Methods for adding members and coupons
	void ajouterMembre(const string& nomMembre);
	void ajouterCoupon(const string& code, double rabais, int cout);

	// Methods for allowing members to buy and use coupons or tickets
	Membre* trouverMembre(const string& nomMembre) const;
	void assignerBillet(const string& nomMembre, const string& pnr,
		double prixBase, const string& od, TarifBillet tarif, const string& dateVol,
		bool utiliserCoupon);
	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(const string& nomMembre);

	// Printing method
	void afficherInfos() const;

private:
	// Attributes
	/**
	 * @brief membres_ Dynamic array of pointers to the set of members.
	 */
	Membre** membres_;
	/**
	 * @brief nbMembres_ Number of members.
	 */
	int nbMembres_;
	/**
	 * @brief capaciteMembres_ Size of the membres_ array.
	 */
	int capaciteMembres_;
	/**
	 * @brief coupons_ Dynamic array of pointers to the set of coupons.
	 */
	Coupon** coupons_;
	/**
	 * @brief nbCoupons_ Number of coupons.
	 */
	int nbCoupons_;
	/**
	 * @brief capaciteCoupons_ Size of the coupons_ array.
	 */
	int capaciteCoupons_;
};

#endif // !GESTIONNAIRE_H