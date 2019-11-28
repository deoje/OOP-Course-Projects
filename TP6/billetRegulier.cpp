/********************************************
* Titre: Travail pratique #6 - billetRegulier.cpp
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/

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

BilletRegulier* BilletRegulier::clone() const
{
	return new BilletRegulier(*this);
}

void BilletRegulier::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Vol le" << ": " << dateVol_ << endl;
}
