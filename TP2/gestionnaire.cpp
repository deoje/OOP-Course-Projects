/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "gestionnaire.h"

Gestionnaire::Gestionnaire()
{
}

Gestionnaire::~Gestionnaire()
{
	for (int i = 0; i < membres_.size(); i++) {
		delete membres_[i];
	}

	for (int i = 0; i < coupons_.size(); i++) {
		delete coupons_[i];
	}
}

vector<Membre*> Gestionnaire::getMembres() const
{
	return membres_;
}

int Gestionnaire::getNbMembres() const
{
	return membres_.size();
}

int Gestionnaire::getCapaciteMembres() const
{
	return membres_.capacity();
}

vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}

int Gestionnaire::getNbCoupons() const
{
	return coupons_.size();
}

int Gestionnaire::getCapaciteCoupons() const
{
	return coupons_.capacity();
}

void Gestionnaire::ajouterMembre(const string& nomMembre)
{
	membres_.push_back(new Membre(nomMembre));
}

void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	coupons_.push_back(new Coupon(code, rabais, cout));
}

Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (int i = 0; i < membres_.size(); i++) {
		// TODO: Faite cette comparaison avec la surcharge de l'operateur == de la classe Membre
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}

void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon)
{
	double prixReel;
	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	if (utiliserCoupon) {
		prixReel = prixBase - appliquerCoupon(membre, prixBase);
	}
	else {
		prixReel = prixBase;
	}
	membre->ajouterBillet(pnr, prixReel, od, tarif, dateVol);
}

double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	if (membre->getNbCoupons() == 0) {
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}

	Coupon* meilleurCoupon = membre->getCoupons()[0];
	vector<Coupon*> coupons = membre->getCoupons();
	for (int i = 1; i < membre->getNbCoupons(); i++) {
		if (*(coupons[i]) > *(meilleurCoupon)) {
			meilleurCoupon = membre->getCoupons()[i];
		}
	}

	// TODO: Utiliser la surcharge de l'operateur -= de la classe Membre plutot qu'utiliser la methode retirerCoupon
	*membre -= meilleurCoupon;

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

	for (int i = 0; i < coupons_.size(); i++) {
		if (membre->getPoints() >= coupons_[i]->getCout()) {
			// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
			if (meilleurCoupon == nullptr) {
				meilleurCoupon = coupons_[i];
			}
			// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
			// TODO: Faites cette comparaison avec la surcharge de l'operateur > de la classe Coupon
			else if (coupons_[i] > meilleurCoupon) {
				meilleurCoupon = coupons_[i];
			}
		}
	}

	if (meilleurCoupon) {
		membre->acheterCoupon(meilleurCoupon);
	}
	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

ostream& operator<< (ostream& os, const Gestionnaire& gestionnaire)
{
	os << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for (int i = 0; i < gestionnaire.getNbMembres(); i++) {
		os << *(gestionnaire.getMembres()[i]);
	}
	return os;
}