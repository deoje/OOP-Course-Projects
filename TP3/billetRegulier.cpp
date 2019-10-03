#include "billetRegulier.h"

BilletRegulier::BilletRegulier(const string& pnr, const string& nomPassager,
	double prix, const string& od, TarifBillet tarif, const string& dateVol,
	TypeBillet typeBillet) :
	Billet(pnr, nomPassager, prix, od, tarif, typeBillet),
	dateVol_(dateVol)
{
}

string BilletRegulier::getDateVol() const {
	return dateVol_;
}

void BilletRegulier::setDateVol(string dateVol) {
	dateVol_ = dateVol;
}

ostream& operator<<(ostream& o, const BilletRegulier& billet) {
	o << billet << endl;
	o << "\t\t\t" << setw(11) << "- Vol le" << ": " << billet.dateVol_ << endl;

	return o;
}