
/********************************************
* Titre: Travail pratique #6 - main.cpp
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/

#include "mainwindow.h"
#include <string>
#include <iostream>
#include <vector>
#include <QApplication>

#include "billetRegulierSolde.h"
#include "flightPassSolde.h"
#include "membrePremium.h"
#include "coupon.h"
#include "def.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Coupons
    vector<Coupon*> coupons;

    Coupon* c1 = new Coupon("20%", 0.2, 1700);
    coupons.push_back(c1);

    Coupon* c2 = new Coupon("10%", 0.1, 900);
    coupons.push_back(c2);

    Coupon* c3 = new Coupon("5%", 0.05, 500);
    coupons.push_back(c3);


    // Membres
    vector<Membre*> membres;

    MembreRegulier* robertRegulier = new MembreRegulier("Robert");
    robertRegulier->ajouterBillet(new BilletRegulier("B4Y6S1", 2000, "YUL - LGA", TarifBillet::Premiere, "2019-12-21"));
    robertRegulier->ajouterBillet(new FlightPass("GHJ6U2V", 50000, "YUL - CDG", TarifBillet::Premiere));
    membres.push_back(robertRegulier);

    MembreRegulier* johnRegulier = new MembreRegulier("John");
    johnRegulier->ajouterBillet(new BilletRegulier("A1A1A1", 3000, "YUL - CDG", TarifBillet::Premiere, "2019-12-21"));
    membres.push_back(johnRegulier);

    MembreRegulier* marcRegulier = new MembreRegulier("Marc");
    marcRegulier->ajouterBillet(new FlightPassSolde("HH6T3R", 25000, "YUL - LGA", TarifBillet::PremiumEconomie, 0.25));
    membres.push_back(marcRegulier);

    MembrePremium* alexPremium = new MembrePremium("Alex");
    alexPremium->ajouterBillet(new BilletRegulierSolde("O8I9P0", 2500, "YUL - LGA", TarifBillet::PremiumEconomie, "2019-12-21", 0.5));
    membres.push_back(alexPremium);




    QApplication a(argc, argv);
    MainWindow w(coupons, membres);
    w.show();
    return a.exec();
}
