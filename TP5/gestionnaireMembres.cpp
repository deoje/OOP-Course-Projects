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
	double revenu = 0;
	for_each(conteneur_.begin(), conteneur_.end(), [&revenu](pair<string, Membre*> membre){
		vector<Billet*> billets = membre.second->getBillets();
		for_each(billets.begin(), billets.end(), [&revenu](Billet* billet) {
			revenu += billet->getPrix();
		});
	});
	return revenu;
}

int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{
	int nbBilletsSolde = 0;
	for_each(conteneur_.begin(), conteneur_.end(), [&nbBilletsSolde](pair<string, Membre*> membre) {
		vector<Billet*> billets = membre.second->getBillets();
		for_each(billets.begin(), billets.end(), [&nbBilletsSolde](Billet* billet) {
			if (dynamic_cast<Solde*>(billet)) {
				++nbBilletsSolde;
			}
		});
	});
	return nbBilletsSolde;
}

Billet* GestionnaireMembres::getBilletMin(string nomMembre) const
{
	map<string, Membre*>::const_iterator positionMembre = conteneur_.find(nomMembre);
	vector<Billet*> billets = (*positionMembre).second->getBillets();
	vector<Billet*>::const_iterator itBillet = min_element(billets.begin(), billets.end(),
		[](Billet* billet1, Billet* billet2) {
			return billet1->getPrix() < billet2->getPrix();});
	return *itBillet;
}

Billet* GestionnaireMembres::getBilletMax(string nomMembre) const
{
	map<string, Membre*>::const_iterator positionMembre = conteneur_.find(nomMembre);
	vector<Billet*> billets = (*positionMembre).second->getBillets();
	vector<Billet*>::const_iterator itBillet = min_element(billets.begin(), billets.end(),
		[](Billet* billet1, Billet* billet2) {
			return billet1->getPrix() > billet2->getPrix();});
	return *itBillet;
}

vector<Billet*> GestionnaireMembres::trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const
{
	vector<Billet*> billetsDansIntervalle;
	vector<Billet*> billets = membre->getBillets();
	copy_if(billets.begin(), billets.end(), back_inserter(billetsDansIntervalle), IntervallePrixBillet(pair<double, double>(prixInf, prixSup)));
	
	return billetsDansIntervalle;
}

void GestionnaireMembres::afficher(ostream& o) const
{
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";
	for_each(conteneur_.begin(), conteneur_.end(), [&o](pair<string, Membre*> membre) {
		membre.second->afficher(o);
	});
}
