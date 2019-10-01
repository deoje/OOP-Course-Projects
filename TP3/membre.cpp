/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

//a changer
Membre::Membre() :
	nom_("")
{
}

//a changer
Membre::Membre(const string& nom, TypeMembre typeMembre) :
	nom_(nom)
{
}

//a changer
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	for (int i = 0; i < membre.billets_.size(); ++i) {
		billets_.push_back(new Billet(*membre.billets_[i]));
	}
}

Membre::~Membre()
{
	for (int i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}

string Membre::getNom() const
{
	return nom_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}


void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

// a changer
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, typeBillet);
	billets_.push_back(billet);

	//inutile, cette classe ne fait pas partie du programme de fidèlité.
	//modifierPoints(calculerPoints(billet));
}



bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}

Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;
		typeMembre_ = membre.typeMembre_;


		for (int i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		for (int i = 0; i < membre.billets_.size(); i++) {
			billets_.push_back(new Billet(*membre.billets_[i]));
		}
	}

	return *this;
}

// a changer
ostream& operator<<(ostream& o, const Membre& membre)
{
	o << setfill(' ');
	o << "- Membre " << membre.nom_ << ":" << endl;
	o << "\t" << left << setw(10) << "- Points" << ": " << membre.points_ << endl;
	o << "\t" << "- Billets :" << endl;
	for (int i = 0; i < membre.billets_.size(); i++) {
		o << *membre.billets_[i];
	}
	o << "\t" << "- Coupons :" << endl;
	for (int i = 0; i < membre.coupons_.size(); i++) {
		o << *membre.coupons_[i];
	}

	return o << endl;
}
