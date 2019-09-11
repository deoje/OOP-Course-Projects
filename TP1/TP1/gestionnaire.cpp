#include "pch.h"
#include "gestionnaire.h"


Gestionnaire::Gestionnaire()
{
	membres_ = new Membre*[];
	nbMembres_ = 0;
	capaciteMembres_ = CAPACITE_INITIALE;
	coupons_ = new Coupon*[];
	nbCoupons_ = 0;
	capaciteCoupons_ = CAPACITE_INITIALE;
}

Membre** Gestionnaire::getMembres()
{
	return membres_;
}

int Gestionnaire::getNbMembres()
{
	return nbMembres_;
}

int Gestionnaire::getCapaciteMembres()
{
	return capaciteCoupons_;
}

Coupon** Gestionnaire::getCoupons()
{
	return coupons_;
}

int Gestionnaire::getNbCoupons()
{
	return nbCoupons_;
}

int Gestionnaire::getCapaciteCoupons()
{
	return capaciteCoupons_;
}

void Gestionnaire::ajouterMembre(const string& nomMembre)
{
	// Increase the size of the container if need be.
	if (nbMembres_ >= capaciteMembres_) {
		Membre** expandedArray = new Membre*[capaciteMembres_*2];
		for (unsigned int i = 0; i < capaciteMembres_; i++) {
			expandedArray[i] = membres_[i];
		}
		delete[] membres_;
		membres_ = expandedArray;
		capaciteMembres_ *= 2;
	}
	membres_[nbMembres_] = new Membre();
	nbMembres_++;
}

void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	if (nbCoupons_ >= capaciteCoupons_) {
		Coupon** expandedArray = new Coupon*[capaciteCoupons_ * 2];
		for (unsigned int i = 0; i < capaciteCoupons_; i++) {
			expandedArray[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = expandedArray;
		capaciteCoupons_ *= 2;
	}
	coupons_[nbCoupons_] = new Coupon(code, rabais, cout);
	nbCoupons_++;
}

Membre* Gestionnaire::trouverMembre(const string& nomMembre)
{
	for (int i = 0; i < nbMembres_; i++) {
		if (membres_[i]->getNom() == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Member '" << nomMembre << "' was not found." << endl;
	return nullptr;
}

void Gestionnaire::assignerBillet(const string& nomMembre,
	const string& pnr, double prixBase, const string& od,
	TarifBillet tarif, const string& dateVol,
	bool utiliserCoupon)
{
	double prix = prixBase;
	if (utiliserCoupon) {
		// TODO
	}
	trouverMembre(nomMembre)->ajouterBillet(pnr, prix, od,
		tarif, dateVol);
}

double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	Coupon** coupons = membre->getCoupons();
	int nCoupons = membre->getNbCoupons();
	if (nCoupons == 0) {
		cout << "Member " << membre->getNom() << " has "
			<< "no coupon." << endl;
		return;
	}
	Coupon* bestCoupon = coupons[0];
	for (int i = 1; i < nCoupons; i++) {
		double rabais = coupons[i]->getRabais();
		if (rabais > bestCoupon->getRabais()) {
			bestCoupon = coupons[i];
		}
	}
	double discoutOnPrice = bestCoupon->getRabais() * prix;
	membre->retirerCoupon(bestCoupon);
	return discoutOnPrice;
}

void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	Coupon* bestCoupon = coupons_[0];
	for (int i = 1; i < nbCoupons_; i++) {
		double rabais = coupons_[i]->getRabais();
		if (rabais > bestCoupon->getRabais()) {
			bestCoupon = coupons_[i];
		}
	}
	Membre* membre = trouverMembre(nomMembre);
	if (membre->getPoints >= bestCoupon->getCout) {
		trouverMembre(nomMembre)->acheterCoupon(bestCoupon);
	}
	else {
		cout << "Member '" << nomMembre << "' cannot "
			<< "buy a coupon." << endl;
	}
	// TODO: pop the coupon
}

void Gestionnaire::afficherInfos()
{
	for (int i = 0; i < nbMembres_; i++) {
		membres_[i]->afficherMembre();
	}
}

Gestionnaire::~Gestionnaire()
{
}
