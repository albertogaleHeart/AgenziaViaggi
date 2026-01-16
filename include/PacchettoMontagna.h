#ifndef PACCHETTOMONTAGNA_H
#define PACCHETTOMONTAGNA_H

#include "PacchettoViaggio.h"
#include <string>
#include <vector>


class PacchettoMontagna : public PacchettoViaggio{
private:
    bool skipassIncluso; // true se include skipass
    int numeroEscursioni; // Numero di escursioni guidate incluse
    std::string difficolta; // "Facile", "Media", "Difficile"

    public:
    PacchettoMontagna(std::string codice, std::string dest, int giorni, double prezzo, bool skipass, int escursioni, std::string difficolta);
    double calcolaPrezzoFinale() const override; 
    void stampaDettagli() const override;
    std::string toString() const override;
    std::string getTipologia() const override;
};

#endif