#pragma once
/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef GESTIONNAIREMEMBRES_H
#define	GESTIONNAIREMEMBRES_H

#include <vector>

#include "membrePremium.h"
#include "solde.h"
#include "gestionnaireGenerique.h"
#include "foncteur.h"

class GestionnaireMembres: public GestionnaireGenerique<pair<string, Membre*>, map<string, Membre*>, AjouterMembre> {
public:

	void assignerBillet(Billet* billet, const string& nomMembre, int rabaisCoupon);
	/**
	 *	@brief calculerRevenu To calculate the revenue from the sale of tickets
	 *	@return double representing the revenu
	 */
	double calculerRevenu() const;
	/**
	 *	@brief calculerNombreBilletsEnSolde To apply a coupon when buying a ticket for a member
	 *	@param membre The member which posseses the coupons
	 *	@param prix The ticket's price which will be lowered by using a coupon
	 *	@return double representing the discounted price. Zero is returned if no coupon has been found
	 */
	int calculerNombreBilletsEnSolde() const;
	/**
	 *	@brief getBilletMin To get the ticket with the lowest price for a member
	 *	@param nonMembre String representing the name of the member which posseses the ticket
	 *	@return Billet* Pointer to the ticket with the lowest price
	 */
	Billet* getBilletMin(string nomMembre) const ;
	/**
	 *	@brief getBilletMax To get the ticket with the highest price for a member
	 *	@param nonMembre String representing the name of the member which posseses the ticket
	 *	@return Billet* Pointer to the ticket with the highest price
	 */
	Billet* getBilletMax(string nomMembre) const ;
	/**
	 *	@brief trouverBilletParIntervallle To get the tickets in a desired price range
	 *	@param membre Pointer to the member
	 *	@param prixInf Double representing the lowest price
	 *	@param prixInf Double representing the highest price 
	 *	@return vector<Billet*> vector containing the tickets in the desired price range
	 */
	vector<Billet*> trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const;

	void afficher(ostream& o) const;
};
#endif // !GESTIONNAIREMEMBRES_H



