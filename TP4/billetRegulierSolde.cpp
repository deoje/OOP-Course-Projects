/*
* Titre : billetRegulierSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "billetRegulierSolde.h"


BilletRegulierSolde::BilletRegulierSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol, double pourcentageSolde)
	: BilletRegulier(pnr,prix,od,tarif,dateVol), Solde(pourcentageSolde)
{
}


double BilletRegulierSolde::getPrix() const
{
	return getPrixBase() * (1 - getPourcentageSolde());
}


double BilletRegulierSolde::getPrixBase() const
{
	return Billet::getPrix(); // Billet ou Billet regulier ?
}


BilletRegulierSolde* BilletRegulierSolde::clone() const
{
	return new BilletRegulierSolde(
		getPnr(),
		getPrix(),
		getOd(),
		getTarif(),
		getDateVol(),
		getPourcentageSolde()
	);
}


void BilletRegulierSolde::afficher(ostream& o) const
{
	BilletRegulier::afficher(o);
	o << "\t\t\t" << setw(11) << "- Pourcentage solde" << ": " << getPourcentageSolde() << "%" << endl;
}