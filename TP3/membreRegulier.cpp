#include "membreRegulier.h"

MembreRegulier::MembreRegulier(const string& nom, TypeMembre typeMembre) :
	Membre(nom, typeMembre),
	points_(0)
{
}

int MembreRegulier::getPoints() const
{
	return points_;
}

/**
*	@brief ajouterBillet To create a specific type of ticket and then add it to a member
*	@param pnr String representing the ticket's ID
*	@param prix Double representing the ticket's price
*	@param od Constant reference to a string representing the ticket's origin and destination
*	@param tarif TarifBillet enum to set the ticket's class (economie, affaire ...)
*	@param typeBillet TypeBillet enum to set the ticket's type
*	@param dateVol String representing the ticket's date of flight
*/
void MembreRegulier::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol){
	// Use the method defined in the base class
	Membre::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	// Change the points of the member with the results of the method calculerPoints on the last ticket added to billets_
	modifierPoints(calculerPoints(billets_[billets_.size() - 1]));
}

vector<Coupon*> MembreRegulier::getCoupons() const
{
	return coupons_;
}

void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	if (points_ >= coupon->getCout()) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}


Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	for (int i = 0; i < coupons_.size(); i++) {
		if (coupons_[i] == coupon) {
			coupons_[i] = coupons_[coupons_.size() - 1];
			coupons_.pop_back();
			return *this;
		}
	}

	return *this;
}

void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}

/**
*	@brief Operator overload (<<) to print the state of the current member
*/
ostream& operator<<(ostream& os, const MembreRegulier& membreRegulier) {
	os << setfill(' ');
	os << "- Membre " << membreRegulier.nom_ << ":" << endl;
	os << "\t" << "- Billets :" << endl;
	for (int i = 0; i < membreRegulier.billets_.size(); i++) {
		os << *membreRegulier.billets_[i];
	}
	os << "\t" << left << setw(10) << "- Points" << ": " << membreRegulier.points_ << endl;
	os << "\t" << "- Coupons :" << endl;
	for (int i = 0; i < membreRegulier.coupons_.size(); i++) {
		os << *membreRegulier.coupons_[i];
	}

	return os << endl;
}

double MembreRegulier::calculerPoints(Billet* billet) const
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

	return billet->getPrix() * 0.10 + bonus;
}

