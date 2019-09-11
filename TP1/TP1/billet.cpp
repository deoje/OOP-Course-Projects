#include "pch.h"
#include "billet.h"


Billet::Billet()
{
	pnr_ = "";
	nomPassager_ = "";
	prix_ = 0.0;
	od_ = "";
	tarif_ = TarifBillet::Economie;
	dateVol_ = "";
}

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

string Billet::getPnr()
{
	return pnr_;
}
string Billet::getNomPassager()
{
	return nomPassager_;
}
double Billet::getPrix()
{
	return prix_;
}
string Billet::getOd()
{
	return od_;
}
TarifBillet Billet::getTarif()
{
	return tarif_;
}
string Billet::getDateVol()
{
	return dateVol_;
}

void Billet::setPnr(const string& pnr)
{
	pnr_ = pnr;
}
void Billet::setNomPassager(const string& nomPassager)
{
	nomPassager_ = nomPassager;
}
void Billet::setPrix(double prix)
{
	prix_ = prix;
}
void Billet::setOd(const string& od)
{
	od_ = od;
}
void Billet::setTarif(TarifBillet tarif)
{
	tarif_ = tarif;
}
void Billet::setDateVol(const string& dateVol)
{
	dateVol_ = dateVol;
}

string Billet::formatTarif(TarifBillet tarif)
{
	switch (tarif) {
	case TarifBillet::Economie:
		return "Economie";
	case TarifBillet::PremiumEconomie:
		return "PremiumEconomie";
	case TarifBillet::Affaire:
		return "Affaire";
	case TarifBillet::Premiere:
		return "Premiere";
	}
	return "Invalid formatTarif";
}

void Billet::afficherBillet()
{
	cout << "\t\t - Billet " << pnr_ << "(Classe : "
		<< formatTarif(tarif_) << endl;
	cout << "\t\t\t - Passager \t : " << nomPassager_;
	cout << "\t\t\t - Prix \t : " << prix_;
	cout << "\t\t\t - Trajet \t : " << od_;
	cout << "\t\t\t - Vol le \t : " << dateVol_;
}

Billet::~Billet()
{
}
