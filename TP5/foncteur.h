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
	// Constructor
	AjouterCoupon(vector<Coupon*>& conteneur): conteneur_(conteneur) {};

	/**
	 *	@brief operator() to add a coupon into conteneur_
	 *	@param coupon Pointer to the coupon to add
	 *	@return vector<Coupon*> returns the vector after inserting the coupon in the vector
	 */
	vector<Coupon*> operator()(Coupon* coupon) {

		// Verify if the coupon is already in the vector
		if ( find(conteneur_.begin(), conteneur_.end(), coupon) != conteneur_.end() ) {
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
	// Constructor
	AjouterMembre(map<string, Membre*>& conteneur) : conteneur_(conteneur) {};

	/**
	 *	@brief operator() to add a member into conteneur_
	 *	@param member Pair of string and pointer of the member to add
	 */
	void operator()(pair<string, Membre*> membre) {
		conteneur_.insert(membre);
	}

private:
	/**
	 *	@brief conteneur_ map container which contains pairs of ("<name of the member>", pointer to member)
	 */
	map<string, Membre*>& conteneur_;
};

class IntervallePrixBillet
{
public:
	// Constructor
	IntervallePrixBillet(pair<double, double> extrema) : borneInf_(extrema.first), borneSup_(extrema.second) {};
	/**
	 *	@brief operator() to verify if the price of the billet is in the range [borneInf_, borneSup_]
	 *	@param billet Pointer to the billet
	 *	@return bool returns True if the price is in the specified range
	 */
	bool operator()(Billet* billet) const {
		return billet->getPrix() <= borneSup_ && billet->getPrix() >= borneInf_;
	}

private:
	/*
	*	@brief borneInf_ The min value of the interval 
	*/
	double borneInf_;
	/*
	*	@brief borneInf_ The max value of the interval
	*/
	double borneSup_;
};