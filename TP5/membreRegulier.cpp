/********************************************
* Titre: Travail pratique #5 - membreRegulier.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "membreRegulier.h"

MembreRegulier::MembreRegulier(const string& nom) : 
	Membre(nom), points_(0)
{
}

int MembreRegulier::getPoints() const
{
	return points_;
}

vector<Coupon*> MembreRegulier::getCoupons() const
{
	return coupons_;
}

void MembreRegulier::ajouterBillet(Billet* billet)
{
	Membre::ajouterBillet(billet);
	modifierPoints(calculerPoints(billets_.back()));
}

Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	coupons_.erase(std::remove(coupons_.begin(), coupons_.end(), coupon), coupons_.end());
	//remove(coupons_.begin(), coupons_.end(), coupon);
	//cout << coupons_.size() << endl;
	//remove_if(coupons_.begin(), coupons_.end(), [coupon](Coupon* c) -> bool {
	//	cout << int(coupon->getCode() == c->getCode()) << "    ****" << endl;
 	//	return coupon->getCode() == c->getCode();
	//});
	//cout << coupons_.size() << endl;

	return *this;
}

void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}

double MembreRegulier::calculerPoints(Billet* billet) const
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

	return billet->getPrix() * 0.10 + bonus;
}

bool MembreRegulier::peutAcheterCoupon(Coupon* coupon) const
{
	return points_ >= coupon->getCout();
}

void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	if (peutAcheterCoupon(coupon)) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}

void MembreRegulier::afficher(ostream& o) const
{
	Membre::afficher(o);
	o << "\t" << "- Points : " << points_ << endl;
	o << "\t" << "- Coupons :" << endl;

	copy(billets_.begin(), billets_.end(), ostream_iterator<Billet*>(o, "\n"));
}
