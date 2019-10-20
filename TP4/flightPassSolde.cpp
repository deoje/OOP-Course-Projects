/*
* Titre : flightPassSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "flightPassSolde.h"

/**
*	@brief Constructor with parameters which also intiate the state of the
*	inherited classes
*/
FlightPassSolde::FlightPassSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, double pourcentageSolde)
	: FlightPass(pnr,prix,od,tarif), Solde(pourcentageSolde)
{
}

/**
*	@brief getPrix To get the price of the ticket after discount
*	@return Double representing the price of the discounted ticket
*/
double FlightPassSolde::getPrix() const
{
	return getPrixBase() * (1 - getPourcentageSolde());
}

/**
*	@brief getPrixBase To get the base price of the ticket
*	@return Double representing the base price of the ticket
*/
double FlightPassSolde::getPrixBase() const
{
	return Billet::getPrix();
}

/**
*	@brief clone To create a dynamically allocated exact copy of this object
*	@param FlightPassSolde* pointer to the copy
*/
FlightPassSolde* FlightPassSolde::clone() const
{
	// Create new object
	FlightPassSolde* flightPassSolde = new FlightPassSolde(
		getPnr(),
		getPrix(),
		getOd(),
		getTarif(),
		getPourcentageSolde()
	);

	// To get the exact state, we need to get the same number of tickets left
	for (int i = 0; i < getNbUtilisationsRestante(); ++i) {
		flightPassSolde->decrementeNbUtilisations();
	}

	// Return the pointer to the new object
	return flightPassSolde;
}

/**
*	@brief afficher To print out the current state of this object
*/
void FlightPassSolde::afficher(ostream& o) const
{
	FlightPass::afficher(o);
	o << "\t\t\t" << setw(11) << "- Pourcentage solde" << ": " << getPourcentageSolde() << "%" << endl;
}