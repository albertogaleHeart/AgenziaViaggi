#include "../include/PacchettoViaggio.h"
#include <iostream>
#include "../include/Utils.h"
using namespace std;

PacchettoViaggio::PacchettoViaggio(string codice, string dest, int giorni, double prezzo)
    : codicePacchetto(codice), 
      destinazione(dest), 
      durataGiorni(giorni), 
      prezzoBase(prezzo), 
      disponibile(true) {} 

PacchettoViaggio::~PacchettoViaggio() {}


string PacchettoViaggio::getCodicePacchetto() const {
    return codicePacchetto;
}

string PacchettoViaggio::getDestinazione() const {
    return destinazione;
}

int PacchettoViaggio::getDurataGiorni() const {
    return durataGiorni;
}

double PacchettoViaggio::getPrezzoBase() const {
    return prezzoBase;
}

bool PacchettoViaggio::isDisponibile() const {
    return disponibile;
}

void PacchettoViaggio::setDisponibile(bool disp) {
    disponibile = disp;
}


