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

// TODO
void Gestionnaire::assignerBillet(Billet* billet, const string& nomMembre, bool utiliserCoupon)
	{
	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		delete billet;
		return;
	}

	double prix = billet->getPrix();

	if (utiliserCoupon) {
		prix -= appliquerCoupon(membre, prix);
	}

	switch (membre->getTypeMembre()) {
	case Membre_Premium:
		double rabais = 0.005 * static_cast<MembrePremium*>(membre)->getpointsCumulee() / 1000;
		if (rabais > 0.1)
			rabais = 0.1;

		prix *= (1 - rabais);
		billet->setPrix(prix);
		static_cast<MembrePremium*>(membre)->ajouterBillet(billet);
		break;
	case Membre_Occasionnel:
		billet->setPrix(prix);
		membre->ajouterBillet(billet);
		break;
	case Membre_Regulier:
		billet->setPrix(prix);
		static_cast<MembreRegulier*>(membre)->ajouterBillet(billet);
		break;
	}
	
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

// TODO
double Gestionnaire::calculerRevenu()
{
	
}

// TODO
int Gestionnaire::calculerNombreBilletsEnSolde()
{

}

// TODO: Retirer cette fonction par afficher()
ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for (int i = 0; i < gestionnaire.membres_.size(); ++i) {
		switch (gestionnaire.membres_[i]->getTypeMembre())
		{
		case Membre_Premium:
			o << *static_cast<MembrePremium*>(gestionnaire.membres_[i]);
			break;
		case Membre_Occasionnel:
			o << *gestionnaire.membres_[i];
			break;
		case Membre_Regulier:
			o << *static_cast<MembreRegulier*>(gestionnaire.membres_[i]);
			break;
		}
	}

	return o;
}
	
// TODO
void Gestionnaire::afficher(ostream& o)
{
	
}