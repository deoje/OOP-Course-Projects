/*
* Titre : solde.h - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe C�T�-MORNEAULT
*/

#ifndef SOLDE_H
#define SOLDE_H

using namespace std;

class Solde {// la classe est abstraite ==> poss�de au moins une fonction membre virtuelle pure.
public:
	// Constructeurs
	Solde(double pourcentageSolde);
	virtual ~Solde();

	// Getter
	double getPourcentageSolde() const;
	virtual double getPrixBase() const  = 0; // fonction membre virtuelle pure

	// Setter
	void setPourcentageSolde(double pourcentageSolde);
protected:
	double pourcentageSolde_;
};
#endif // !SOLDE_H