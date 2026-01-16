#include "../include/PacchettoMontagna.h"
#include <iostream>
#include <iomanip>
#include "../include/Utils.h"
using namespace std;

PacchettoMontagna::PacchettoMontagna(string codice, string dest, int giorni,
                                     double prezzo, bool skipass, int escursioni, 
                                     string diff)
    :PacchettoViaggio(codice, dest, giorni, prezzo),
     skipassIncluso(skipass),
     numeroEscursioni(escursioni),
     difficolta(diff) {}

double PacchettoMontagna::calcolaPrezzoFinale() const {
    double totale = prezzoBase;
    if (skipassIncluso) totale += durataGiorni * 45.0;
    totale += numeroEscursioni * 30.0; 
    if (difficolta == "Difficile") totale *= 1.20;
    return totale;
}  

void PacchettoMontagna::stampaDettagli() const {
    cout << "PACCHETTO MONTAGNA\nCodice: " << codicePacchetto << "\n"
         << "Destinazione: " << destinazione << "\n"
         << "Durata: " << durataGiorni << " giorni\n"
         << "Skipass incluso: " << (skipassIncluso ? "Si" : "No") << "\n"
         << "Numero di escursioni: " << numeroEscursioni << "\n"
         << "Difficoltà: " << difficolta << "\n";
    cout << "\nPrezzo Finale: " << calcolaPrezzoFinale() << " Euro\n";
}

string PacchettoMontagna::toString() const {
    return getTipologia() + ";" + getCodicePacchetto() + ";" + destinazione + ";" + to_string(durataGiorni) + ";" + to_string(getPrezzoBase()) + ";" +
    (isDisponibile() ? "1" : "0") + ";" + (skipassIncluso ? "1" : "0") + ";" + to_string(numeroEscursioni) + ";" + difficolta + "\n"; 
}

string PacchettoMontagna::getTipologia() const {
    return "Montagna";
}