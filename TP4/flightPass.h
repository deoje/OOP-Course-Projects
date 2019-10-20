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
	// Constructor
	FlightPass(const string& pnr, double prix, const string& od, TarifBillet tarif);

	// Getter
	int getNbUtilisationsRestante() const;

	// Utils
	void decrementeNbUtilisations();
	/*
	   Overriding: FlightPass::clone() remplace Billet::clone() car aucun appel
	   à cette dernière.
	*/
	FlightPass* clone() const override;
	/*
	   Overriding: FlightPass::afficher() est une extension de Billet::clone() car la redéfinition
	   fait appel à cette dernière.
	*/
	void afficher(ostream& o) const override;
private:
	 int nbUtilisationsRestante_;
};
#endif // !FLIGHT_PASS_H