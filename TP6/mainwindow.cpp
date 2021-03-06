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
#include <QButtonGroup>
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

/*
*   @brief afficherMessage To display a message in a separate window
*   @param msg QString representing the message to display
*/
void MainWindow::afficherMessage(QString msg) {
    QMessageBox msgToShow;
    msgToShow.setText(msg.toStdString().c_str());
    msgToShow.exec();
}

void MainWindow::setMenu() {
    QAction* exit = new QAction(tr("&Quitter"), this);
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    QAction* nettoyer_vue = new QAction(tr("&Nettoyer vue"), this);
    connect(nettoyer_vue, SIGNAL(triggered()), this, SLOT(nettoyerVue()));
    QMenu* fileMenu = menuBar()->addMenu(tr("&Fichier"));
    fileMenu->addAction(exit);
    fileMenu->addAction(nettoyer_vue);
}


void MainWindow::setUI(){

    //liste des billets
    QLabel* billetsLabel = new QLabel();
    billetsLabel->setText("Billets : ");
    listeBillets_ = new QListWidget(this);
    listeBillets_->setSortingEnabled(true);
    // Link the action of clicking an item in the ticket's list box
    // to the actual function that handles what to show after the selection
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
    // Link the action of selecting a type in the ticket's type radio buttons
    // to the actual function that handles which field can actually me modified
    connect(billetTypeButtonGroup, SIGNAL(buttonClicked(int)),
        this, SLOT(selectionnerTypeBillet(int)));

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
    addBilletButton_ = new QPushButton(this);
    addBilletButton_->setText("Ajouter Billet");
    // Link the action of clicking on "Ajouter Billet"
    // to the actual function that handles the addition of the new ticket
    connect(addBilletButton_, SIGNAL(clicked()),
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
    addCouponButton_ = new QPushButton(this);
    addCouponButton_->setText("Ajouter Coupon");
    // Link the action of clicking on "Ajouter Coupon"
    // to the actual function that handles the addition of the new coupon
    connect(addCouponButton_, SIGNAL(clicked()), this, SLOT(ajouterCoupon()));

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

    //Champ pour les points du Membres Regulier
    editeurPoints_ = new QLineEdit();
    editeurPoints_->setValidator(new QDoubleValidator(0, 10000, 2, this));

    QHBoxLayout* pointsMembreLayout = new QHBoxLayout();
    pointsMembreLayout->addWidget(new QLabel("Points : "));
    pointsMembreLayout->addWidget(editeurPoints_);
    editeurPoints_->setDisabled(true);
    editeurPoints_->setText("N/A");


    //Champ pour les points cumules du Membres Regulier
    editeurPointsCumules_ = new QLineEdit();
    editeurPointsCumules_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    QHBoxLayout* pointsCumMembreLayout = new QHBoxLayout();
    pointsCumMembreLayout->addWidget(new QLabel("Points Cumules : "));
    pointsCumMembreLayout->addWidget(editeurPointsCumules_);
    editeurPointsCumules_->setDisabled(true);
    editeurPointsCumules_->setText("N/A");


    //Champ pour les points cumules du Membres Regulier
    editeurJoursRestants_ = new QLineEdit();
    editeurJoursRestants_->setValidator(new QDoubleValidator(0, 10000, 2, this));
    QHBoxLayout* joursRestantsLayout = new QHBoxLayout();
    joursRestantsLayout->addWidget(new QLabel("Jours Restants : "));
    joursRestantsLayout->addWidget(editeurJoursRestants_);
    editeurJoursRestants_->setDisabled(true);
    editeurJoursRestants_->setText("N/A");



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

     layoutHautDroite->addWidget(addBilletButton_);

     layoutHautDroite->addWidget(horizontaleFrameLine);

     layoutHautDroite->addLayout(codeCouponLayout);
     layoutHautDroite->addLayout(rabaisCouponLayout);
     layoutHautDroite->addLayout(coutCouponLayout);

     layoutHautDroite->addWidget(addCouponButton_);

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

    // Clean individual sections
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

    // Remove tickets to reload them later
    listeBillets_->clearSelection();
    // Allow selection of a ticket
    listeBillets_->setDisabled(false);

    // Allow selection of a member which will receive the new ticket
    choixMembreBillet_->setDisabled(false);
    // Revert to the invalid "Membres" option
    choixMembreBillet_->setCurrentIndex(0);

    // Select the first radio button by default
    boutonsRadioTypeBillets_[0]->setChecked(true);

    for(QRadioButton * button : boutonsRadioTypeBillets_){
        button->setDisabled(false);
    }

    // Allow modification to fields and empty them
    editeurPNR_->setDisabled(false);
    editeurPNR_->setText("");
    editeurPrixBillet_->setDisabled(false);
    editeurPrixBillet_->setText("");
    editeurOD_->setDisabled(false);
    editeurOD_->setText("");
    choixTarifBillet_->setDisabled(false);
    choixTarifBillet_->setCurrentIndex(0);
    editeurDateVol_->setDisabled(false);
    editeurDateVol_->setText("");

    // Since the first radio button shows as selected
    // disable fields that should not be modified
    editeurPourcentageSoldeBillet_->setDisabled(true);
    editeurPourcentageSoldeBillet_->setText("");
    editeurUtilisationsRestantesFlightPass_->setDisabled(true);
    editeurUtilisationsRestantesFlightPass_->setText("");

    // Allow clicking "Ajouter Billet"
    addBilletButton_->setDisabled(false);
}

void MainWindow::nettoyerVueCoupons(){

    // Remove coupons to reload them later
    listeCoupons_->clearSelection();
    // Allow selection of a ticket
    listeCoupons_->setDisabled(false);

    // Allow modification to fields and empty them
    editeurCodeCoupon_->setDisabled(false);
    editeurCodeCoupon_->setText("");
    editeurRabaisCoupon_->setDisabled(false);
    editeurRabaisCoupon_->setText("");
    editeurCoutCoupon_->setDisabled(false);
    editeurCoutCoupon_->setText("");
    addCouponButton_->setDisabled(false);

    // Match the display show in the assignement paper
    editeurPoints_->setDisabled(true);
    editeurPoints_->setText("N/A");
    editeurPointsCumules_->setDisabled(true);
    editeurPointsCumules_->setText("N/A");
    editeurJoursRestants_->setDisabled(true);
    editeurJoursRestants_->setText("N/A");
}

void MainWindow::nettoyerVueMembres(){

    // Remove members to reload them later
    listeMembres_->clearSelection();
    // Allow selection of a ticket
    listeMembres_->setDisabled(false);
}


void MainWindow::selectionnerBillet(QListWidgetItem* item){
    // Fetch the actual billet data
    Billet * billet = item->data(Qt::UserRole).value<Billet*>();

    // Disable modifications
    int posBillet = choixMembreBillet_->findText(QString(QString::fromStdString(billet->getNomPassager())));
    choixMembreBillet_->setCurrentIndex(posBillet);
    choixMembreBillet_->setDisabled(true);
    for (QRadioButton * button : boutonsRadioTypeBillets_){
        button->setDisabled(true);
    }
    editeurPNR_->setDisabled(true);
    editeurPrixBillet_->setDisabled(true);
    editeurOD_->setDisabled(true);
    choixTarifBillet_->setDisabled(true);
    editeurDateVol_->setDisabled(true);
    editeurPourcentageSoldeBillet_->setDisabled(true);
    editeurUtilisationsRestantesFlightPass_->setDisabled(true);
    addBilletButton_->setDisabled(true);

    // Match the display of the member's section shown in the assignment
    editeurPoints_->setText(QString("N/A"));
    editeurPoints_->setDisabled(true);
    editeurPointsCumules_->setText(QString("N/A"));
    editeurPointsCumules_->setDisabled(true);
    editeurJoursRestants_->setText(QString("N/A"));
    editeurJoursRestants_->setDisabled(true);

    // Set the values in the fields which all type of tickets have
    editeurPNR_->setText(QString::fromStdString(billet->getPnr()));
    editeurPrixBillet_->setText(QString::number(billet->getPrix()));
    editeurOD_->setText(QString::fromStdString(billet->getOd()));
    int posTarif = choixTarifBillet_->findText(QString::fromStdString(getTarifBilletString(billet->getTarif())));
    choixTarifBillet_->setCurrentIndex(posTarif);

    // Verify if it's a regular ticket
    BilletRegulier * billetRegulier = dynamic_cast<BilletRegulier*>(billet);
    if (billetRegulier){
        editeurDateVol_->setText(
            QString::fromStdString(billetRegulier->getDateVol())
        );

        BilletRegulierSolde * billetRegulierSolde = dynamic_cast<BilletRegulierSolde*>(billetRegulier);

        // Verify if it's in sale
        if (billetRegulierSolde){
            editeurPourcentageSoldeBillet_->setText(
                QString::number(billetRegulierSolde->getPourcentageSolde()));
            editeurUtilisationsRestantesFlightPass_->setText(QString("N/A"));
            boutonsRadioTypeBillets_[1]->setChecked(true);
            return;
        } else { // Set default values to field which a regular ticket does not have
            editeurPourcentageSoldeBillet_->setText(QString("N/A"));
            editeurUtilisationsRestantesFlightPass_->setText(QString("N/A"));
            boutonsRadioTypeBillets_[0]->setChecked(true);
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
        } else { // No in sale, so set default values to sale fields
            editeurPourcentageSoldeBillet_->setText(QString("N/A"));
            boutonsRadioTypeBillets_[3]->setChecked(true);
            return;
        }
    } else { // In case a basic ticket is added programmatically?
        editeurDateVol_->setText(QString("N/A"));
        editeurPourcentageSoldeBillet_->setText(QString("N/A"));
        editeurUtilisationsRestantesFlightPass_->setText(QString("N/A"));
        boutonsRadioTypeBillets_[2]->setChecked(true);
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

    //Disable abilty to add a coupon
    addCouponButton_->setDisabled(true);

    // Match the display in the assignment
    editeurPoints_->setDisabled(true);
    editeurPointsCumules_->setDisabled(true);
    editeurJoursRestants_->setDisabled(true);
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
            editeurJoursRestants_->setText(QString::number(membrePremium->getJourRestants()));
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

void MainWindow::selectionnerTypeBillet(int index){
    switch (index) {
        case -2: // Regular
        editeurPNR_->setDisabled(false);
        editeurPrixBillet_->setDisabled(false);
        editeurOD_->setDisabled(false);
        editeurDateVol_->setDisabled(false);
        editeurPourcentageSoldeBillet_->setDisabled(true);
        editeurUtilisationsRestantesFlightPass_->setDisabled(true);
        break;
        case -3: // Regular in sale
        editeurPNR_->setDisabled(false);
        editeurPrixBillet_->setDisabled(false);
        editeurOD_->setDisabled(false);
        editeurDateVol_->setDisabled(false);
        editeurPourcentageSoldeBillet_->setDisabled(false);
        editeurUtilisationsRestantesFlightPass_->setDisabled(true);
        break;
        case -4: // FlightPass
        editeurPNR_->setDisabled(false);
        editeurPrixBillet_->setDisabled(false);
        editeurOD_->setDisabled(false);
        editeurDateVol_->setDisabled(true);
        editeurPourcentageSoldeBillet_->setDisabled(true);
        editeurUtilisationsRestantesFlightPass_->setDisabled(true);
        break;
        case -5: // FlightPass in sale
        editeurPNR_->setDisabled(false);
        editeurPrixBillet_->setDisabled(false);
        editeurOD_->setDisabled(false);
        editeurDateVol_->setDisabled(true);
        editeurPourcentageSoldeBillet_->setDisabled(false);
        editeurUtilisationsRestantesFlightPass_->setDisabled(true);
        break;
       default: // In case of a unexpected int?
            editeurPNR_->setDisabled(true);
            editeurPrixBillet_->setDisabled(true);
            editeurOD_->setDisabled(true);
            editeurDateVol_->setDisabled(true);
            editeurPourcentageSoldeBillet_->setDisabled(true);
            editeurJoursRestants_->setDisabled(true);
    }
}

void MainWindow::ajouterBillet(){

    try {
        // Get the text from the combo box
        QString memberName = choixMembreBillet_->currentText();

        // Find the corresponding member
        Membre * member = nullptr;
        for (int i = 0; i < listeMembres_->count(); ++i){
            // store the item i
            QListWidgetItem * item = listeMembres_->item(i);

            // fetch the actual member pointer from the item
            Membre* tempMember = item->data(Qt::UserRole).value<Membre*>();

            if (memberName.toStdString() == tempMember->getNom()){
                // We found the member which selected in the combo box
                member = tempMember;
                // No need to continue looping
                break;
            }
        }

        if (!member){ // No actual member was selected
            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun membre selectionné!"));
            e.raise();
        }

        // Fetch the ticket's type
        QRadioButton* selection = nullptr;
        for (QRadioButton* button : boutonsRadioTypeBillets_){
            if (button->isChecked()){
                selection = button;
                break;
            }
        }

        if (!selection){ // No type specified
            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun type de billet sélectionné!"));
            e.raise();
        }

        // Verify if common fields were filled
        if (editeurPNR_->text().isEmpty()){
            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun PNR défini."));
            e.raise();
        } else if (editeurPrixBillet_->text().isEmpty()) {

            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun Prix défini."));
            e.raise();
        } else if (editeurOD_->text().isEmpty()){
            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucune Origine-Destination définie."));
            e.raise();
        } else if (choixTarifBillet_->currentText().toStdString() == "Tarif Billet"){
            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun Tarif Billet défini."));
            e.raise();
        }

        // Depending on the type of ticket selected, verify if
        // the fields were filled and create the ticket
        if (selection->text().toStdString() == "Regulier"){

            if (editeurDateVol_->text().isEmpty()){
                ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucune Date de vol définie."));
                e.raise();
            }
            // Create the ticket
            Billet* billet = new BilletRegulier(
                        editeurPNR_->text().toStdString(),
                        editeurPrixBillet_->text().toDouble(),
                        editeurOD_->text().toStdString(),
                        getTarifBillet(),
                        editeurDateVol_->text().toStdString());

            // Add it to the corresponding member
            member->ajouterBillet(billet);

        } else if (selection->text().toStdString() == "Regulier Solde"){

            if (editeurDateVol_->text().isEmpty()){
                ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucune Date de vol définie."));
                e.raise();
            } else if (editeurPourcentageSoldeBillet_->text().isEmpty()){
                    ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun Pourcentage solde billet défini."));
                    e.raise();
            }

            // Create the ticket
            Billet* billet = new BilletRegulierSolde(
                        editeurPNR_->text().toStdString(),
                        editeurPrixBillet_->text().toDouble(),
                        editeurOD_->text().toStdString(),
                        getTarifBillet(),
                        editeurDateVol_->text().toStdString(),
                        editeurPourcentageSoldeBillet_->text().toDouble()
                        );

            // Add it to the corresponding member
            member->ajouterBillet(billet);

        } else if (selection->text().toStdString() == "FlightPass"){

            // Create the ticket
            Billet * billet = new FlightPass(
                        editeurPNR_->text().toStdString(),
                        editeurPrixBillet_->text().toDouble(),
                        editeurOD_->text().toStdString(),
                        getTarifBillet()
                        );

            // Add it to the corresponding member
            member->ajouterBillet(billet);

        } else if (selection->text().toStdString() == "FlightPass Solde"){

            if (editeurPourcentageSoldeBillet_->text().isEmpty()){
                            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun Pourcentage solde billet définie."));
                            e.raise();
                        }
            // Create the ticket
            Billet * billet = new FlightPassSolde(
                        editeurPNR_->text().toStdString(),
                        editeurPrixBillet_->text().toDouble(),
                        editeurOD_->text().toStdString(),
                        getTarifBillet(),
                        editeurPourcentageSoldeBillet_->text().toDouble()
                        );

            // Add it to the corresponding member
            member->ajouterBillet(billet);
        }

        // Show a confirmation msg and clean the window
        QString msg = QString::fromStdString("Billet " + editeurPNR_->text().toStdString() + " a été ajouté!");
        afficherMessage(msg);
        nettoyerVueBillets();
        chargerBillets();

    } catch (ExceptionArgumentInvalide& e){ // If a field is not filled
          // Print exception msg here
          afficherMessage(e.what());
    }
}

void MainWindow::ajouterCoupon(){

    try {

        // Verify if fields are filled
        if (editeurCodeCoupon_->text().isEmpty()){
            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun Code défini."));
            e.raise();
        } else if (editeurRabaisCoupon_->text().isEmpty()){
            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun Rabais défini."));
            e.raise();
        } else if (editeurCoutCoupon_->text().isEmpty()){
            ExceptionArgumentInvalide e = ExceptionArgumentInvalide(QString("ERREUR: Aucun Cout défini."));
            e.raise();
        }

        // Create a new coupon
        Coupon* coupon = new Coupon(editeurCodeCoupon_->text().toStdString(),
                                    editeurRabaisCoupon_->text().toInt(),
                                    editeurCoutCoupon_->text().toInt());

        // Add the coupon to the vector
        coupons_.push_back(coupon);

        // Print confirmation msg and clean coupon's display
        QString msg = QString::fromStdString("Coupon " + editeurCodeCoupon_->text().toStdString() + " a été ajouté!");
        afficherMessage(msg);
        nettoyerVueCoupons();
        chargerCoupons();

    } catch (ExceptionArgumentInvalide& e ){ // if some info is missing
        // No actual member was selected
        afficherMessage(e.what());
    }
}


void MainWindow::filtrerListe(int index){
    // Iterate through all the members
    for (int i = 0; i < listeMembres_->count(); ++i){

        // store the item i
        QListWidgetItem *item = listeMembres_->item(i);

        // fetch the actual member pointer from the item
        Membre* member = item->data(Qt::UserRole).value<Membre*>();

        // Hide the member if the index corresponds to its type
        item->setHidden(!filtrerMasque(member, index));
    }
}

bool MainWindow::filtrerMasque(Membre* membre, int index) {

    switch (index){
        case 2 : // Verify if member is actually premium
            if (typeid(*membre) == typeid(MembrePremium))
                return true;
            break;
        case 1 : // Verify if member is actually regular
            if (typeid(*membre) == typeid(MembreRegulier))
                return true;
            break;
        case 0 : // Return true since a member was passed as a parameter
            return true;
        default:
            return false;
    }
    return false;
}

TarifBillet MainWindow::getTarifBillet(){
    // fetch the text from selected Tarif
    QString tarif = choixTarifBillet_->currentText();

    // Return the matching Tarif
    if (tarif == "Economie")
        return TarifBillet::Economie;
    if (tarif == "Premium economie")
        return TarifBillet::PremiumEconomie;
    if (tarif == "Affaire")
        return TarifBillet::Affaire;
    if (tarif == "Premiere")
        return TarifBillet::Premiere;

    // return a TarifBillet for sure
    return TarifBillet::Economie;
}

// Helper to get a string depending on the tarif we are working with
string MainWindow::getTarifBilletString(const TarifBillet & tarif){

    if (tarif == TarifBillet::Economie)
        return "Economie";
    if (tarif == TarifBillet::PremiumEconomie)
        return "Premium economie";
    if (tarif == TarifBillet::Affaire)
        return "Affaire";
    if (tarif == TarifBillet::Premiere)
        return "Premiere";
    return "Economie";
}

Membre* MainWindow::trouverMembreParNom(const string& nom){
    auto it = std::find_if(membres_.begin(), membres_.end(),
        [&nom](Membre* ptrMembre) -> bool {return ptrMembre->getNom() == nom;});
    return *it;
}
