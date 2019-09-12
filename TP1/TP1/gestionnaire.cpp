#include "pch.h"
#include "gestionnaire.h"

/**
*@brief Gestionnaire default constructor. Initializes empty arrays and
*       attributes.
*/
Gestionnaire::Gestionnaire()
	: nbMembres_(0),
	  capaciteMembres_(CAPACITE_INITIALE),
	  nbCoupons_(0),
	  capaciteCoupons_(CAPACITE_INITIALE)
{
	membres_ = new Membre*[capaciteMembres_];
	coupons_ = new Coupon*[capaciteCoupons_];
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
	membres_ = nullptr;
	for (int i = 0; i < nbCoupons_; i++) {
		delete coupons_[i];
	}
	delete[] coupons_;
	coupons_ = nullptr;
}

/**
*@brief Get pointer to array 'membres_'.
*@return attribute membres_.
*/
Membre** Gestionnaire::getMembres() const
{
	return membres_;
}

/**
*@brief Get the number of members.
*@return attribute nbMembres_.
*/
int Gestionnaire::getNbMembres() const
{
	return nbMembres_;
}

/**
*@brief Get the total size of array 'membres_'.
*@return attribute capaciteMembres_.
*/
int Gestionnaire::getCapaciteMembres() const
{
	return capaciteMembres_;
}

/**
*@brief Get the pointer to array of coupons.
*@return attribute coupons_.
*/
Coupon** Gestionnaire::getCoupons() const
{
	return coupons_;
}

/**
*@brief Get the number of coupons.
*@return attribute nbCoupons_.
*/
int Gestionnaire::getNbCoupons() const
{
	return nbCoupons_;
}

/**
*@brief Get the total size of array 'coupons_'.
*@return attribute capaciteCoupons_.
*/
int Gestionnaire::getCapaciteCoupons() const
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
		// Select an appropriate capacity.
		int expandedCapacity = (capaciteMembres_ == 0) ?
			capaciteMembres_ = CAPACITE_INITIALE : capaciteMembres_ * 2;
		// Copy previously held attributes.
		Membre** expandedArray = new Membre*[expandedCapacity];
		for (int i = 0; i < nbMembres_; i++) {
			expandedArray[i] = membres_[i];
		}
		delete[] membres_;
		membres_ = expandedArray;
		capaciteMembres_ = expandedCapacity;
	}
	// Add a new element to the array.
	membres_[nbMembres_++] = new Membre(nomMembre);
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
		// Select an appropriate capacity.
		int expandedCapacity = (capaciteCoupons_ == 0) ?
			capaciteCoupons_ = CAPACITE_INITIALE : capaciteCoupons_ * 2;
		// Copy previously held attributes.
		Coupon** expandedArray = new Coupon*[expandedCapacity];
		for (int i = 0; i < nbCoupons_; i++) {
			expandedArray[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = expandedArray;
		capaciteCoupons_ = expandedCapacity;
	}
	coupons_[nbCoupons_++] = new Coupon(code, rabais, cout);
}

/**
*@brief Find and return a member in the list of members.
*@param nomMembre Name of the member to look for.
*@return Pointer to the member of the desired name.
*/
Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (int i = 0; i < nbMembres_; i++) {
		if (membres_[i]->getNom() == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Error: member '" << nomMembre << "' was not found." << endl;
	return nullptr;
}

/**
*@brief Assigns a ticket to a member identified by their name.
*       If the member owns one or many coupons, apply the best discount.
*@param nomMember Name of the member to which a ticket is assigned.
*@param pnr Identifier for the assigned ticket.
*@param prixBase Full price of the ticket.
*@param od Origin and destination for the ticket.
*@param tarif Type tarification.
*@param dateVol FLight date.
*@param utiliserCoupon Whether or not use a discount.
*/
void Gestionnaire::assignerBillet(const string& nomMembre,
	const string& pnr, double prixBase, const string& od,
	TarifBillet tarif, const string& dateVol,
	bool utiliserCoupon)
{
	double prix = prixBase;
	Membre* membre = trouverMembre(nomMembre);
	if (utiliserCoupon) {
		prix = appliquerCoupon(membre, prixBase);
	}
	membre->ajouterBillet(pnr, prix, od,
		tarif, dateVol);
}

/**
*@brief Select a member's best coupon and compute the discounted
*       ticket price. The coupon is thence withdrawn from a member's set.
*@param membre The member for which a discount is to be applied.
*@param prix Price of the ticket to purchase.
*/
double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	// Assess whether a member owns at least one coupon.
	int nCoupons = membre->getNbCoupons();
	if (nCoupons == 0) {
		cout << "Error: member " << membre->getNom()
			<< " has no coupon." << endl;
		return prix;
	}
	// Select the best coupon.
	Coupon** coupons = membre->getCoupons();
	Coupon* bestCoupon = coupons[0];
	double rabais = bestCoupon->getRabais();
	for (int i = 1; i < nCoupons; i++) {
		if (coupons[i]->getRabais() > bestCoupon->getRabais()) {
			bestCoupon = coupons[i];
		}
	}
	double reducedPrice = (1.0 - bestCoupon->getRabais()) * prix;
	membre->retirerCoupon(bestCoupon);
	return reducedPrice;
}

/**
*@brief Buy the best available coupon for a client.
*@param nomMembre Name of the member for which a coupon is purchased.
*/
void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	// Find the best discount that can be purchased.
	Membre* membre = trouverMembre(nomMembre);
	int maxPrice = membre->getPoints();
	Coupon* bestCoupon = nullptr;
	double rabais = 0.0;
	int couponID = 0;
	for (int i = 0; i < nbCoupons_; i++) {
		if (coupons_[i]->getCout() <= maxPrice) {
			rabais = coupons_[i]->getRabais();
			if (i == 0 || rabais > bestCoupon->getRabais()) {
				bestCoupon = coupons_[i];
				couponID = i;
			}
		}
	}
	// Buy the coupon if one has been found.
	if (bestCoupon != nullptr) {
		trouverMembre(nomMembre)->acheterCoupon(bestCoupon);
		// TODO: Remove the coupon from the set?
		//Coupon** reducedArray = new Coupon*[capaciteCoupons_];
		//int skipDeletedCoupon = 0;
		//for (unsigned int i = 0; i < nbCoupons_ - 1; i++) {
		//	if (i == couponID) {
		//		skipDeletedCoupon = 1;
		//	}
		//	reducedArray[i] = coupons_[i + skipDeletedCoupon];
		//}
		//delete[] coupons_;
		//coupons_ = reducedArray;
		//nbCoupons_--;
	}
	else {
		cout << "Error: member '" << nomMembre << "' cannot "
			<< "buy a coupon." << endl;
	}
}

/**
*@brief Print information for all members.
*/
void Gestionnaire::afficherInfos() const
{
	cout << "====================ETAT ACTUEL DU PROGRAMME==================="
		<< endl << endl;
	for (int i = 0; i < nbMembres_; i++) {
		membres_[i]->afficherMembre();
		cout << endl;
	}
}
