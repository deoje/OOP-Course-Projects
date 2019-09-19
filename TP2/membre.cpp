/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

Membre::Membre() :
	nom_(""),
	points_(0),
	billets_(new Billet* [CAPACITE_INITIALE]),
	nbBillets_(0),
	capaciteBillets_(CAPACITE_INITIALE),
	coupons_(new Coupon* [CAPACITE_INITIALE]),
	nbCoupons_(0),
	capaciteCoupons_(CAPACITE_INITIALE)
{
}

Membre::Membre(const string& nom) :
	nom_(nom),
	points_(0),
	billets_(new Billet* [CAPACITE_INITIALE]),
	nbBillets_(0),
	capaciteBillets_(CAPACITE_INITIALE),
	coupons_(new Coupon* [CAPACITE_INITIALE]),
	nbCoupons_(0),
	capaciteCoupons_(CAPACITE_INITIALE)
{
}

Membre::~Membre()
{
	for (int i = 0; i < nbBillets_; i++) {
		delete billets_[i];
	}
	delete[] billets_;

	delete[] coupons_;
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

Coupon** Membre::getCoupons() const
{
	return coupons_;
}

int Membre::getNbBillets() const
{
	return nbBillets_;
}

int Membre::getNbCoupons() const
{
	return nbCoupons_;
}

int Membre::getCapaciteBillets() const
{
	return capaciteBillets_;
}

int Membre::getCapaciteCoupons() const
{
	return capaciteCoupons_;
}

void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

void Membre::modifierPoints(int points)
{
	points_ += points;
}

void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, dateVol);
	if (nbBillets_ >= capaciteBillets_) {
		capaciteBillets_ *= 2;

		Billet** temp = new Billet * [capaciteBillets_];

		for (int i = 0; i < nbBillets_; i++) {
			temp[i] = billets_[i];
		}
		delete[] billets_;

		billets_ = temp;
	}
	billets_[nbBillets_++] = billet;
	modifierPoints(calculerPoints(billet));
}

void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_ > coupon->getCout()) {
		// TODO: Utiliser la surcharge de l'operateur += de la classe Membre plutot qu'utiliser la methode ajouterCoupon
		ajouterCoupon(coupon);
		modifierPoints(-coupon->getCout());
	}
}

double  Membre::calculerPoints(Billet * billet) const
{
	double bonus = 0;
	switch (billet->getTarif()) {
	case TarifBillet::PremiumEconomie:
		bonus = 50;
		break;
	case TarifBillet::Affaire:
		bonus = 150;
		break;
	case TarifBillet::Premiere:
		bonus = 300;
		break;
	default:
		break;
	}

	return billet->getPrix()* 0.10 + bonus;
}

// TODO: Remplacer cette methode par l'operateur +=
void Membre::ajouterCoupon(Coupon* coupon)
{
	if (nbCoupons_ >= capaciteCoupons_) {
		capaciteCoupons_ *= 2;

		Coupon** temp = new Coupon *[capaciteCoupons_];

		for (int i = 0; i < nbCoupons_; i++) {
			temp[i] = coupons_[i];
		}
		delete[] coupons_;

		coupons_ = temp;
	}
	coupons_[nbCoupons_++] = coupon;
}

// TODO: Remplacer cette methode par l'operateur -=
void Membre::retirerCoupon(Coupon* coupon)
{
	for (int i = 0; i < nbCoupons_; i++) {
		if (coupons_[i] == coupon) {
			nbCoupons_--;
			for (int j = i; j < nbCoupons_; j++) {
				coupons_[j] = coupons_[j + 1];
			}
			return;
		}
	}
}

// TODO: Remplacer cette methode par la surcharge de l'operateur <<
void Membre::afficherMembre() const
{
	cout << setfill(' ');
	cout << "- Membre " << nom_ << ":" << endl;
	cout << "\t" << left << setw(10) << "- Points" << ": " << points_ << endl;
	cout << "\t" << "- Billets :" << endl;
	for (int i = 0; i < nbBillets_; i++) {
		billets_[i]->afficherBillet();
	}
	cout << "\t" << "- Coupons :" << endl;
	for (int i = 0; i < nbCoupons_; i++) {
		//coupons_[i]->afficherCoupon();
	}
	cout << endl;
}
