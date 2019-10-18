/*
* Titre : gestionnaire.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "gestionnaire.h"

Gestionnaire::Gestionnaire()
{
}

Gestionnaire::~Gestionnaire()
{
	for (size_t i = 0; i < membres_.size(); ++i) {
		delete membres_[i];
	}

	for (size_t i = 0; i < coupons_.size(); ++i) {
		delete coupons_[i];
	}
}

vector<Membre*> Gestionnaire::getMembres() const
{
	return membres_;
}

vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}

void Gestionnaire::ajouterMembre(Membre* membre)
{
	membres_.push_back(membre);
}

void Gestionnaire::ajouterCoupon(Coupon* coupon)
{
	coupons_.push_back(coupon);
}

Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (size_t i = 0; i < membres_.size(); ++i) {
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}

/**
*	@brief Ticket assigning method.
*	@param billet Pointer to the ticket that will be assigned.
*	@param nomMembre Member name
*	@param utiliserCoupon Boolean indicating whether a coupon is used or not.
*/
void Gestionnaire::assignerBillet(Billet* billet, const string& nomMembre, bool utiliserCoupon)
	{
	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		delete billet;
		return;
	}

	double basePrice = billet->getPrix();
	double price = basePrice;

	// Discount obtained from using a coupon.
	if (utiliserCoupon) {
		price -= appliquerCoupon(membre, basePrice);
	}

	// Discount obtained from premium membership.
	if (MembrePremium* membrePremium = dynamic_cast<MembrePremium*>(membre)) {
		double discount = 0.005 * membrePremium->getpointsCumulee() / 1000;
		if (discount > 0.1)
			discount = 0.1;

		price -= basePrice * (1 - discount);
	}

	billet->setPrix(price);
	membre->ajouterBillet(billet);
	
}

double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	MembreRegulier* membreReg = dynamic_cast<MembreRegulier*>(membre);

	if (!membreReg || membreReg->getCoupons().size() == 0) {
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}

	Coupon* meilleurCoupon = membreReg->getCoupons()[0];
	vector<Coupon*> coupons = membreReg->getCoupons();
	for (size_t i = 1; i < coupons.size(); ++i) {
		if (*coupons[i] > *meilleurCoupon) {
			meilleurCoupon = coupons[i];
		}
	}

	*membreReg -= meilleurCoupon;

	return prix * meilleurCoupon->getRabais();
}

void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	if (coupons_.size() == 0) {
		cout << "Le gestionnaire n'a pas de coupon!" << endl;
		return;
	}

	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	Coupon* meilleurCoupon = nullptr;

	if (auto membreRegulier = dynamic_cast<MembreRegulier*>(membre)) {
		for (size_t i = 0; i < coupons_.size(); ++i) {
			if (membreRegulier->peutAcheterCoupon(coupons_[i])) {
				// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
				if (meilleurCoupon == nullptr) {
					meilleurCoupon = coupons_[i];
				}
				// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
				else if (*coupons_[i] > * meilleurCoupon) {
					meilleurCoupon = coupons_[i];
				}
			}
		}
		if (meilleurCoupon) {
			membreRegulier->acheterCoupon(meilleurCoupon);
		}
		else {
			cout << "Le membre ne peut acheter de coupon\n";
		}
	}
	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

/**
*	@brief Revenu calculating method
*/
double Gestionnaire::calculerRevenu()
{
	double revenu = 0.0;
	for (int i = 0; i < membres_.size(); i++) {
		// Sum all the prices of all tickets.
		for (int j = 0; j < membres_[i]->getBillets().size(); j++) {
			revenu += membres_[i]->getBillets()[j]->getPrix();
		}
	}
	return revenu;
}

/**
*	@brief This method computes the number of discounted tickets.
*/
int Gestionnaire::calculerNombreBilletsEnSolde()
{
	int nBillets = 0;
	for (int i = 0; i < membres_.size(); i++) {
		for (int j = 0; j < membres_[i]->getBillets().size(); j++) {
			// A ticket is discounted if it inherited "Solde"
			if (dynamic_cast<BilletRegulierSolde*>(membres_[i]->getBillets()[j])) {
				nBillets++;
			}
			else if (dynamic_cast<FlightPassSolde*>(membres_[i]->getBillets()[j])) {
				nBillets++;
			}
		}
	}
	return nBillets;
}
	
/**
*	@brief Printing method for the whole class.
*	@param o The output stream used for display.
*/
void Gestionnaire::afficher(ostream& o)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for (int i = 0; i < membres_.size(); ++i) {
		membres_[i]->afficher(o);
	}
	o << endl;
}