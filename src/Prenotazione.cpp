#include "../include/Prenotazione.h"
#include <iostream>
#include "../include/Utils.h"
using namespace std;

Prenotazione::Prenotazione(string codice, Cliente* cli, PacchettoViaggio* pac, int num) 
    : codicePrenotazione(codice), 
      cliente(cli), 
      pacchetto(pac),
      numeroPersone(num), 
      confermata(false) {}

void Prenotazione::calcolaPrezzoTotale() {
    double prezzoUnitario = pacchetto->calcolaPrezzoFinale();
    double totaleSenzaSconto = prezzoUnitario * numeroPersone;
    prezzoTotale = cliente->applicaSconto(totaleSenzaSconto);
}

void Prenotazione::confermaPrenotazione() {
    confermata = true; 
}

string Prenotazione::getCodicePrenotazione() const {
    return codicePrenotazione;
}
Cliente* Prenotazione::getCliente() const {
    return cliente;
}

PacchettoViaggio* Prenotazione::getPacchetto() const { 
    return pacchetto; 
}

double Prenotazione::getPrezzoTotale() const {
    return prezzoTotale;
}
bool Prenotazione::isConfermata() const {
    return confermata;
}
void Prenotazione::stampaPrenotazione() const {
    cout << "Codice Prenotazione: " << codicePrenotazione << "\n"
         << "Codice Cliente: " << cliente->getCodiceCliente() << "\n"
         << "Codice Pacchetto: " << pacchetto->getCodicePacchetto() << "\n"
         << "Numero di persone: " << numeroPersone << "\n"
         << "Confermata: " << (confermata ? "Si" : "No") << "\n"
         << "Prezzo Totale: " << getPrezzoTotale() << "\n";
}
