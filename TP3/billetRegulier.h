/*
* Titre : billetRegulier.h - Travail Pratique #3
* Date : 20 Septembre 2019
* Auteur : Jeffrey Lavallee
*/

#ifndef BILLET_REGULIER_H
#define BILLET_REGULIER_H
#include "billet.h"

class BilletRegulier : public Billet {

public:
	// Constructor by parameter
	BilletRegulier(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol, TypeBillet typeBillet);

	// Getter & Setter
	string getDateVol() const;
	void setDateVol(string dateVol);

	// Overloading << operator
	friend ostream& operator<<(ostream& o, const BilletRegulier& billetRegulier);
private:
	/**
	* @ brief dateVol_ String containing the date of flight
	*/
	string dateVol_;
};

#endif