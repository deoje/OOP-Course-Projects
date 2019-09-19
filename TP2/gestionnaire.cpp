/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "gestionnaire.h"

Gestionnaire::Gestionnaire() :
	membres_(new Membre*[CAPACITE_INITIALE]),
	nbMembres_(0),
	capaciteMembres_(CAPACITE_INITIALE),
	coupons_(new Coupon*[CAPACITE_INITIALE]),
	nbCoupons_(0),
	capaciteCoupons_(CAPACITE_INITIALE)
{
}

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

Membre** Gestionnaire::getMembres() const
{
	return membres_;
}

int Gestionnaire::getNbMembres() const
{
	return nbMembres_;
}

int Gestionnaire::getCapaciteMembres() const
{
	return capaciteMembres_;
}

Coupon** Gestionnaire::getCoupons() const
{
	return coupons_;
}

int Gestionnaire::getNbCoupons() const
{
	return nbCoupons_;
}

int Gestionnaire::getCapaciteCoupons() const
{
	return capaciteCoupons_;
}

void Gestionnaire::ajouterMembre(const string& nomMembre)
{
	Membre* membre = new Membre(nomMembre);
	if (nbMembres_ >= capaciteMembres_) {
		capaciteMembres_ *= 2;

		Membre** temp = new Membre* [capaciteMembres_];

		for (int i = 0; i < nbMembres_; i++) {
			temp[i] = membres_[i];
		}
		delete[] membres_;

		membres_ = temp;
	}
	membres_[nbMembres_++] = membre;
}

void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	Coupon* coupon = new Coupon(code, rabais, cout);
	if (nbCoupons_ >= capaciteCoupons_) {
		capaciteCoupons_ *= 2;

		Coupon** temp = new Coupon * [capaciteCoupons_];

		for (int i = 0; i < nbCoupons_; i++) {
			temp[i] = coupons_[i];
		}
		delete[] coupons_;

		coupons_ = temp;
	}
	coupons_[nbCoupons_++] = coupon;
}

Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (int i = 0; i < nbMembres_; i++) {
		// TODO: Faite cette comparaison avec la surcharge de l'operateur == de la classe Membre
		if (membres_[i]->getNom() == nomMembre) {
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
	Coupon** coupons = membre->getCoupons();
	for (int i = 1; i < membre->getNbCoupons(); i++) {
		// TODO: Faites cette comparaison par la surcharge de l'operateur > de la classe Coupon
		if (coupons[i]->getRabais() > meilleurCoupon->getRabais()) {
			meilleurCoupon = membre->getCoupons()[i];
		}
	}

	// TODO: Utiliser la surcharge de l'operateur -= de la classe Membre plutot qu'utiliser la methode retirerCoupon
	membre->retirerCoupon(meilleurCoupon);

	return prix * meilleurCoupon->getRabais();
}

void Gestionnaire::acheterCoupon(const string& nomMembre)
{
	if (nbCoupons_ == 0) {
		cout << "Le gestionnaire n'a pas de coupon!" << endl;
		return;
	}

	Membre* membre = trouverMembre(nomMembre);

	if (membre == nullptr) {
		return;
	}

	Coupon* meilleurCoupon = nullptr;

	for (int i = 0; i < nbCoupons_; i++) {
		if (membre->getPoints() >= coupons_[i]->getCout()) {
			// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
			if (meilleurCoupon == nullptr) {
				meilleurCoupon = coupons_[i];
			}
			// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
			// TODO: Faites cette comparaison avec la surcharge de l'operateur > de la classe Coupon
			else if (coupons_[i]->getRabais() > meilleurCoupon->getRabais()) {
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

// TODO: Remplacer cette methode par l'operateur <<
void Gestionnaire::afficherInfos() const
{
	cout << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for (int i = 0; i < nbMembres_; i++) {
		membres_[i]->afficherMembre();
	}
}
