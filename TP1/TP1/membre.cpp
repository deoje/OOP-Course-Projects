#include <iomanip>
#include "membre.h"
#include "def.h"


Membre::Membre()
	: nom_("no_name"),
	points_(0),
	nbBillets_(0),
	capaciteBillets_(CAPACITE_INITIALE),
	nbCoupons_(0),
	capaciteCoupons_(CAPACITE_INITIALE)
{
	/**
	* @brief Coupon Default constructor of the class
	*/
	/*
		Billets
	*/
	billets_ = new Billet*[CAPACITE_INITIALE];
	/*
		Coupons
	*/
	coupons_ = new Coupon*[CAPACITE_INITIALE];
}

Membre::Membre(const string& nom)
	: nom_(nom),
	points_(0),
	nbBillets_(0),
	capaciteBillets_(CAPACITE_INITIALE),
	nbCoupons_(0),
	capaciteCoupons_(CAPACITE_INITIALE)
{
	/**
	* @brief Coupon Constructor with parameters receiving its code, rabais and
	*        cout
	* @param nom Constant reference of a string representing the name of the
	* membre
	*/
	/*
		Billets
	*/
	billets_ = new Billet * [CAPACITE_INITIALE];
	/*
		Coupons
	*/
	coupons_ = new Coupon * [CAPACITE_INITIALE];
}

Membre::~Membre()
{
	/**
	* @brief Coupon Destructor
	*/
	// Since this class creates the pointers for Billets
	// we deallocate the memory in the destructor
	for (int i = 0; i < nbBillets_; i++)
	{
		delete billets_[i];
	}

	delete[] billets_;
	billets_ = nullptr;

	delete[] coupons_;
	coupons_ = nullptr;
}

string Membre::getNom() const
{
	/**
	* @brief getNom to get the name of the member
	* @return string representing the name of the member 
	*/
	return nom_;
}

int Membre::getPoints() const
{
	/**
	* @brief getPoints to get the points of the member
	* @return int representing the points a member has
	*/
	return points_;
}

Billet** Membre::getBillets() const
{
	/**
	* @brief getBillets to get the pointer to the array of billet
	* @return a pointer to an array of pointers of billet
	*/
	return billets_;
}

int Membre::getNbBillets() const
{
	/**
	* @brief getNbBillets to get the number of billet the member has
	* @return int representing the number of billet
	*/
	return nbBillets_;
}

int Membre::getCapaciteBillets() const
{
	/**
	* @brief getCapaciteBillets to get the total length of billets_
	* @return int representing the length
	*/
	return capaciteBillets_;
}

Coupon** Membre::getCoupons() const {
	/**
	* @brief getCoupons to get the pointer to the array of coupon
	* @return a pointer to an array of pointers of coupon
	*/
	return coupons_;
}

int Membre::getNbCoupons() const
{
	/**
	* @brief getNbCoupns to get the number of coupons the member has
	* @return int representing the number of coupons
	*/
	return nbCoupons_;
}

int Membre::getCapaciteCoupons() const
{
	/**
	* @brief getCapaciteCoupons to get the total length of coupons_
	* @return int representing the length
	*/
	return capaciteCoupons_;
}

void Membre::setNom(const string& nom) {
	/**
	* @brief setNom to change the name of the member
	* @param nom String representing the new name
	*/
	nom_ = nom;
}

void Membre::modifierPoints(int points) {
	/**
	* @brief modifierPoints to add or remove points_
	* @param points Positive or negative int to add to points_
	*/
	points_ += points;
}

void Membre::ajouterBillet(const string& pnr, double prix,
	const string& od, TarifBillet tarif, const string& dateVol)
{
	/**
	* @brief ajouterBillet to add a Billet to billets_
	*/

	// Creating the new Billet
	Billet* newBillet = new Billet(pnr, getNom(), prix, od, tarif, dateVol);
	// Veryfing if the array billets_ is full
	if (nbBillets_ == capaciteBillets_)
	{
		// Calculating the new length of billets_
		int newCapacity = capaciteBillets_ * 2;

		// Creating the new array with a higher capacity
		Billet** newArray = new Billet * [newCapacity];

		// Filling the new array with the old billets_
		for (int i = 0; i < nbBillets_; i++)
		{
			newArray[i] = billets_[i];
		}

		// Deallocating the memory for the old array
		delete[] billets_;
		// Changing the member field billets_ for newArray
		billets_ = newArray;
		// Updating the capacity
		capaciteBillets_ = newCapacity;
	}
	// Calculate points earned by buying this ticket
	double newPoints = calculerPoints(newBillet);
	// Adding the new points to points_
	modifierPoints(newPoints);
	// Adding the new billets to billets_ and incrementing the value of nbBillets
	billets_[nbBillets_++] = newBillet;
}

void Membre::ajouterCoupon(Coupon* coupon)
{
	/**
	* @brief ajouterCoupon to add a coupon to coupons_
	* @param coupon New coupon to add
	*/

	// Verifying if we reached the maximum capacity of coupons_
	if (nbCoupons_ == capaciteCoupons_)
	{	
		// increasing the capacity
		int newCapacity = capaciteCoupons_ *2;

		// Creating the new bigger array
		Coupon** newArray = new Coupon * [newCapacity];

		// Filling the new array with coupons_'s content
		for (int i = 0; i < nbCoupons_; i++) {
			newArray[i] = coupons_[i];
		}

		// Delete the old coupon_
		delete[] coupons_;
		// Replace coupons_ with newArray
		coupons_ = newArray;
		// Update the capacity
		capaciteCoupons_ = newCapacity;
	}
	// Add the coupon to the array
	coupons_[nbCoupons_] = coupon;

	// Increment nbBillets to update it
	nbCoupons_++;
}

void Membre::retirerCoupon(Coupon* coupon)
{
	/**
	* @brief retirerCoupon to remove a coupon from coupons_
	* @param coupon The coupon to remove
	*/

	// Loop through all the coupons in coupons_
	for (int i = 0; i < nbCoupons_; i++) {

		// For the first encounter of the coupon with the same code
		if (coupons_[i]->getCode() == coupon->getCode()) {
			// Replace it and the following one with these last ones
			for (int j = i; j < nbCoupons_ - 1;j++) {
				coupons_[j] = coupons_[j + 1];
			}
			// Decrease by one the value of the coupons
			nbCoupons_--;
			// Go out of the loop once we find the right coupon and remove it
			break;
		}
	}
}

void Membre::acheterCoupon(Coupon* coupon) {

	/**
	* @brief acheterCoupon to buy a coupon
	* @param coupon The new coupon
	*/
	// Verify if there's enough points to by coupon
	if (getPoints() >= coupon->getCout())
	{
		// add coupon to table
		ajouterCoupon(coupon);
		// Deduct points used to buy the coupon
		modifierPoints(coupon->getCout() * -1);
	}
}

double Membre::calculerPoints(Billet* billet) const
{
	/**
	* @brief calculerPoints To calculate points gained with billet
	*/
	// calculate the base points earned
	double basePoints = billet->getPrix() * 0.1;

	double bonusPoints = 0;

	// Verify if bonus points
	if (billet->getTarif() == TarifBillet::PremiumEconomie)
	{
		bonusPoints = 50;
	}
	else if (billet->getTarif() == TarifBillet::Affaire)
	{
		bonusPoints = 150;
	}
	else if (billet->getTarif() == TarifBillet::Premiere)
	{
		bonusPoints = 300;
	}

	return basePoints + bonusPoints;
}

void Membre::afficherMembre() const {

	/**
	* @brief affficherMembre to print the state of the member
	*/
	cout << "- Membre " << nom_ << ":" << endl;
	cout << "\t - Points  : " << points_ << endl;
	cout << "\t - Billets : ";
	if (nbBillets_ == 0) {
		cout << " Aucun billet" << endl;
	}
	else {
		cout << endl;
		for (int i = 0; i < nbBillets_; i++) {
			billets_[i]->afficherBillet();
		}
	}
	cout << "\t - Coupons : ";
	if (nbCoupons_ == 0) {
		cout << " Aucun coupon" << endl;
	}
	else {
		cout << endl;
		for (int i = 0; i < nbCoupons_; i++) {
			coupons_[i]->afficherCoupon();
		}
	}
}