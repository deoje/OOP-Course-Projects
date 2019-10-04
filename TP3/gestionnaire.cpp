/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe C�T�-MORNEAULT
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

vector<Coupon*> Gestionnaire::getCoupons() const
{
	return coupons_;
}

void Gestionnaire::ajouterMembre(const string& nomMembre, TypeMembre typeMembre)
{
	switch (typeMembre) {
	case Membre_Occasionnel:
		membres_.push_back(new Membre(nomMembre, typeMembre));
		break;
	case Membre_Regulier:
		membres_.push_back(new MembreRegulier(nomMembre, typeMembre));
		break;
	case Membre_Premium:
		membres_.push_back(new MembrePremium(nomMembre));
		break;
	}
}

void Gestionnaire::ajouterCoupon(const string& code, double rabais, int cout)
{
	coupons_.push_back(new Coupon(code, rabais, cout));
}

Membre* Gestionnaire::trouverMembre(const string& nomMembre) const
{
	for (int i = 0; i < membres_.size(); i++) {
		if (*membres_[i] == nomMembre) {
			return membres_[i];
		}
	}
	cout << "Le membre " << nomMembre << " n'existe pas\n";

	return nullptr;
}

void Gestionnaire::assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon, TypeBillet typeBillet)
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
	if (typeBillet == Flight_Pass) {
		prixReel *= 10;
	}
	if (membre->getTypeMembre() == Membre_Premium) {
		MembrePremium* membrePremium = static_cast<MembrePremium*>(membre);
		double deduction = double(membrePremium->getpointsCumulee()) / 1000.0 * (0.5 / 100.0);
		if (deduction > 0.1) {
			deduction = 0.1;
		}
		prixReel *= (1.0 - deduction);
		membrePremium->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
	}

	if (membre->getTypeMembre() == Membre_Occasionnel) {
		membre->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
	}
	else {
		MembreRegulier* tempMembre = static_cast<MembreRegulier*>(membre);
		tempMembre->ajouterBillet(pnr, prixReel, od, tarif, typeBillet, dateVol);
	}
}

double Gestionnaire::appliquerCoupon(Membre* membre, double prix)
{
	MembreRegulier* membreRegulier = static_cast<MembreRegulier*>(membre);
	if (membreRegulier->getCoupons().size() == 0) {
		cout << "Le membre n'a pas de coupon utilisable\n";
		return 0;
	}

	Coupon* meilleurCoupon = membreRegulier->getCoupons()[0];
	vector<Coupon*> coupons = membreRegulier->getCoupons();
	for (int i = 1; i < coupons.size(); ++i) {
		if (*coupons[i] > *meilleurCoupon) {
			meilleurCoupon = coupons[i];
		}
	}

	*membreRegulier -= meilleurCoupon;

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

	MembreRegulier* membreRegulier = static_cast<MembreRegulier*>(membre);
	for (int i = 0; i < coupons_.size(); i++) {
		if (membreRegulier->getPoints() >= coupons_[i]->getCout()) {
			// Si on avait pas encore trouve de meilleur coupon, on fait la premiere assignation
			if (meilleurCoupon == nullptr) {
				meilleurCoupon = coupons_[i];
			}
			// Sinon on compare si le coupon courant a un rabais superieur au meilleur coupon
			else if (*coupons_[i] > *meilleurCoupon) {
				meilleurCoupon = coupons_[i];
			}
		}
	}

	if (meilleurCoupon) {
		if (membreRegulier->getTypeMembre() == Membre_Premium) {
			MembrePremium* tempMembre = static_cast<MembrePremium*>(membreRegulier);
			tempMembre->acheterCoupon(meilleurCoupon);
		}
		else {
			membreRegulier->acheterCoupon(meilleurCoupon);
		}
	}
	else {
		cout << "Le membre ne peut acheter de coupon\n";
	}
}

ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire)
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for (int i = 0; i < gestionnaire.membres_.size(); i++) {
		o << *gestionnaire.membres_[i];
	}

	return o;
}
