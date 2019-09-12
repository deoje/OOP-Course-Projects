/*
 * Date : 1 Septembre 2019
 * Auteur : Wassim Khene
 */

#ifndef BILLET_H
#define BILLET_H

#include <string>
#include <iostream>
#include <iomanip>
#include "def.h"

using namespace std;

class Billet {
public:
	// Constructor
	Billet();
	Billet(const string& pnr, const string& nomPassager, double prix,
		const string& od, TarifBillet tarif, const string& dateVol);

	// Destructor
	~Billet();

	// Getters
	string getPnr() const;
	string getNomPassager() const;
	double getPrix() const;
	string getOd() const;
	TarifBillet getTarif() const;
	string getDateVol() const;

	// Setters
	void setPnr(const string& pnr);
	void setNomPassager(const string& nomPassager);
	void setPrix(double prix);
	void setOd(const string& od);
	void setTarif(TarifBillet tarif);
	void setDateVol(const string& dateVol);

	// Printing methods
	string formatTarif(TarifBillet tarif) const;
	void afficherBillet() const;

private:
	// Attributes
	/**
	 * @brief pnr_ Identifier for the ticket.
	 */
	string pnr_;
	/**
	 * @brief nomPassager_ Passenger name.
	 */
	string nomPassager_;
	/**
	 * @brief prix_ Ticket price.
	 */
	double prix_;
	/**
	 * @brief od_ Origin and destination for the ticket.
	 */
	string od_;
	/**
	 * @brief tarif_ Type of ticket.
	 */
	TarifBillet tarif_;
	/**
	 * @brief dateVol Flight date.
	 */
	string dateVol_;
};
#endif // !BILLET_H