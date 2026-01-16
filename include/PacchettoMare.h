#ifndef PACCHETTOMARE_H
#define PACCHETTOMARE_H

#include "PacchettoViaggio.h"
#include <string>
#include <vector>

class PacchettoMare : public PacchettoViaggio {
private:
    bool ombrelloneIncluso; // true se include ombrellone+lettini
    std::string tipoTrattamento; // "Pensione completa", "Mezza pensione", "Solo colazione"
    bool attrezzaturaSportiva; // true se include attrezzatura per sport acquatici

public:
    // Costruttore
    PacchettoMare(std::string codice, std::string dest, int giorni, double prezzo, bool ombrellone, std::string trattamento, bool attrezziSport);
    double calcolaPrezzoFinale() const override; 
    void stampaDettagli() const override;
    std::string toString() const override;
    std::string getTipologia() const override;
};

#endif