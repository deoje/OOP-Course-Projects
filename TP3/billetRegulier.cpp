#include "billetRegulier.h"

BilletRegulier::BilletRegulier(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol, TypeBillet typeBillet)
	: Billet(pnr,nomPassager,prix, od, tarif, typeBillet),
	  dateVol_(dateVol)
{
}

string BilletRegulier::getDateVol() const
{
	/**
	* @brief getdateVol To get the date of flight
	* @return String reprensenting the date of the flight
	*/
	return dateVol_;
}

void BilletRegulier::setDateVol(string dateVol)
{
	/**
	* @brief setDateVol To set the date of the flight
	* @param dateVol String representing the date of the flight
	*/
	dateVol_ = dateVol_;
}

ostream& operator<<(ostream& o, const BilletRegulier& billet)
{	
	// Implicit upcasting i.e. BilletRegulier --> Billet
	Billet tempBillet = billet;

	o << tempBillet << endl;

	return o;
}
