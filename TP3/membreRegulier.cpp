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

void MembreRegulier::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol){
	Membre::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	modifierPoints(-calculerPoints(billets_[billets_.size() - 1]));
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

ostream& operator<<(ostream& os, const MembreRegulier& membreRegulier) {
	os << membreRegulier;
	os << "\t" << left << setw(10) << "- Points" << ": " << membreRegulier.points_ << endl;
	os << "\t" << "- Coupons :" << endl;
	for (int i = 0; i < membreRegulier.coupons_.size(); i++) {
		os << *membreRegulier.coupons_[i];
	}
	return os << membreRegulier;
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

