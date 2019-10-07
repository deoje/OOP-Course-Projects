#include "membrePremium.h"

/**
*	@brief Constructors with Parameters
*	@param nom String representing the member's name
*/
MembrePremium::MembrePremium(const string& nom) :
	MembreRegulier(nom, Membre_Premium),
	joursRestants_(JOUR_RESTANT_INITIALE), // The duration in days of the premim membership
	pointsCumules_(0)
{
}

/**
*	@brief setJoursRestants To set the number of days left to the premium membership
*	@param joursRestants Usigned int representing the number of days left
*/
void MembrePremium::setJourRestants(unsigned int joursRestants) {
	joursRestants_ = joursRestants;
}
/**
*	@brief modifierPointsCumules To modify the amount of cumulated points
*	@param pointCumulee Unsigned int of points to add
*/
void MembrePremium::modifierPointsCumules(unsigned int pointCumulee) {
	pointsCumules_ += pointCumulee;
}

/**
*	@brief getJoursRestant To get the number of days left
*	@return Usigned int of days left
*/
unsigned int MembrePremium::getJourRestants() const {
	return joursRestants_;
}

/**
*	@brief modifierPointsCumules To modify the amount of cumulated points
*	@param pointCumulee Unsigned int of points to add
*/
unsigned int MembrePremium::getpointsCumulee() const {
	return pointsCumules_;
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
void MembrePremium::ajouterBillet(const string& pnr, double prix,
	const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol) {
	MembreRegulier::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	modifierPointsCumules(calculerPoints(billets_[billets_.size() - 1]));
}

/**
*	@brief acheterCoupon To buy a coupon for the current member
*	@param coupon Coupon to buy
*/
void MembrePremium::acheterCoupon(Coupon* coupon) {
	double rabais = double(points_) / 1000.0 * 0.01; //?
	if (rabais > (20.0 / 100.0)) {
		rabais = (20.0 / 100.0);
	}
	int cost = coupon->getCout() * (1.0 - rabais);
	if (points_ >= cost) {
		*this += coupon;
		modifierPoints(-cost);
	}
}

/**
*	@brief Operator overload (<<) to print the state of the current member
*/
ostream& operator<<(ostream& os, const MembrePremium& membrePremium) {
	// Implicit upcasting i.e. MembrePremium --> MembreRegulier
	MembreRegulier membreRegulier = membrePremium;

	os << membreRegulier;
	os << "\t" << left << "- Points cumules : " << membrePremium.pointsCumules_ << endl;
	os << "\t" << left << "- Jours premium restants : " << membrePremium.joursRestants_ << endl;
	return os << endl;
}