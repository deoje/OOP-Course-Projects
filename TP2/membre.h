/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#ifndef MEMBRE_H
#define MEMBRE_H

#include <string>
#include <vector>

#include "billet.h"
#include "coupon.h"

using namespace std;

class Membre {
public:
	// Constructeurs
	Membre();
	Membre(const string& nom);
	// TODO: Ajouter un constructeur par copie si necessaire
	Membre(const Membre& m2);

	~Membre();

	// Getters
	string getNom() const;
	int getPoints() const;
	vector<Billet*> getBillets() const;
	vector<Coupon*> getCoupons() const;
	int getNbBillets() const;
	int getNbCoupons() const;

	// Setters
	void setNom(const string& nom);
	void modifierPoints(int points);
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol);
	void acheterCoupon(Coupon* coupon);
	double calculerPoints(Billet* billet) const;

	// TODO: Remplacer cette methode par l'operateur +=
	Membre& operator+=(Coupon* c);
	// TODO: Remplacer cette methode par l'operateur -=
	Membre& operator-=(Coupon* c);

	// TODO: Surcharger l'operateur == (operande de gauche est un membre et droite est un string)
	bool operator==(const string& s) const;
	// TODO: Surcharger l'operateur == (operande de gauche est un string et droite est un membre)
	friend bool operator==(const string& s, const Membre& m);
	// TODO: Surcharger l'operateur =
	Membre& operator=(const Membre& m2);


	// TODO: Remplacer cette methode par l'operateur <<
	friend ostream& operator<<(ostream& o, const Membre& m);
private:
	string nom_;
	int points_;
	// TODO: Convertir billets_ en vecteur
	vector<Billet*> billets_;
	// TODO: Convertir coupons_ en vecteur
	vector<Coupon*> coupons_;
};
#endif // !MEMBRE_H
