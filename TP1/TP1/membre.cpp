#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#include "pch.h"
#include "membre.h"
#include "def.h"


Membre::Membre()
{
	nom_ = "no_name";
	points_ = 0;
	/*
		Billets
	*/
	nbBillets_ = 0;
	capaciteBillets_ = CAPACITE_INITIALE;
	billets_ = new Billet*[CAPACITE_INITIALE];
	/*
		Coupons
	*/
	nbCoupons_ = 0;
	capaciteCoupons_ = CAPACITE_INITIALE;
	coupons_ = new Coupon*[CAPACITE_INITIALE];
}

Membre::Membre(const string& nom)
{
	nom_ = nom;
	points_ = 0;
	/*
		Billets
	*/
	nbBillets_ = 0;
	capaciteBillets_ = CAPACITE_INITIALE;
	billets_ = new Billet * [CAPACITE_INITIALE];
	/*
		Coupons
	*/
	nbCoupons_ = 0;
	capaciteCoupons_ = CAPACITE_INITIALE;
	coupons_ = new Coupon * [CAPACITE_INITIALE];
}

Membre::~Membre()
{
	for (int i = 0; i < nbBillets_; i++)
	{
		delete billets_[i];
	}

	delete[] billets_;
	billets_ = nullptr;

	delete[] coupons_;
	coupons_ = nullptr;
}

string Membre::getNom() const
{
	return nom_;
}

int Membre::getPoints() const
{
	return points_;
}

Billet** Membre::getBillets() const
{
	return billets_;
}

int Membre::getNbBillets() const
{
	return nbBillets_;
}

int Membre::getCapaciteBillets() const
{
	return capaciteBillets_;
}

Coupon** Membre::getCoupons() const {
	return coupons_;
}

int Membre::getNbCoupons() const
{
	return nbCoupons_;
}

int Membre::getCapaciteCoupons() const
{
	return capaciteCoupons_;
}

void Membre::setNom(const string& nom) {
	nom_ = nom;
}

void Membre::modifierPoints(int points) {
	points_ += points;
}

void Membre::ajouterBillet(const string& pnr, double prix,
	const string& od, TarifBillet tarif, const string& dateVol)
{
	// Creating Billet
	Billet* newBillet = new Billet(pnr, getNom(), prix, od, tarif, dateVol);

	if (nbBillets_ == capaciteBillets_)
	{
		int newCapacity = capaciteBillets_ * 2;
		Billet** newArray = new Billet * [newCapacity];
		for (size_t i = 0; i < nbBillets_; i++)
		{
			newArray[i] = billets_[i];
		}

		delete[] billets_;
		billets_ = newArray;
		capaciteBillets_ = newCapacity;
	}
	double newPoints = calculerPoints(newBillet);
	modifierPoints(newPoints);
	billets_[nbBillets_++] = newBillet;
}

void Membre::ajouterCoupon(Coupon* coupon)
{
	if (nbCoupons_ == capaciteCoupons_)
	{
		int newCapacity = capaciteCoupons_ *2;

		Coupon** newArray = new Coupon * [newCapacity];

		for (int i = 0; i < nbCoupons_; i++) {
			newArray[i] = coupons_[i];
		}

		delete[] coupons_;
		coupons_ = newArray;
		capaciteCoupons_ = newCapacity;
	}
	// Add the coupon to the array
	coupons_[nbCoupons_] = coupon;
	nbCoupons_++;
}

void Membre::retirerCoupon(Coupon* coupon)
{
	for (int i = 0; i < nbCoupons_; i++) {
		if (coupons_[i]->getCode() == coupon->getCode()) {

			for (int j = i; j < nbCoupons_ - 1;j++) {
				coupons_[j] = coupons_[j + 1];
			}

			nbCoupons_--;
			break;
		}
	}
}

void Membre::acheterCoupon(Coupon* coupon) {
	if (getPoints() >= coupon->getCout())
	{
		// add coupon to table
		ajouterCoupon(coupon);
		// Deduct points used to buy the coupon
		modifierPoints(coupon->getCout() * -1);
	}
}

double Membre::calculerPoints(Billet* billet) const
{
	double basePoints = billet->getPrix() * 0.1;
	double bonusPoints = 0;
	if (billet->getTarif() == TarifBillet::PremiumEconomie)
	{
		bonusPoints = 50;
	}
	else if (billet->getTarif() == TarifBillet::Affaire)
	{
		bonusPoints = 150;
	}
	else if (billet->getTarif() == TarifBillet::Premiere)
	{
		bonusPoints = 300;
	}

	return basePoints + bonusPoints;
}

void Membre::afficherMembre() const {

}