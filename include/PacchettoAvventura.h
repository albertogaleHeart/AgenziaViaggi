#ifndef PACCHETTOAVVENTURA_H
#define PACCHETTOAVVENTURA_H

#include "PacchettoViaggio.h"
#include <string>
#include <vector>


class PacchettoAvventura : public PacchettoViaggio {

private:
    std::vector<std::string> attivita; // Lista attività (es: "Rafting", "Arrampicata", "Parapendio")
    std::string livelloAdrenalina; // "Basso", "Medio", "Alto"
    bool assicurazioneExtra; // true se include assicurazione extra

public:
    // Costruttore
    PacchettoAvventura(std::string codice, std::string dest, int giorni, double prezzo, std::vector<std::string> attivita,
                       std::string adrenalina, bool assicurazione);
    double calcolaPrezzoFinale() const override; 
    void stampaDettagli() const override;
    std::string toString() const override;
    std::string getTipologia() const override;

};

#endif