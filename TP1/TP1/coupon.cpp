#include <iostream>
#include <string>
#include <iomanip>

//#include "pch.h"
#include "coupon.h"

using namespace std;

Coupon::Coupon()
{
	code_ = "";
	rabais_ = 0.0;
	cout_ = 100;
}

Coupon::Coupon(const string& code, double rabais, int cout)
{
	code_ = code;
	rabais_ = rabais;
	cout_ = cout;
}

string Coupon::getCode() const
{
	return code_;
}

double Coupon::getRabais() const
{
	return rabais_;
}

int Coupon::getCout() const
{
	return cout_;
}

void Coupon::setCode(const string& code)
{
	code_ = code;
}

void Coupon::setRabais(double rabais)
{
	rabais_ = rabais;
}

void Coupon::setCout(int cout)
{
	cout_ = cout;
}

void Coupon::afficherCoupon()const
{
	cout << "- Coupon " + code_ + ". "
		<< "Rabais" << " : " << rabais_ << "."
		<< endl;

}