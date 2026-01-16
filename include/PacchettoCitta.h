#ifndef PACCHETTOACITTA_H
#define PACCHETTOACITTA_H

#include "PacchettoViaggio.h"
#include <string>
#include <vector>


class PacchettoCitta : public PacchettoViaggio {
private:
    int numeroMusei; // Numero di musei inclusi nel tour
    bool guidaTuristica; // true se include guida turistica
    std::string categoriaHotel; // "3 stelle", "4 stelle", "5 stelle"

public:
    // Costruttore
    PacchettoCitta(std::string codice, std::string dest, int giorni, double prezzo, int musei, bool guida, std::string hotel);
    double calcolaPrezzoFinale() const override; 
    void stampaDettagli() const override;
    std::string toString() const override;
    std::string getTipologia() const override;
};

#endif