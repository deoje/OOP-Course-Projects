/*
* Titre : billetRegulierSolde.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe C�T�-MORNEAULT
*/

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
	/*
	   Overriding: BilletRegulierSolde::getPrix() est une extension de Billet::getPrix() car la red�finition
	   fait appel � cette derni�re.
	*/
	double getPrix() const override;
	/*
	   Overriding: BilletRegulierSolde::getPrixBase() remplace Solde::getPrixBase() car aucun appel
	   � cette derni�re.
	*/
	double getPrixBase() const override;

	// Utils
	/*
	   Overriding: BilletRegulierSolde::clone() remplace BilletRegulier::clone() car aucun appel
	   � cette derni�re.
	*/
	BilletRegulierSolde* clone() const override;
	/*
	   Overriding: BilletRegulierSolde::afficher() est une extension de BilletRegulier::clone() car la red�finition
	   fait appel � cette derni�re.
	*/
	void afficher(ostream& o) const override;
};
#endif // !BILLET_REGULIER_SOLDE_H