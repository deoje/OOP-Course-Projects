/********************************************
* Titre: Travail pratique #6 - flightPass.h
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/

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

	void afficher(ostream& o) const override;
private:
	 int nbUtilisationsRestante_;
};
#endif // !FLIGHT_PASS_H
