#include "pch.h"
#include "billet.h"

/**
*@brief Billet default constructor. Initializes values to 0 or empty strings.
*/
Billet::Billet()
{
	pnr_ = "";
	nomPassager_ = "";
	prix_ = 0.0;
	od_ = "";
	tarif_ = TarifBillet::Economie;
	dateVol_ = "";
}

/**
*@brief Billet constructor by parameter.
*@param pnr Ticket reservation number (used as an ID).
*@param nomPassager Passenger name.
*@param prix Ticket price.
*@param od origin and destination.
*@param tarif Price reduction.
*@param dateVol Flight date.
*/
Billet::Billet(const string& pnr, const string& nomPassager,
			   double prix, const string& od, TarifBillet tarif,
			   const string& dateVol)
{
	pnr_ = pnr;
	nomPassager_ = nomPassager;
	prix_ = prix;
	od_ = od;
	tarif_ = tarif;
	dateVol_ = dateVol;
}

/**
*@brief Getter for attribute pnr.
*@return attribute pnr_.
*/
string Billet::getPnr()
{
	return pnr_;
}

/**
*@brief Getter for attribute nomPassager.
*@return attribute nomPassager_.
*/
string Billet::getNomPassager()
{
	return nomPassager_;
}

/**
*@brief Getter for attribute prix.
*@return attribute prix_.
*/
double Billet::getPrix()
{
	return prix_;
}

/**
*@brief Getter for attribute od.
*@return attribute od_.
*/
string Billet::getOd()
{
	return od_;
}

/**
*@brief Getter for attribute tarif.
*@return attribute tarif_.
*/
TarifBillet Billet::getTarif()
{
	return tarif_;
}

/**
*@brief Getter for attribute dateVol.
*@return attribute dateVol_.
*/
string Billet::getDateVol()
{
	return dateVol_;
}

/**
*@brief Setter for attribute pnr.
*@param pnr new reseration number.
*/
void Billet::setPnr(const string& pnr)
{
	pnr_ = pnr;
}

/**
*@brief Setter for attribute nomPassager.
*@param nomPassager new passenger name.
*/
void Billet::setNomPassager(const string& nomPassager)
{
	nomPassager_ = nomPassager;
}

/**
*@brief Setter for attribute prix.
*@param prix new price.
*/
void Billet::setPrix(double prix)
{
	prix_ = prix;
}

/**
*@brief Setter for attribute od.
*@param od new origin and destination.
*/
void Billet::setOd(const string& od)
{
	od_ = od;
}

/**
*@brief Setter for attribute tarif.
*@param tarif new price reduction.
*/
void Billet::setTarif(TarifBillet tarif)
{
	tarif_ = tarif;
}

/**
*@brief Setter for attribute dateVol.
*@param dateVol new flight date.
*/
void Billet::setDateVol(const string& dateVol)
{
	dateVol_ = dateVol;
}

/**
*@brief Format price reduction as a string instead of an enumeration.
*@param tarif Price reduction (as an enumeration).
*@return A character string for the price reduction.
*/
string Billet::formatTarif(TarifBillet tarif)
{
	switch (tarif) {
	case TarifBillet::Economie:
		return "Economie";
	case TarifBillet::PremiumEconomie:
		return "Premium economie";
	case TarifBillet::Affaire:
		return "Affaire";
	case TarifBillet::Premiere:
		return "Premiere";
	}
	return "Invalid formatTarif";
}

/**
*@brief Print all ticket attributes with an indentation.
*/
void Billet::afficherBillet()
{
	cout << "\t\t - Billet " << pnr_ << "(Classe : "
		<< formatTarif(tarif_) << endl;
	cout << "\t\t\t - Passager \t : " << nomPassager_;
	cout << "\t\t\t - Prix \t : " << prix_;
	cout << "\t\t\t - Trajet \t : " << od_;
	cout << "\t\t\t - Vol le \t : " << dateVol_;
}

// TODO: check if the destructor is really necessary.
Billet::~Billet()
{
}
