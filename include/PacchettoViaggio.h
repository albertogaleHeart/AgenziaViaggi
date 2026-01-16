#ifndef PACCHETTOVIAGGIO_H
#define PACCHETTOVIAGGIO_H

#include <string>
#include <fstream> // per lavorare con i file



// Classe base astratta
class PacchettoViaggio
{
protected:
    // Attributi protetti per le sottoclassi
    std::string codicePacchetto;
    std::string destinazione;
    int durataGiorni;
    double prezzoBase;
    bool disponibile;

public:
    PacchettoViaggio(std::string codice, std::string dest, int giorni, double prezzo);

    virtual ~PacchettoViaggio();

    virtual double calcolaPrezzoFinale() const = 0;
    virtual void stampaDettagli() const = 0;
    virtual std::string toString() const = 0;
    virtual std::string getTipologia() const = 0;

    std::string getCodicePacchetto() const;
    std::string getDestinazione() const;
    int getDurataGiorni() const;
    double getPrezzoBase() const;
    bool isDisponibile() const;
    void setDisponibile(bool disp);
};

#endif
