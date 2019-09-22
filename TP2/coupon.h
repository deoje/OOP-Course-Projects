/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#ifndef COUPON_H
#define COUPON_H

#include <string>
#include <iostream>

using namespace std;

class Coupon {
public:
	// Constructeurs
	Coupon();
	Coupon(const string& code, double rabais, int cout);
	
	~Coupon();

	// Getters
	string getCode() const;
	double getRabais() const;
	int getCout() const;

	// Setters
	void setCode(const string& code);
	void setRabais(double rabais);
	void setCout(int cout);

	/**
	 * @brief operator> To compare the rabais_ field of each Coupon object
	 * @param c2 The coupon to compare the left operand with
	 */
	bool operator>(const Coupon& c2) const;
	/**
	 * @brief operator< To compare the rabais_ field of each Coupon object
	 * @param c2 The coupon to compare the left operand with
	 */
	bool operator<(const Coupon& c2) const;
	/**
	 * @brief operator>> To output the state of the Coupon object
	 * @param c2 The coupon to compare the left operand with
	 */
	friend ostream& operator<<(ostream& o, const Coupon& c);

private:
	string code_;
	double rabais_;
	int cout_;
};
#endif // !COUPON_H

