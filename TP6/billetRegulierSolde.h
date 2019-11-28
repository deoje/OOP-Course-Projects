/********************************************
* Titre: Travail pratique #6 - billetRegulierSolde.h
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/

#ifndef BILLET_REGULIER_SOLDE_H
#define BILLET_REGULIER_SOLDE_H

#include <iomanip>

#include "billetRegulier.h"
#include "solde.h"

using namespace std;

class BilletRegulierSolde : public BilletRegulier, public Solde {
public:
	// Constructeur
	BilletRegulierSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol, double pourcentageSolde);

	// Getter
	double getPrix() const override;
	double getPrixBase() const override;

	BilletRegulierSolde* clone() const override;

	void afficher(ostream& o) const override;
};
#endif // !BILLET_REGULIER_SOLDE_H
