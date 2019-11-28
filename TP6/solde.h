/********************************************
* Titre: Travail pratique #6 - solde.h
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/

#ifndef SOLDE_H
#define SOLDE_H

using namespace std;

class Solde {
public:
	// Constructeurs
	Solde(double pourcentageSolde);
	virtual ~Solde();

	// Getter
	double getPourcentageSolde() const;
	virtual double getPrixBase() const = 0;

	// Setter
	void setPourcentageSolde(double pourcentageSolde);
protected:
	double pourcentageSolde_;
};
#endif // !SOLDE_H
