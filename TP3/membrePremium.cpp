#include "membrePremium.h"

MembrePremium::MembrePremium(const string& nom) :
	MembreRegulier(nom, typeMembre),
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
	return joursRectants_;
}

unsigned int MembrePremium::getpointsCumulee() const {
	return pointsCumules_;
}

void MembrePremium::acheterCoupon(Coupon* coupon) {
	double rabais = (pointsCumules / 1000) * 0.01;
	if (rabais > 20.0) {
		rabais = 20.0;
	}
	MembreRegulier::acheterCoupon(coupon);
}

friend ostream& operator<<(ostream& os, const MembrePremium& membrePremium) {
	os << membrePremium << endl;
	os << "\t" << left << "- Points cumules : " << membrePremium.pointsCumules_ << endl;
	os << "\t" << left << "- Jours premium restants : " << membrePremium.pointsCumules_ << endl;
	return o << endl << this;
}