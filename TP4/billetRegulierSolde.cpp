/*
* Titre : billetRegulierSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "billetRegulierSolde.h"

/**
*	@brief Constructor with parameters which also intiate the state of the
*	inherited classes
*/
BilletRegulierSolde::BilletRegulierSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol, double pourcentageSolde)
	: BilletRegulier(pnr,prix,od,tarif,dateVol), Solde(pourcentageSolde)
{
}

/**
*	@brief getPrix To get the price of the ticket after discount
*	@return Double representing the price of the discounted ticket 
*/
double BilletRegulierSolde::getPrix() const
{
	return getPrixBase() * (1 - getPourcentageSolde());
}

/**
*	@brief getPrixBase To get the base price of the ticket
*	@return Double representing the base price of the ticket
*/
double BilletRegulierSolde::getPrixBase() const
{
	return BilletRegulier::getPrix(); // Billet ou Billet regulier ?
}

/**
*	@brief clone To create a dynamically allocated exact copy of this object
*	@param BilletRegulierSolde* pointer to the copy
*/
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

/**
*	@brief afficher To print out the current state of this object
*/
void BilletRegulierSolde::afficher(ostream& o) const
{
	BilletRegulier::afficher(o);
	o << "\t\t\t" << setw(11) << "- Pourcentage solde" << ": " << getPourcentageSolde() << "%" << endl;
}