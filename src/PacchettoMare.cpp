#include "../include/PacchettoMare.h"
#include <iostream>
#include <iomanip>
#include "../include/Utils.h"
using namespace std;

PacchettoMare::PacchettoMare(string codice, string dest, int giorni,
                             double prezzo, bool ombrellone, string trattamento, 
                             bool attrezziSport)
    : PacchettoViaggio(codice, dest, giorni, prezzo),
      ombrelloneIncluso(ombrellone), 
      tipoTrattamento(trattamento), 
      attrezzaturaSportiva(attrezziSport) {}

double PacchettoMare::calcolaPrezzoFinale() const {
    double totale = prezzoBase;
    if (ombrelloneIncluso) totale += 100.0;
    if (tipoTrattamento == "Pensione completa") totale += 200.0;
    else if (tipoTrattamento == "Mezza pensione") totale += 100.0;
    if (attrezzaturaSportiva) totale += 150.0;
    return totale;
}  

void PacchettoMare::stampaDettagli() const {
    cout << "PACCHETTO MARE\nCodice: " << codicePacchetto << "\n"
         << "Destinazione: " << destinazione << "\n"
         << "Durata: " << durataGiorni << " giorni\n"
         << "Ombrellone incluso: " << (ombrelloneIncluso ? "Si" : "No") << "\n"
         << "Tipo di trattamento: " << tipoTrattamento << "\n"
         << "Attrezzatura sportiva inclusa: " << (attrezzaturaSportiva ? "Si" : "No") << "\n";
    cout << "\nPrezzo Finale: " << calcolaPrezzoFinale() << " Euro\n";
}

string PacchettoMare::toString() const {
    return getTipologia() + ";" + getCodicePacchetto() + ";" + destinazione + ";" + to_string(durataGiorni) + ";" + to_string(getPrezzoBase()) + ";" +
    (isDisponibile() ? "1" : "0") + ";" + (ombrelloneIncluso ? "1" : "0") + ";" + tipoTrattamento + ";" + (attrezzaturaSportiva ? "1" : "0") + "\n"; 
}

string PacchettoMare::getTipologia() const {
    return "Mare";
}
