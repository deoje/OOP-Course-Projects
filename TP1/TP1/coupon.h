/*
 * Date : 1 Septembre 2019
 * Auteur : Wassim Khene
 */

#ifndef COUPON_H
#define COUPON_H

#include <string>
#include <iostream>

using namespace std;

class Coupon {
public:
	// Constructors
	Coupon();
	Coupon(const string& code, double rabais, int cout);

	// Destructors
	~Coupon() = default;

	// Getters
	string getCode() const;
	double getRabais() const;
	int getCout() const;

	// Setters
	void setCode(const string& code);
	void setRabais(double rabais);
	void setCout(int cout);

	// Printing methods
	void afficherCoupon() const;
private:
	/**
	* @brief code_ the name of the coupon
	*/
	string code_;
	/**
	* @brief rabais_ the deduction offered by the coupon
	* represented as a number between 0 and 1
	*/
	double rabais_;
	/**
	* @brief cout_ the price of the coupon in points
	*/
	int cout_;
};

#endif // !COUPON_H