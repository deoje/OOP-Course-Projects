/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "GestionnaireMembres.h"
#include <numeric>

void GestionnaireMembres::assignerBillet(Billet* billet, const string& nomMembre, int rabaisCoupon)
{
	Membre* membre = conteneur_[nomMembre];

	if (membre == nullptr) {
		delete billet;
		return;
	}

	double prix = billet->getPrix();

	if (auto solde = dynamic_cast<Solde*>(billet)) {
		prix = solde->getPrixBase();
	}

	
	prix -= rabaisCoupon;
	

	if (auto membrePremium = dynamic_cast<MembrePremium*>(membre)) {
		double rabais = 0.005 * membrePremium->getpointsCumulee() / 1000;
		if (rabais > 0.1)
			rabais = 0.1;

		prix *= (1 - rabais);
	}

	billet->setPrix(prix);
	membre->ajouterBillet(billet);
}



double GestionnaireMembres::calculerRevenu() const
{
	//TODO
	double revenu = 0;
	for (size_t i = 0; i < membres_.size(); ++i) {
		for (size_t j = 0; j < membres_[i]->getBillets().size(); ++j) {
			revenu += membres_[i]->getBillets()[j]->getPrix();
		}
	}

	return revenu;
}

int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{
	//TODO
	int nbBilletsSolde = 0;
	for (size_t i = 0; i < membres_.size(); ++i) {
		for (size_t j = 0; j < membres_[i]->getBillets().size(); ++j) {
			if (dynamic_cast<Solde*>(membres_[i]->getBillets()[j])) {
				++nbBilletsSolde;
			}
		}
	}

	return nbBilletsSolde;
}

void GestionnaireMembres::afficher(ostream& o) const
{
	//TODO
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for (size_t i =0 ; i<membres_.size() ; ++i) {
		membres[i]->afficher(o);
	}
}
