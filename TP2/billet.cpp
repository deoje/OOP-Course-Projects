/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "billet.h"

Billet::Billet() :
	pnr_(""),
	nomPassager_(""),
	prix_(0),
	od_(""),
	tarif_(TarifBillet::Economie),
	dateVol_("")
{
}

Billet::Billet(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol) :
	pnr_(pnr),
	nomPassager_(nomPassager),
	prix_(prix),
	od_(od),
	tarif_(tarif),
	dateVol_(dateVol)
{
}

Billet::~Billet()
{
}

string Billet::getPnr() const
{
	return pnr_;
}

string Billet::getNomPassager() const
{
	return nomPassager_;
}

double Billet::getPrix() const
{
	return prix_;
}

string Billet::getOd() const
{
	return od_;
}

TarifBillet Billet::getTarif() const
{
	return tarif_;
}

string Billet::getDateVol() const
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

string Billet::formatTarif(TarifBillet tarif) const
{
	switch (tarif)
	{
		case TarifBillet::Economie:
			return "Economie";
		case TarifBillet::PremiumEconomie:
			return "Premium economie";
		case TarifBillet::Affaire:
			return "Affaire";
		case TarifBillet::Premiere:
			return "Premiere";
		default:
			return "";
	}
}

ostream& operator<< (ostream& os, const Billet& billet)
{
	os << "\t\t- Billet " << billet.getPnr() << " (Classe : " << billet.formatTarif(billet.getTarif()) << ")" << endl;
	os << left << "\t\t\t" << setw(11) << "- Passager " << ": " << billet.getNomPassager() << endl;
	os << "\t\t\t" << setw(11) << "- Prix" << ": " << billet.getPrix() << "$" << endl;
	os << "\t\t\t" << setw(11) << "- Trajet" << ": " << billet.getOd() << endl;
	os << "\t\t\t" << setw(11) << "- Vol le" << ": " << billet.getDateVol() << endl;
}
