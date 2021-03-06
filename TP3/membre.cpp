/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe C�T�-MORNEAULT
 */

#include "membre.h"

Membre::Membre() :
	nom_(""),
	typeMembre_(Membre_Occasionnel) // Added for inheritance
{
}

Membre::Membre(const string& nom, TypeMembre typeMembre) :
	nom_(nom),
	typeMembre_(typeMembre) // Added for inheritance
{
}

/**
*	@brief Copy Constructor for the Member Class
*	@param membre The reference to the member object to copy
*/

Membre::Membre(const Membre& membre) :
	nom_(membre.nom_),
	typeMembre_(membre.typeMembre_)
{
	for (int i = 0; i < membre.getBillets().size(); ++i) {
		Billet* billet = membre.getBillets()[i];
		switch (billet->getTypeBillet()) {
			case Billet_Base: {
				billets_.push_back(new Billet(*billet));
			}
				break;
			case Billet_Regulier: {
				BilletRegulier* billetRegulier = static_cast<BilletRegulier*>(billet);
				billets_.push_back(new BilletRegulier(billetRegulier->getPnr(),
					nom_, billetRegulier->getPrix(), billetRegulier->getOd(),
					billetRegulier->getTarif(), billetRegulier->getDateVol(),
					billetRegulier->getTypeBillet()));
			}
				break;
			case Flight_Pass:{
				billets_.push_back(new FlightPass(billet->getPnr(),
					nom_, billet->getPrix(), billet->getOd(),
					billet->getTarif(), billet->getTypeBillet()));
			}
				break;
		}
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

TypeMembre Membre::getTypeMembre() const
{
	return typeMembre_;
}


void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

/**
*	@brief ajouterBillet To create a specific type of ticket and then add it to a member
*	@param pnr String representing the ticket's ID
*	@param prix Double representing the ticket's price
*	@param od Constant reference to a string representing the ticket's origin and destination
*	@param tarif TarifBillet enum to set the ticket's class (economie, affaire ...)
*	@param typeBillet TypeBillet enum to set the ticket's type
*	@param dateVol String representing the ticket's date of flight
*/
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{ 
	switch (typeBillet) {
		case Billet_Base:
			billets_.push_back(new Billet(pnr, nom_, prix, od, tarif, Billet_Base));
			break;
		case Billet_Regulier:
			billets_.push_back(new BilletRegulier(pnr, nom_, prix, od, tarif, dateVol, Billet_Regulier));
			break;
		case Flight_Pass:
			billets_.push_back(new FlightPass(pnr, nom_, prix, od, tarif, Flight_Pass));
			break;
	}
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

/**
*	@brief utiliserBillet To use a member's ticket
*	@param pnr String representing the ticket's ID
*/

void Membre::utiliserBillet(const string& pnr) {
	for (int i = 0; i < billets_.size(); ++i) {
		if (billets_[i]->getPnr() == pnr) {
			bool mustRemove = false;
			// If it is a FlightPass, handle number of use
			if (billets_[i]->getTypeBillet() == Flight_Pass) {
				FlightPass* flightPass = static_cast<FlightPass*>(billets_[i]);
				flightPass->decrementeNbUtilisations();
				if (flightPass->getNbUtilisationsRestante() <= 0) {
					mustRemove = true;
				}
			}
			// If it is a regular pass, it must be removed.
			else {
				mustRemove = true;
			}
			if (mustRemove) {
				delete billets_[i];
				billets_[i] = billets_[billets_.size() - 1];
				billets_.pop_back();
				// Exit the function, because other tickets won't be removed.
				return;
			}
		}
	}
	// This part of the function is executed only if no "Billet" has been
	// found (a "return" statement in the loop terminates the function
	// once a ticket is found).
	cout << "Le billet '" << pnr << "' est introuvable." << endl;
}

/**
*	@brief Operator overload (<<) to print the state of the current member
*/
ostream& operator<<(ostream& o, const Membre& membre)
{
	o << setfill(' ');
	o << "- Membre " << membre.nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	for (int i = 0; i < membre.billets_.size(); i++) {
		if (membre.billets_[i]->getTypeBillet() == Flight_Pass) {
			o << *(static_cast<FlightPass*>(membre.billets_[i]));
			continue;
		}
		o << *membre.billets_[i];
	}

	return o << endl;
}
