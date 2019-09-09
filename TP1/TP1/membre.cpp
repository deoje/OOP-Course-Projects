#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#include "pch.h"
#include "membre.h"


Membre::Membre()
{
	nom_ = "no_name";
	points_ = 0;
	//billet**
	nbBillets_ = 0;
	capaciteBillets_ = 0;
	//coupons**
	nbCoupons_ = 0;
	capaciteCoupons_ = 0;

}

Membre::Membre(const string& nom)
// : call constructor of billet and coupon
{
	nom_ = nom;
	points_ = 0;
	//billet**
	nbBillets_ = 0;
	capaciteBillets_ = 0;
	//coupons**
	nbCoupons_ = 0;
	capaciteCoupons_ = 0;
}

Membre::~Membre()
{
	// Do some delete for dynamic tables?
}

string Membre::getNom() const
{
	return nom_;
}

int Membre::getPoints() const
{
	return points_;
}

// Implement getBillet() here

int Membre::getNbBillets() const
{
	return nbBillets_;
}

int Membre::getCapaciteBillets() const
{
	return capaciteBillets_;
}

// Implement getCoupons() here

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