/*
* Titre : flightPass.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#ifndef FLIGHT_PASS_H
#define FLIGHT_PASS_H

#include <iomanip>

#include "billet.h"

class FlightPass : public Billet {
public:
	FlightPass(const string& pnr, double prix, const string& od, TarifBillet tarif);

	int getNbUtilisationsRestante() const;

	void decrementeNbUtilisations();

	FlightPass* clone() const override;

	//// TODO : Remplacer cette fonction par la methode afficher()
	//friend ostream& operator<<(ostream& o, const FlightPass& flightpass);

	void afficher(ostream& o) const override;
private:
	 int nbUtilisationsRestante_;
};
#endif // !FLIGHT_PASS_H