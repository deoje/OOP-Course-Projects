/********************************************
* Titre: Travail pratique #6 - membre.cpp
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/
#include "membre.h"

#include <algorithm>

Membre::Membre() :
	nom_("")
{
}

Membre::Membre(const string& nom) :
	nom_(nom)
{
}

//todo
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	copy(membre.billets_.begin(), membre.billets_.end(), back_inserter(billets_));
}

//todo
Membre::~Membre()
{
	for (vector<Billet*>::iterator it = billets_.begin(); it != billets_.end(); it++) {
		delete* it;
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

//todo
vector<Billet*>::iterator Membre::trouverBillet(const string& pnr)
{
	
	return find_if(billets_.begin(), billets_.end(), [&](Billet* b1) {return b1->getPnr() == pnr; });
}

//todo
void Membre::utiliserBillet(const string& pnr)
{

	auto itBillet = trouverBillet(pnr);
	if (itBillet == billets_.end()) {
		cout << "Le billet n'est pas trouve" << endl;
		return;
	}

	if (auto flightPass = dynamic_cast<FlightPass*>(*itBillet)) {
		flightPass->decrementeNbUtilisations();
		if (flightPass->getNbUtilisationsRestante() > 0) {
			return;
		}
	}

	delete* itBillet;
	billets_.erase(itBillet);
}

void Membre::ajouterBillet(Billet* billet)
{
	billet->setNomPassager(nom_);
	billets_.push_back(billet);
}

bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}

//todo
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;

		for (auto it = billets_.begin(); it != billets_.end(); it++) {
			delete* it;
		}

		billets_.clear();

		copy(membre.billets_.begin(), membre.billets_.end(), back_inserter(billets_));

	}

	return *this;
}

//todo
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;

	copy(billets_.begin(), billets_.end(), ostream_iterator<Billet*>(o));
}
