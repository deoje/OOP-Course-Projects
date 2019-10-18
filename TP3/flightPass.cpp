#include "flightPass.h"

FlightPass::FlightPass(
	const string& pnr,
	const string& nomPassager,
	double prix,
	const string& od,
	TarifBillet tarif,
	TypeBillet typeBillet
)
	: Billet(pnr, nomPassager, prix, od, tarif, typeBillet),
	  nbUtilisationsRestante_(NB_UTILISATIONS_INITIALE)
{
}

void FlightPass::decrementeNbUtilisations() 
{
	nbUtilisationsRestante_--;
}

int FlightPass::getNbUtilisationsRestante() const
{
	return nbUtilisationsRestante_;
}

ostream& operator<<(ostream& os, const FlightPass& flightpass)
{
	// Implicit upcasting i.e. flightPass --> Billet
	//Billet tempBillet = flightpass;
	Billet billet = static_cast<Billet>(flightpass);

	os << billet
	   << "\t\t\t" << setw(11) << "- Utilisation restantes" << ": " << flightpass.nbUtilisationsRestante_ << endl;

	return os;
}