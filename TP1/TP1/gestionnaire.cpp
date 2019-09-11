#include "pch.h"
#include "gestionnaire.h"

/**
*@brief Gestionnaire default constructor. Initializes empty arrays and
*       attributes.
*/
Gestionnaire::Gestionnaire()
{
	membres_ = new Membre*[0];
	nbMembres_ = 0;
	capaciteMembres_ = CAPACITE_INITIALE;
	coupons_ = new Coupon*[0];
	nbCoupons_ = 0;
	capaciteCoupons_ = CAPACITE_INITIALE;
}

/**
*@brief Get array 'membres_'.
*@return attribute membres_.
*/
Membre** Gestionnaire::getMembres()
{
	return membres_;
}

/**
*@brief Get the number of members.
*@return attribute nbMembres_.
*/
int Gestionnaire::getNbMembres()
{
	return nbMembres_;
}

/**
*@brief Get the total size of array 'membres_'.
*@return attribute capaciteMembres_.
*/
int Gestionnaire::getCapaciteMembres()
{
	return capaciteMembres_;
}

/**
*@brief Get the array of coupons.
*@return attribute coupons_.
*/
Coupon** Gestionnaire::getCoupons()
{
	return coupons_;
}

/**
*@brief Get the number of coupons.
*@return attribute nbCoupons_.
*/
int Gestionnaire::getNbCoupons()
{
	return nbCoupons_;
}

/**
*@brief Get the total size of array 'coupons_'.
*@return attribute capaciteCoupons_.
*/
int Gestionnaire::getCapaciteCoupons()
{
	return capaciteCoupons_;
}

/**
*@brief Create a new object 'Membre' and add it to the array of members.
*@param nomMembre The new member's name.
*/
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

/**
*@brief Create a new object 'Coupon' and add it to the array of coupons.
*@param code The new coupon's code.
*@param rabais Price reduction for this coupon.
*@param cout Cost of the new coupon.
*/
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

/**
*@brief Find and return a member in the list of members.
*@param nomMembre Name of the member to look for.
*@return Pointer to the member of the desired name.
*/
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

/**
*@brief TODO
*/
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

/**
*@brief TODO
*/
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	Coupon** coupons = membre->getCoupons();
	int nCoupons = membre->getNbCoupons();
	if (nCoupons == 0) {
		cout << "Member " << membre->getNom() << " has "
			<< "no coupon." << endl;
		return 0.0;
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

/**
*@brief TODO
*/
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
	if (membre->getPoints() >= bestCoupon->getCout()) {
		trouverMembre(nomMembre)->acheterCoupon(bestCoupon);
	}
	else {
		cout << "Member '" << nomMembre << "' cannot "
			<< "buy a coupon." << endl;
	}
	// TODO: pop the coupon
}

/**
*@brief Print information for all members.
*/
void Gestionnaire::afficherInfos()
{
	for (int i = 0; i < nbMembres_; i++) {
		membres_[i]->afficherMembre();
	}
}

/**
*@brief Delete attributes 'membres_' and 'coupons_' and their content.
*/
Gestionnaire::~Gestionnaire()
{
	for (int i = 0; i < nbMembres_; i++) {
		delete membres_[i];
	}
	delete[] membres_;
	for (int i = 0; i < nbCoupons_; i++) {
		delete coupons_[i];
	}
	delete[] coupons_;
}
