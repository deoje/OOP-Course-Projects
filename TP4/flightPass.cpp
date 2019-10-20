/*
* Titre : flightPass.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/
#include "flightPass.h"

/**
*	@brief Constructor by parameters which initiate the state of the inherited classes
*/
FlightPass::FlightPass(const string& pnr, double prix, const string& od, TarifBillet tarif) : 
	Billet(pnr, prix, od, tarif), nbUtilisationsRestante_(NB_UTILISATIONS_INITIALE)
{
}

int FlightPass::getNbUtilisationsRestante() const
{
	return nbUtilisationsRestante_;
}

void FlightPass::decrementeNbUtilisations()
{
	--nbUtilisationsRestante_;
}

/**
*	@brief clone To return a dynamically allocated exact copy of this object
*	@return FlightPass* pointer to the copy
*/
FlightPass* FlightPass::clone() const
{
	FlightPass* flightPass = new FlightPass(
		getPnr(),
		getPrix(),
		getOd(),
		getTarif()
	);
	// decrement the number of uses left to the same number as this object
	for (int i = 0; i < nbUtilisationsRestante_; ++i) {
		flightPass->decrementeNbUtilisations();
	}

	return flightPass;
}

/**
*	@brief afficher To print out the state of the current object
*	@param Ostream reference
*/
void FlightPass::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Utilisation restantes" << ": " << nbUtilisationsRestante_ << endl;

}