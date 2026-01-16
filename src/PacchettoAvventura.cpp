#include "../include/PacchettoAvventura.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "../include/Utils.h"
using namespace std;

PacchettoAvventura::PacchettoAvventura(string codice, string dest, int giorni, 
                                       double prezzo, vector<string> att, 
                                       string adrenalina, bool assicurazione)
    : PacchettoViaggio(codice, dest, giorni, prezzo), 
      attivita(att), 
      livelloAdrenalina(adrenalina), 
      assicurazioneExtra(assicurazione) {}


double PacchettoAvventura::calcolaPrezzoFinale() const {
    double totale = prezzoBase;
    totale += attivita.size() * 80.0;
    if (livelloAdrenalina == "Alto") {
        totale *= 1.25; // +25% sul totale 
    } else if (livelloAdrenalina == "Medio") {
        totale *= 1.15; // +15% sul totale 
    }
    if (assicurazioneExtra) {
        totale += 100.0; 
    }

    return totale;
}

void PacchettoAvventura::stampaDettagli() const {
    cout << "PACCHETTO AVVENTURA\nCodice: " << codicePacchetto << "\n"
         << "Destinazione: " << destinazione << "\n"
         << "Durata: " << durataGiorni << " giorni\n"
         << "Livello Adrenalina: " << livelloAdrenalina << "\n"
         << "Assicurazione Extra: " << (assicurazioneExtra ? "Si" : "No") << "\n"
         << "Attivita incluse: ";
    
        for (size_t i = 0; i < attivita.size(); ++i) {
        cout << attivita[i] << (i == attivita.size() - 1 ? "" : ", ");
    }
    
    cout << "\nPrezzo Finale: " << calcolaPrezzoFinale() << " Euro\n";
}  //lo \n è fuori dal ciclo for

string PacchettoAvventura::toString() const {
    string ListaAtt = "";
    for (size_t i = 0; i < attivita.size(); i++){
        ListaAtt += attivita[i];
        if (i < attivita.size()-1) ListaAtt += "|";
    }
    return getTipologia() + ";" + getCodicePacchetto() + ";" + destinazione + ";" + to_string(durataGiorni) + ";" + to_string(getPrezzoBase()) + ";" +
    (isDisponibile() ? "1" : "0") + ";" + ListaAtt + ";" + livelloAdrenalina + ";" + (assicurazioneExtra ? "1" : "0") + "\n"; 
}

// Ritorna la stringa della tipologia 
string PacchettoAvventura::getTipologia() const {
    return "Avventura";
}