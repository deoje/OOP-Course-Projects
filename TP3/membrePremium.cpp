#include "membrePremium.h"

MembrePremium::MembrePremium(const string& nom) :
	MembreRegulier(nom, Membre_Premium),
	joursRestants_(JOUR_RESTANT_INITIALE),
	pointsCumules_(0)
{
}

void MembrePremium::setJourRestants(unsigned int joursRestants) {
	joursRestants_ = joursRestants;
}

void MembrePremium::modifierPointsCumules(unsigned int pointCumulee) {
	pointsCumules_ += pointCumulee;
}

unsigned int MembrePremium::getJourRestants() const {
	return joursRestants_;
}

unsigned int MembrePremium::getpointsCumulee() const {
	return pointsCumules_;
}

void MembrePremium::ajouterBillet(const string& pnr, double prix,
	const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol) {
	MembreRegulier::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
}

void MembrePremium::acheterCoupon(Coupon* coupon) {
	double rabais = double(pointsCumules_ / 1000) * 0.01;
	if (rabais > (20.0 / 100)) {
		rabais = (20.0 / 100);
	}
	int cout = coupon->getCout() * (1 - rabais);
	if (points_ > cout) {
		*this += coupon;
		modifierPoints(-cout);
	}
}

ostream& operator<<(ostream& os, const MembrePremium& membrePremium) {
	os << membrePremium << endl;
	os << "\t" << left << "- Points cumules : " << membrePremium.pointsCumules_ << endl;
	os << "\t" << left << "- Jours premium restants : " << membrePremium.pointsCumules_ << endl;
	return os << endl << membrePremium;
}