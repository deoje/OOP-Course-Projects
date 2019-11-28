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
    QLabel* msgToShow = new QLabel(msg.toStdString().c_str());
    msgToShow->show();
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
    connect(listeBillets_, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(selectionnerBillet(QListWidgetItem*)));

    // Boutons radios Type de billets
    boutonsRadioTypeBillets_.push_back(new QRadioButton("Regulier", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("Regulier Solde", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("FlightPass", this));
    boutonsRadioTypeBillets_.push_back(new QRadioButton("FlightPass Solde", this));

    QButtonGroup* billetTypeButtonGroup = new QButtonGroup;
    for (QRadioButton* bouton : boutonsRadioTypeBillets_)
        billetTypeButtonGroup->addButton(bouton);
    connect(billetTypeButtonGroup, SIGNAL(buttonClicked(int)),
        this, SLOT(changedType(int)));

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
    QPushButton * addBilletButton = new QPushButton(this);
    addBilletButton->setText("Ajouter Billet");
    connect(addBilletButton, SIGNAL(clicked()),
            this, SLOT(ajouterBillet()));

    //ligne seprant les ajouts de billets
    //et les ajouts de coupons
    QFrame* horizontaleFrameLine = new QFrame();
    horizontaleFrameLine->setFrameShape(QFrame::HLine);

    //liste des coupons
    QLabel* couponsLabel = new QLabel();
    couponsLabel->setText("Coupons : ");
    listeCoupons_ = new QListWidget(this);
    listeCoupons_->setSortingEnabled(true);
    connect(listeCoupons_, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(selectionnerCoupon(QListWidgetItem*)));


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
    QPushButton * addCouponButton = new QPushButton(this);
    addCouponButton->setText("Ajouter Coupon");
    connect(addCouponButton, SIGNAL(clicked()), this, SLOT(ajouterCoupon()));

    //ligne seprant les ajouts de coupons
    //et les informations des membres
    QFrame* horizontaleFrameLine2 = new QFrame();
    horizontaleFrameLine2->setFrameShape(QFrame::HLine);


    //selecteur pour les membres
    QComboBox* choixMembre = new QComboBox(this);
    choixMembre->addItem("Tout Afficher"); // Index 0
    choixMembre->addItem("Afficher Membres Reguliers"); // Index 1
    choixMembre->addItem("Afficher Membres Premium"); // Index 2
    connect(choixMembre, SIGNAL(currentIndexChanged(int)),
            this, SLOT(filtrerListe(int)));

    //liste des membres
    QLabel* membresLabel = new QLabel();
    membresLabel->setText("Membres : ");
    listeMembres_ = new QListWidget(this);
    listeMembres_->setSortingEnabled(true);
    connect(listeMembres_, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(selectionnerMembre(QListWidgetItem*)));
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
    // Fetch the actual billet data
    Billet * billet = item->data(Qt::UserRole).value<Billet*>();

    // Disable modifications
    editeurDateVol_->setDisabled(true);
    editeurPourcentageSoldeBillet_->setDisabled(true);
    editeurUtilisationsRestantesFlightPass_->setDisabled(true);

    // Verify if it's a regular ticket
    BilletRegulier * billetRegulier = dynamic_cast<BilletRegulier*>(billet);
    if (billetRegulier){

        editeurDateVol_->setText(
            QString::fromStdString(billetRegulier->getDateVol())
        );

        BilletRegulierSolde * billetRegulierSolde = dynamic_cast<BilletRegulierSolde*>(billetRegulier);

        // Verify if it's in sale
        if (billetRegulierSolde)
        {
            editeurPourcentageSoldeBillet_->setText(
                QString::number(billetRegulierSolde->getPourcentageSolde()));
            editeurUtilisationsRestantesFlightPass_->setText(QString("N/A"));
            return;

        } else {

            editeurPourcentageSoldeBillet_->setText(QString("N/A"));
            editeurUtilisationsRestantesFlightPass_->setText(QString("N/A"));
            return;
        }
    }

    // Verify if it's a flightPass
    FlightPass * flightPass = dynamic_cast<FlightPass*>(billet);
    if (flightPass){
        editeurDateVol_->setText(QString("N/A"));
        editeurUtilisationsRestantesFlightPass_->setText(QString::number(flightPass->getNbUtilisationsRestante()));

        FlightPassSolde * flightPassSolde = dynamic_cast<FlightPassSolde*>(flightPass);
        // Verify if it's in sale
        if (flightPassSolde){
            editeurPourcentageSoldeBillet_->setText(
                QString::number(flightPassSolde->getPourcentageSolde()));
            return;
            }
        editeurPourcentageSoldeBillet_->setText(QString("N/A"));
        return;
    } else {
        editeurDateVol_->setText(QString("N/A"));
        editeurPourcentageSoldeBillet_->setText(QString("N/A"));
        editeurUtilisationsRestantesFlightPass_->setText(QString("N/A"));
    }
}

void MainWindow::selectionnerCoupon(QListWidgetItem* item ){
    // Fetch the actual coupon data
    Coupon* coupon = item->data(Qt::UserRole).value<Coupon*>();

    // Disable modifications to coupon's code and show its value
    editeurCodeCoupon_->setDisabled(true);
    editeurCodeCoupon_->setText(QString::fromStdString(coupon->getCode()));

    // Disable modifications to coupon's rabais and show its value
    editeurRabaisCoupon_->setDisabled(true);
    editeurRabaisCoupon_->setText(QString::number(coupon->getRabais()));

    // Disable modifications to coupon's cout and show its value
    editeurCoutCoupon_->setDisabled(true);
    editeurCoutCoupon_->setText(QString::number(coupon->getCout()));
}

void MainWindow::selectionnerMembre(QListWidgetItem* item){
    // Fetch the the member from the data
    Membre * membre = item->data(Qt::UserRole).value<Membre*>();

    // Disable modifications to member's data
    editeurPoints_->setDisabled(true);
    editeurPointsCumules_->setDisabled(true);
    editeurJoursRestants_->setDisabled(true);

    // Verify if regular member
    MembreRegulier * membreRegulier = dynamic_cast<MembreRegulier*>(membre);
    if (membreRegulier){

        editeurPoints_->setText(QString::number(membreRegulier->getPoints()));

        // Verify if premium member
        MembrePremium * membrePremium = dynamic_cast<MembrePremium*>(membreRegulier);
        if (membrePremium){
            editeurPointsCumules_->setText(QString::number(membrePremium->getpointsCumulee()));
            editeurJoursRestants_->setText(QString::number(membrePremium->getpointsCumulee()));
            return;
        }

        editeurPointsCumules_->setText(QString("N/A"));
        editeurJoursRestants_->setText(QString("N/A"));
        return;

    } else {
        editeurPoints_->setText(QString("N/A"));
        editeurPointsCumules_->setText(QString("N/A"));
        editeurJoursRestants_->setText(QString("N/A"));
        return;
    }
}
void MainWindow::ajouterBillet(){
    // TODO

}
void MainWindow::ajouterCoupon(){

    // TODO
}


void MainWindow::filtrerListe(int index){
    // Iterate through all the members
    for (int i = 0; i < listeMembres_->count(); ++i){

        // store the item i
        QListWidgetItem *item = listeMembres_->item(i);

        // fetch the actual member pointer from the item
        Membre* member = item->data(Qt::UserRole).value<Membre*>();

        // Hide the member if the index corresponds to its type
        item->setHidden(filtrerMasque(member, index));
    }
}

bool MainWindow::filtrerMasque(Membre* membre, int index) {

    switch (index){
        case 2 : // Verify if member is actually premium
            if (dynamic_cast<MembrePremium*>(membre))
                return true;
            break;
        case 1 : // Verify if member is actually regular
            if (dynamic_cast<MembreRegulier*>(membre))
                return true;
            break;
        case 0 : // Return true since a member was passed as a parameter
            return true;
        default: // Covers cases where the type does not match the index and index is not 0, 1 or 2.
            return false;
    }
}

TarifBillet MainWindow::getTarifBillet(){
//TODO
    return TarifBillet::Affaire;
}



Membre* MainWindow::trouverMembreParNom(const string& nom){
    auto it = std::find_if(membres_.begin(), membres_.end(),
        [&nom](Membre* ptrMembre) -> bool {return ptrMembre->getNom() == nom;});
    return *it;
}
