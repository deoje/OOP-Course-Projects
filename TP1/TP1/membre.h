/*
 * Date : 1 Septembre 2019
 * Auteur : Wassim Khene
 */

#ifndef MEMBRE_H
#define MEMBRE_H

#include <string>
#include "billet.h";
#include "coupon.h";

using namespace std;

class Membre {
public:
	// Constructors
	Membre();
	Membre(const string& nom);

	// Destructors
	~Membre();

	// Getters
	string getNom() const;
	int getPoints() const;
	Billet** getBillets() const;
	int getNbBillets() const;
	int getCapaciteBillets() const;
	Coupon** getCoupons() const;
	int getNbCoupons() const;
	int getCapaciteCoupons() const;

	// Setters
	void setNom(const string& nom);
	void modifierPoints(int points);
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol);
	void ajouterCoupon(Coupon* coupon);
	void retirerCoupon(Coupon* coupon);

	// Methods for buying coupons and calculating points per billet
	void acheterCoupon(Coupon* coupon);
	double calculerPoints(Billet* billet) const; // const?

	// Printing methods
	void afficherMembre() const;

private:
	/**
	* @brief nom_ Name of the membre
	*/
	string nom_;
	/**
	* @brief points_ Number of points a member has
	*/
	int points_;
	/**
	* @brief billets_ Array pointing to the billets the member has
	*/
	Billet** billets_;
	/**
	* @brief nbBillets_ Number of tickets a member has
	*/
	int nbBillets_;
	/**
	* @brief capaciteBillets_ Total length of the billets_ array
	*/
	int capaciteBillets_;
	/**
	* @brief coupons_ Array pointing to the coupons the member has
	*/
	Coupon** coupons_;
	/**
	* @brief nbCoupons_ Number of coupons the member has
	*/
	int nbCoupons_;
	/**
	* @brief capaciteCoupons_ Total length of the coupons_ array
	*/
	int capaciteCoupons_;
};


#endif