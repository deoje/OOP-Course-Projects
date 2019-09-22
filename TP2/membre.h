/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#ifndef MEMBRE_H
#define MEMBRE_H

#include <string>
#include <vector>

#include "billet.h"
#include "coupon.h"

using namespace std;

class Membre {
public:
	// Constructeurs
	Membre();
	Membre(const string& nom);
	/**
	 * @brief Membre Copy constructor
	 * @param m2 The member to copy
	 */
	Membre(const Membre& m2);

	/**
	 * @brief ~Membre Membre destructor
	 */
	~Membre();

	// Getters
	string getNom() const;
	int getPoints() const;
	vector<Billet*> getBillets() const;
	vector<Coupon*> getCoupons() const;
	int getNbBillets() const;
	int getNbCoupons() const;

	// Setters
	void setNom(const string& nom);
	void modifierPoints(int points);
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol);
	void acheterCoupon(Coupon* coupon);
	double calculerPoints(Billet* billet) const;

	/**
	 * @brief operator+= To add a coupon to the current Member
	 * @param c The coupon to add
	 */
	Membre& operator+=(Coupon* c);
	/**
	 * @brief operator+-= To remove a coupon from coupons_
	 * @param c The coupon to remove
	 */
	Membre& operator-=(Coupon* c);

	/**
	 * @brief operator== To compare a Member's name with a string
	 * @param s The string to compare nom_ with
	 */
	bool operator==(const string& s) const;
	/**
	 * @brief operator== To compare a string with a Member's name
	 * @param m The member to compare s with
	 */
	friend bool operator==(const string& s, const Membre& m);
	/**
	 * @brief operator= To assign the current member to the member m2
	 * @param m2 The member to copy
	 */
	Membre& operator=(const Membre& m2);


	/**
	 * @brief operator<< To output the state of the current member
	 * @param ostream The ostream object
	 * @param m The Membre object which has the state of interest
	 */
	friend ostream& operator<<(ostream& o, const Membre& m);

private:
	string nom_;
	int points_;
	/**
	 * @brief billets_ To store pointers to Billet objects
	 */
	vector<Billet*> billets_;
	/**
	 * @brief billets_ To store pointers to Coupons objects
	 */
	vector<Coupon*> coupons_;
};
#endif // !MEMBRE_H
