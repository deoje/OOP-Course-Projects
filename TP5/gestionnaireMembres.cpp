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
	// Initialize the variable holding the number of tickets in sale
	int nbBilletsSolde = 0;

	// Iterate through the vector of member
	for_each(conteneur_.begin(), conteneur_.end(), [&nbBilletsSolde](pair<string, Membre*> membre) {

		// Get the vector of pointers to the member's tickets
		vector<Billet*> billets = membre.second->getBillets();

		// Iterate through the vector of tickets
		for_each(billets.begin(), billets.end(), [&nbBilletsSolde](Billet* billet) {

			// If the ticket is in sale, increment the number of tickets in sale
			if (dynamic_cast<Solde*>(billet)) {
				++nbBilletsSolde;
			}
		});

	});
	return nbBilletsSolde;
}

Billet* GestionnaireMembres::getBilletMin(string nomMembre) const
{
	// Get an iterator pointing to the member
	map<string, Membre*>::const_iterator positionMembre = conteneur_.find(nomMembre);
	// Get the member's tickets
	vector<Billet*> billets = (*positionMembre).second->getBillets();
	// Get an iterator pointing to the ticket
	vector<Billet*>::const_iterator itBillet = min_element(billets.begin(), billets.end(),
		[](Billet* billet1, Billet* billet2) {

			// Find the ticket with the lowest price by comparing prices
			return billet1->getPrix() < billet2->getPrix();});

	// return the pointer to the ticket 
	return *itBillet;
}

Billet* GestionnaireMembres::getBilletMax(string nomMembre) const
{
	// Get an iterator pointing to the member
	map<string, Membre*>::const_iterator positionMembre = conteneur_.find(nomMembre);
	// Get the member's tickets
	vector<Billet*> billets = (*positionMembre).second->getBillets();
	// Get an iterator pointing to the ticket
	vector<Billet*>::const_iterator itBillet = min_element(billets.begin(), billets.end(),
		[](Billet* billet1, Billet* billet2) {

			// Find the ticket with the lowest price by comparing prices
			return billet1->getPrix() > billet2->getPrix();});

	// return the pointer to the ticket 
	return *itBillet;
}

vector<Billet*> GestionnaireMembres::trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const
{
	// Initialize the container which will hold the tickets in the desired price range
	vector<Billet*> billetsDansIntervalle;
	// Get the member's tickets
	vector<Billet*> billets = membre->getBillets();
	// Push back the tickets in the desired price range into billetsDansIntervalle
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
