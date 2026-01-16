#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include "Cliente.h"
#include "PacchettoViaggio.h"
#include <string>

class Prenotazione {
private:
    std::string codicePrenotazione;
    Cliente* cliente;               // Puntatore al cliente
    PacchettoViaggio* pacchetto;    // Puntatore al pacchetto 
    int numeroPersone; 
    double prezzoTotale; 
    bool confermata;

public:
    Prenotazione(std::string codice, Cliente* cli, PacchettoViaggio* pac, int num);
    void calcolaPrezzoTotale(); 
    void confermaPrenotazione();
    std::string getCodicePrenotazione() const;
    Cliente* getCliente() const;
    PacchettoViaggio* getPacchetto() const;
    double getPrezzoTotale() const;
    bool isConfermata() const;
    void stampaPrenotazione() const;
};

#endif