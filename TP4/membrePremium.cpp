/*
* Titre : membrePremium.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "membrePremium.h"

MembrePremium::MembrePremium(const string& nom) : 
	MembreRegulier(nom), joursRestants_(JOUR_RESTANT_INITIALE), pointsCumulee_(0)
{
}

void MembrePremium::setJourRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;
}

void MembrePremium::modifierPointsCumulee(unsigned int pointCumulee)
{
	pointsCumulee_ += pointCumulee;
}

unsigned int MembrePremium::getJourRestants() const
{
	return joursRestants_;
}

unsigned int MembrePremium::getpointsCumulee() const
{
	return pointsCumulee_;
}

void MembrePremium::ajouterBillet(Billet* billet)
{
	MembreRegulier::ajouterBillet(billet);
	modifierPointsCumulee(calculerPoints(billets_.back()));
}

double MembrePremium::calculerCoutCoupon(Coupon* coupon)
{
	double rabais = 0.01 * pointsCumulee_ / 1000;

	if (rabais > 0.2)
		rabais = 0.2;

	return coupon->getCout() * (1 - rabais);
}

/**
*	@brief Verify if a member can buy a coupon (may apply a discount).
*	@param coupon The coupon used to assess whether the member can buy it or not.
*/
bool MembrePremium::peutAcheterCoupon(Coupon* coupon)
{
	return points_ >= calculerCoutCoupon(coupon);
}

void MembrePremium::acheterCoupon(Coupon* coupon)
{
	if (peutAcheterCoupon(coupon)) {
		*this += coupon;
		modifierPoints(-calculerCoutCoupon(coupon));
	}
}

/**
*	@brief Premium member printing method.
*	@param o Output stream used for display.
*/
void MembrePremium::afficher(ostream& o)
{
	MembreRegulier::afficher(o);
	o << "\t- Points cumulee: " << pointsCumulee_ << endl;
	o << "\t- Jours premium restant: " << joursRestants_ << endl;
	o << endl;
}