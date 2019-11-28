/********************************************
* Titre: Travail pratique #6 - solde.cpp
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/

#include "solde.h"

Solde::Solde(double pourcentageSolde)
{
	pourcentageSolde_ = pourcentageSolde;
}

Solde::~Solde()
{
}

double Solde::getPourcentageSolde() const
{
	return pourcentageSolde_;
}

void Solde::setPourcentageSolde(double pourcentageSolde)
{
	pourcentageSolde_ = pourcentageSolde;
}
