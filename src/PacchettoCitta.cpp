#include "../include/PacchettoCitta.h"
#include <iostream>
#include <iomanip>
#include "../include/Utils.h"
using namespace std;

PacchettoCitta::PacchettoCitta(string codice, string dest, int giorni, 
                               double prezzo, int musei, bool guida, string hotel)
    : PacchettoViaggio(codice, dest, giorni, prezzo),
      numeroMusei(musei),
      guidaTuristica(guida),
      categoriaHotel(hotel){}
    
double PacchettoCitta::calcolaPrezzoFinale() const {
    double totale = prezzoBase;
    totale += numeroMusei * 15;
    if (guidaTuristica) totale *= 1.10;
    if (categoriaHotel == "4 stelle") totale *= 1.15;
    else if (categoriaHotel == "5 stelle") totale *= 1.30;
    return totale;
}

void PacchettoCitta::stampaDettagli() const {
    cout << "PACCHETTO CITTA\nCodice: " << codicePacchetto << "\n"
         << "Destinazione: " << destinazione << "\n"
         << "Durata: " << durataGiorni << " giorni\n"
         << "Numero musei: " <<numeroMusei << "\n"
         << "Guida turistica: " << (guidaTuristica ? "Si" : "No") << "\n"
         << "Categoria Hotel: " << categoriaHotel << "\n";
    
    cout << "\nPrezzo Finale: " << calcolaPrezzoFinale() << " Euro\n";
}

string PacchettoCitta::toString() const {
    return getTipologia() + ";" + getCodicePacchetto() + ";" + destinazione + ";" + to_string(durataGiorni) + ";" + to_string(getPrezzoBase()) + ";" +
    (isDisponibile() ? "1" : "0") + ";" + to_string(numeroMusei) + ";" + (guidaTuristica ? "1" : "0") + ";" + categoriaHotel + "\n"; 
}

string PacchettoCitta::getTipologia() const{
    return "Citta";
}




