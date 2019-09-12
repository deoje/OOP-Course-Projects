#include <iostream>
#include <iomanip>
#include "coupon.h"

Coupon::Coupon()
	: code_(""),rabais_(0.0),cout_(100)
{
	/**
	* @brief Coupon Default constructor of the class
	*/
}

Coupon::Coupon(const string& code, double rabais, int cout)
	:code_(code), rabais_(rabais), cout_(cout)
{
	/**
	* @brief Coupon Constructor with parameters receiving its code, rabais and
	*        cout
	* @param code The code representing the name
	* @param rabais The deduction offered by the coupon
	* @param cout its price in points
	*/
}

string Coupon::getCode() const
{
	/**
	* @brief getCode to know the name of the coupon
	* @return string representing the name of the coupon
	*/
	return code_;
}

double Coupon::getRabais() const
{
	/**
	* @brief getRabais to know the name of the coupon
	* @return double representing the deduction offered by the coupon (between
	* 0 and 1)
	*/
	return rabais_;
}

int Coupon::getCout() const
{
	/**
	* @brief getCout to know the prince in points of the coupon
	* @return int representing the price in points of the coupon
	*/
	return cout_;
}

void Coupon::setCode(const string& code)
{
	/**
	* @brief setCode to change the name of the coupon
	*/
	code_ = code;
}

void Coupon::setRabais(double rabais)
{
	/**
	* @brief setRabais to change the deduction offered by the coupon (between
	* 0 and 1)
	*/
	rabais_ = rabais;
}

void Coupon::setCout(int cout)
{
	/**
	* @brief setCout to change the price in points of the coupon
	*/
	cout_ = cout;
}

void Coupon::afficherCoupon()const
{
	/**
	* @brief print the code and deduction of a coupon
	*/
	cout << "\t\t - Coupon " + code_ + ". "
		<< "Rabais" << " : " << rabais_ << "."
		<< endl;

}