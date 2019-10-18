/*
* Titre : flightPassSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "flightPassSolde.h"


FlightPassSolde::FlightPassSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, double pourcentageSolde)
	: FlightPass(pnr,prix,od,tarif), Solde(pourcentageSolde)
{
}


double FlightPassSolde::getPrix() const
{
	return getPrixBase() * (1 - getPourcentageSolde());
}


double FlightPassSolde::getPrixBase() const
{
	return Billet::getPrix();
}

// TODO
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

// TODO
void FlightPassSolde::afficher(ostream& o) const
{
	FlightPass::afficher(o);
	o << "\t\t\t" << setw(11) << "- Pourcentage solde" << ": " << getPourcentageSolde() << "%" << endl;
}