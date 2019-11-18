#pragma once
/********************************************
* Titre: Travail pratique #5 - gestionnaireCoupons.h
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#ifndef GESTIONNAIRECOUPONS_H
#define	GESTIONNAIRECOUPONS_H	

#include <vector>

#include "membrePremium.h"
#include "solde.h"
#include "gestionnaireGenerique.h"

class GestionnaireCoupons:
	public GestionnaireGenerique<Coupon*, vector<Coupon*>, AjouterCoupon> {
public:

	/**
	 *	@brief appliquerCoupon To apply a coupon when buying a ticket for a member
	 *	@param membre Pointer to the member which posseses the coupons
	 *	@param prix The ticket's price which will be lowered by using a coupon
	 *	@return double representing the discounted price. Zero is returned if no coupon has been found
	 */
	double appliquerCoupon(Membre* membre, double prix);
	/**
	 *	@brief acheterCoupon To buy a coupon for a member
	 *	@param membre Pointer to the member which receives the new coupons
	 */
	void acheterCoupon(Membre* membre);
};
#endif // !GESTIONNAIRECOUPONS_H



