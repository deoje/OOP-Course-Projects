/*
* Titre : billetRegulier.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "billetRegulier.h"

BilletRegulier::BilletRegulier(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol) : 
	Billet(pnr, prix, od, tarif), dateVol_(dateVol)
{
}

string BilletRegulier::getDateVol() const
{
	return dateVol_;
}

void BilletRegulier::setDateVol(string dateVol)
{
	dateVol_ = dateVol;
}

/**
*	@brief clone To create a dynamically allocated exact copy of this object
*	@return BilletRegulier* pointer to the copy
*/
BilletRegulier* BilletRegulier::clone() const
{
	return new BilletRegulier(
		getPnr(),
		getPrix(),
		getOd(),
		getTarif(),
		dateVol_
	);
}

/**
*	@brief afficher To print out the current state of the object
*	@param o Ostream reference
*/
void BilletRegulier::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Vol le" << ": " << dateVol_ << endl;
}