/*
* Titre : flightPass.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/
#include "flightPass.h"

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


FlightPass* FlightPass::clone() const
{
	FlightPass* flightPass = new FlightPass(
		getPnr(),
		getPrix(),
		getOd(),
		getTarif()
	);

	for (int i = 0; i < nbUtilisationsRestante_; ++i) {
		flightPass->decrementeNbUtilisations();
	}

	return flightPass;
}

// TODO : Remplacer cette fonction par la methode afficher()
//ostream& operator<<(ostream& o, const FlightPass& flightpass)
//{
//	o << static_cast<Billet>(flightpass);
//	o << "\t\t\t" << setw(11) << "- Utilisation restantes" << ": " << flightpass.nbUtilisationsRestante_ << endl;
//
//	return;
//}


void FlightPass::afficher(ostream& o) const
{
	Billet::afficher(o);
	o << "\t\t\t" << setw(11) << "- Utilisation restantes" << ": " << nbUtilisationsRestante_ << endl;

}