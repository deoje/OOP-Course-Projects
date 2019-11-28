/********************************************
* Titre: Travail pratique #6 - mainwindow.cpp
* Date: 21 novembre 2019
* Auteur: Allan BEDDOUK
*******************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ExceptionArgumentInvalide.h"


#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <algorithm>


Q_DECLARE_METATYPE(Membre*)
Q_DECLARE_METATYPE(Billet*)
Q_DECLARE_METATYPE(Coupon*)

using namespace std;

MainWindow::MainWindow(vector<Coupon*> coupons, vector<Membre*> membres, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), coupons_(coupons), membres_(membres)
{
    ui->setupUi(this);
    setup();

}


MainWindow::~MainWindow()
{
    for(auto membre : membres_)
        delete membre;

    for (auto coupon: coupons_)
         delete coupon;

    delete ui;
}

void MainWindow::setup(){
   setMenu();
   setUI();
   chargerCoupons();
   chargerBillets();
   chargerMembres();
   nettoyerVue();
}

void MainWindow::afficherMessage(QString msg) {
    // TODO
}

void MainWindow::setMenu() {
    // TODO
}


void MainWindow::setUI(){

    //liste des billets
    QLabel* billetsLabel = new QLabel();
    billetsLabel->setText("Billets : ");
    listeBillets_ = new QListWidget(this);
    listeBillets_->setSortingEnabled(true);
// TODO

    // Boutons radios Type de billets
    boutonsRadioTypeBillets_.push_back(new QRadioButton("Regulier", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("Regulier Solde", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("FlightPass", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("FlightPass Solde", this));

    QHBoxLayout* boutonsRadioBilletsLayout = new QHBoxLayout();
    for(QRadioButton* bouton : boutonsRadioTypeBillets_)
        boutonsRadioBilletsLayout->addWidget(bouton);


    // Liste deroulante pour choisir le Membre
    choixMembreBillet_ = new QComboBox(this);
    choixMembreBillet_->addItem("Membres");
    ajouterMembresDansComboBox(choixMembreBillet_);

    //Champ pour le PNR
    editeurPNR_ = new QLineEdit();

    QHBoxLayout* pnrLayout = new QHBoxLayout();
    pnrLayout->addWidget(new QLabel("PNR : "));
    pnrLayout->addWidget(editeurPNR_);


    //Champ pour le prix
    editeurPrixBillet_ = new QLineEdit();
    editeurPrixBillet_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* prixBilletLayout = new QHBoxLayout();
    prixBilletLayout->addWidget(new QLabel("Prix : "));
    prixBilletLayout->addWidget(editeurPrixBillet_);


    //Champ pour l'Od
    editeurOD_ = new QLineEdit();

    QHBoxLayout* odBilletLayout = new QHBoxLayout();
    odBilletLayout->addWidget(new QLabel("Od : "));
    odBilletLayout->addWidget(editeurOD_);


    //Champ pour le Tarif du Billet
    choixTarifBillet_ = new QComboBox(this);
    choixTarifBillet_->addItem("Tarif Billet");
    choixTarifBillet_->addItem("Economie");
    choixTarifBillet_->addItem("Premium economie");
    choixTarifBillet_->addItem("Affaire");
    choixTarifBillet_->addItem("Premiere");

    //Champ pour la date de vol
    editeurDateVol_ = new QLineEdit();

    QHBoxLayout* dateVolLayout = new QHBoxLayout();
    dateVolLayout->addWidget(new QLabel("Date de Vol : "));
    dateVolLayout->addWidget(editeurDateVol_);


    //Champ pour le pourcentage solde du billet
    editeurPourcentageSoldeBillet_ = new QLineEdit();
    editeurPourcentageSoldeBillet_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* pourcentageSoldeBilletLayout = new QHBoxLayout();
    pourcentageSoldeBilletLayout->addWidget(new QLabel("Pourcentage Solde Billet : "));
    pourcentageSoldeBilletLayout->addWidget(editeurPourcentageSoldeBillet_);

    //Champ pour les jours restants
    editeurUtilisationsRestantesFlightPass_ = new QLineEdit();
    editeurUtilisationsRestantesFlightPass_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    editeurUtilisationsRestantesFlightPass_->setDisabled(true);

    QHBoxLayout* utilisationsRestantesLayout = new QHBoxLayout();
    utilisationsRestantesLayout->addWidget(new QLabel("Utilisations Restantes : "));
    utilisationsRestantesLayout->addWidget(editeurUtilisationsRestantesFlightPass_);


    //Bouton ajouter billet
// TODO


    //ligne seprant les ajouts de billets
    //et les ajouts de coupons
    QFrame* horizontaleFrameLine = new QFrame();
    horizontaleFrameLine->setFrameShape(QFrame::HLine);

    //liste des coupons
    QLabel* couponsLabel = new QLabel();
    couponsLabel->setText("Coupons : ");
    listeCoupons_ = new QListWidget(this);
    listeCoupons_->setSortingEnabled(true);
// TODO


    //Champ pour le code du coupon
    editeurCodeCoupon_ = new QLineEdit();

    QHBoxLayout* codeCouponLayout = new QHBoxLayout();
    codeCouponLayout->addWidget(new QLabel("Code : "));
    codeCouponLayout->addWidget(editeurCodeCoupon_);

    //Champ pour le rabais du coupon
    editeurRabaisCoupon_ = new QLineEdit();
    editeurRabaisCoupon_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* rabaisCouponLayout = new QHBoxLayout();
    rabaisCouponLayout->addWidget(new QLabel("Rabais : "));
    rabaisCouponLayout->addWidget(editeurRabaisCoupon_);

    //Champ pour le cout du coupon
    editeurCoutCoupon_ = new QLineEdit();
    editeurCoutCoupon_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* coutCouponLayout = new QHBoxLayout();
    coutCouponLayout->addWidget(new QLabel("Cout : "));
    coutCouponLayout->addWidget(editeurCoutCoupon_);


    //Bouton ajouter coupon
// TODO


    //ligne seprant les ajouts de coupons
    //et les informations des membres
    QFrame* horizontaleFrameLine2 = new QFrame();
    horizontaleFrameLine2->setFrameShape(QFrame::HLine);


    //selecteur pour les membres
    QComboBox* choixMembre = new QComboBox(this);
    choixMembre->addItem("Tout Afficher"); // Index 0
    choixMembre->addItem("Afficher Membres Reguliers"); // Index 1
    choixMembre->addItem("Afficher Membres Premium"); // Index 2
// TODO

    //liste des membres
    QLabel* membresLabel = new QLabel();
    membresLabel->setText("Membres : ");
    listeMembres_ = new QListWidget(this);
    listeMembres_->setSortingEnabled(true);
// TODO


    //Champ pour les points du Membres Regulier
    editeurPoints_ = new QLineEdit();
    editeurPoints_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* pointsMembreLayout = new QHBoxLayout();
    pointsMembreLayout->addWidget(new QLabel("Points : "));
    pointsMembreLayout->addWidget(editeurPoints_);


    //Champ pour les points cumules du Membres Regulier
    editeurPointsCumules_ = new QLineEdit();
    editeurPointsCumules_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    QHBoxLayout* pointsCumMembreLayout = new QHBoxLayout();
    pointsCumMembreLayout->addWidget(new QLabel("Points Cumules : "));
    pointsCumMembreLayout->addWidget(editeurPointsCumules_);

    //Champ pour les points cumules du Membres Regulier
    editeurJoursRestants_ = new QLineEdit();
    editeurJoursRestants_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    QHBoxLayout* joursRestantsLayout = new QHBoxLayout();
    joursRestantsLayout->addWidget(new QLabel("Jours Restants : "));
    joursRestantsLayout->addWidget(editeurJoursRestants_);



    //Layout de gauche
    QVBoxLayout* layoutHautGauche = new QVBoxLayout;

    layoutHautGauche->addWidget(billetsLabel);
    layoutHautGauche->addWidget(listeBillets_);

    layoutHautGauche->addWidget(couponsLabel);
    layoutHautGauche->addWidget(listeCoupons_);

    layoutHautGauche->addWidget(choixMembre);

    layoutHautGauche->addWidget(membresLabel);
    layoutHautGauche->addWidget(listeMembres_);

    //layout de droite
     QVBoxLayout* layoutHautDroite = new QVBoxLayout;
     layoutHautDroite->addWidget(choixMembreBillet_);
     layoutHautDroite->addLayout(boutonsRadioBilletsLayout);
     layoutHautDroite->addLayout(pnrLayout);
     layoutHautDroite->addLayout(prixBilletLayout);
     layoutHautDroite->addLayout(odBilletLayout);
     layoutHautDroite->addWidget(choixTarifBillet_);
     layoutHautDroite->addLayout(dateVolLayout);
     layoutHautDroite->addLayout(pourcentageSoldeBilletLayout);
     layoutHautDroite->addLayout(utilisationsRestantesLayout);
//TODO

     layoutHautDroite->addWidget(horizontaleFrameLine);

     layoutHautDroite->addLayout(codeCouponLayout);
     layoutHautDroite->addLayout(rabaisCouponLayout);
     layoutHautDroite->addLayout(coutCouponLayout);
//TODO

     layoutHautDroite->addWidget(horizontaleFrameLine2);

     layoutHautDroite->addLayout(pointsMembreLayout);
     layoutHautDroite->addLayout(pointsCumMembreLayout);
     layoutHautDroite->addLayout(joursRestantsLayout);


    //ligne verticale
    QFrame* verticalFrameLine = new QFrame;
    verticalFrameLine->setFrameShape(QFrame::VLine);

    //Layout du haut
    QHBoxLayout* layoutHaut = new QHBoxLayout;
    layoutHaut->addLayout(layoutHautGauche);
    layoutHaut->addWidget(verticalFrameLine);
    layoutHaut->addLayout(layoutHautDroite);

    //Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutHaut);

    QWidget* widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);

    string title = "Bienvenue sur PolyAir !" ;
    setWindowTitle(title.c_str());
}


void MainWindow::chargerBillets(){
    listeBillets_->clear();

    for(Membre* membre: membres_){
        for(Billet* billet: membre->getBillets())
        {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(billet->getPnr()), listeBillets_);
            item->setData(Qt::UserRole, QVariant::fromValue<Billet*>(billet));
        }
    }

}

void MainWindow::chargerCoupons(){
    listeCoupons_->clear();
    for (auto coupon: coupons_){

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(coupon->getCode()), listeCoupons_);
        item->setData(Qt::UserRole, QVariant::fromValue<Coupon*>(coupon));
    }

}

void MainWindow::chargerMembres(){
    listeMembres_->clear();
    for (auto membre: membres_){

        QListWidgetItem* item = new QListWidgetItem(
            QString::fromStdString(membre->getNom()) , listeMembres_);
        item->setData(Qt::UserRole, QVariant::fromValue<Membre*>(membre));
    }
}

void MainWindow::ajouterMembresDansComboBox(QComboBox* list){
    for(Membre* membre : membres_){
        list->addItem(QString::fromStdString(membre->getNom()));
    }
}

void MainWindow::nettoyerVue() {

    nettoyerVueBillets();
    nettoyerVueCoupons();
    nettoyerVueMembres();

    // Listes
    listeBillets_->clearSelection();
    listeCoupons_->clearSelection();
    listeMembres_->clearSelection();
    chargerBillets();
    chargerCoupons();
    chargerMembres();
}

void MainWindow::nettoyerVueBillets(){

}

void MainWindow::nettoyerVueCoupons(){

}

void MainWindow::nettoyerVueMembres(){

}

void MainWindow::selectionnerBillet(QListWidgetItem* item){
    // TODO
}
void MainWindow::selectionnerCoupon(QListWidgetItem* item ){
    // TODO

}
void MainWindow::selectionnerMembre(QListWidgetItem* item){
    // TODO
}
void MainWindow::ajouterBillet(){
    // TODO

}
void MainWindow::ajouterCoupon(){

    // TODO
}


void MainWindow::filtrerListe(int index){
    // TODO
}

bool MainWindow::filtrerMasque(Membre* membre, int index) {
    // TODO
    return false;
}

TarifBillet MainWindow::getTarifBillet(){
//TODO
    return TarifBillet::Affaire;
}



Membre* MainWindow::trouverMembreParNom(const string& nom){
   //TODO
    return nullptr;
}
