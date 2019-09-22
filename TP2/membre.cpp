/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

Membre::Membre() :
	nom_(""),
	points_(0)
{
}

Membre::Membre(const string& nom) :
	nom_(nom),
	points_(0)
{
}

Membre::Membre(const Membre& m2) : 
	nom_(m2.getNom()),
	points_(m2.getPoints())
{
	// Create a copy of each Billet object found in the
	// billets_ vector of the Membre m
	for (int i = 0; i < m2.getNbBillets(); ++i) {

		// Create a temp var for the original billet
		Billet* originalBillet = m2.billets_[i];

		// Create a new Billet object identical to the original one
		Billet* copyBillet = new Billet(
			originalBillet->getPnr(),
			m2.getNom(),
			originalBillet->getPrix(),
			originalBillet->getOd(),
			originalBillet->getTarif(),
			originalBillet->getDateVol());

		// Add the copy to the new vector
		billets_.push_back(copyBillet);
	}

	// Create a shallow copy of objects in the coupons_ vector
	// but deep copy of pointers
	coupons_ = m2.coupons_;
}

Membre::~Membre()
{
	// iterate through billets_ vector
	for (int i = 0 ; i < billets_.size(); ++i)
		// deallocate the memory for the Billet object at pos i
		delete billets_[i];
}


string Membre::getNom() const
{
	return nom_;
}

int Membre::getPoints() const
{
	return points_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

vector<Coupon*> Membre::getCoupons() const
{
	return coupons_;
}

int Membre::getNbBillets() const
{
	// return the size of the billets_ vector
	return billets_.size();
}

int Membre::getNbCoupons() const
{
	// return the size of the coupons_ vector
	return coupons_.size();
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
	// Create the new Billet object and store its pointer in billet
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, dateVol);
	// append the billet pointer to the billets_ vector
	billets_.push_back(billet);
	// add the points earned by buying this ticket
	modifierPoints(calculerPoints(billet));
}

void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_ > coupon->getCout()) {
		// add the bought coupon to the current member
		*this+=coupon;
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
Membre& Membre::operator+=(Coupon* c)
{
	//append the coupon to the coupons_ vector
	coupons_.push_back(c);
	return *this;
}

// TODO: Remplacer cette methode par l'operateur -=
Membre& Membre::operator-=(Coupon* c)
{	
	// iterate through the coupons_ vector
	for (int i = 0; i < coupons_.size(); ++i) {
		// find the first instance of the corresponding coupon c
		if (coupons_[i] == c) {
			// move every coupon (starting from the positon of the coupon to remove)
			// one place below
			for (int j = i; j < coupons_.size()-1; ++j) {
				coupons_[j] = coupons_[j + 1];
			}
			// remove the last coupons which is now a unusefull copy
			coupons_.pop_back();
			// return the modified instance of the Membre calss
			return *this;
		}
	}
}

bool Membre::operator==(const string& s) const
{
	// verify if the string representing the name of current member matches `s`
	if (nom_ == s)
		return true;
	return false;
}

bool operator==(const string& s, const Membre& m)
{
	// verify if the string representing the name of m matches `s`
	if (s == m.nom_)
		return true;

	return false;
}

Membre& Membre::operator=(const Membre& m2)
{	
	// Verify if we're working with the same Member object
	if (this != &m2) {

		// Iterate the billets_ from the right to left
		for (int i = billets_.size()-1; i > -1; --i) {

			// deallocate the memory for the Billets at pos i
			delete billets_[i];

			// decrease the size of the vector
			billets_.pop_back();
			
		}
		
		// Assign the new name
		nom_ = m2.nom_;
		points_ = m2.points_;

		// Create a copy of each Billet object found in the
		// billets_ vector of the Membre m
		for (int i = 0; i < m2.getNbBillets(); ++i) {

			// Create a temp var for the original billet
			Billet* originalBillet = m2.billets_[i];

			// Create a new Billet object identical to the original one
			Billet* copyBillet = new Billet(
				originalBillet->getPnr(),
				m2.getNom(),
				originalBillet->getPrix(),
				originalBillet->getOd(),
				originalBillet->getTarif(),
				originalBillet->getDateVol());

			// Add the copy to the new vector
			billets_.push_back(copyBillet);
		}

		// Create a shallow copy of objects in the coupons_ vector
		// but deep copy of pointers
		coupons_ = m2.coupons_;
	}
	
	return *this;

}

ostream& operator<<(ostream& o, const Membre& m)
{
	o << setfill(' ');
	o << "- Membre " << m.nom_ << ":" << endl;
	o << "\t" << left << setw(10) << "- Points" << ": " << m.points_ << endl;
	o << "\t" << "- Billets :" << endl;
	for (int i = 0; i < m.billets_.size(); i++) {
		o << *(m.billets_[i]) << endl;
	}
	o << "\t" << "- Coupons :" << endl;
	for (int i = 0; i < m.coupons_.size(); i++) {
		o << *(m.coupons_[i]) << endl;
	}
	o << endl;
	// output a custom print of m's state
	return o;
}

