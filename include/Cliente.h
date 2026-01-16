#ifndef CLIENTE_H
#define CLIENTE_H

#include "Utils.h"
#include <string>

class Cliente {
private:
    std::string codiceCliente; // Formato: "CLT-XXXX"
    std::string nome;
    std::string cognome;
    std::string email;
    std::string telefono;
    int eta;
    std::string tipologiaCliente; // "Standard", "Premium", "VIP"

public:
    // Costruttore
    Cliente(std::string codice, std::string nom, std::string cog, std::string mail, std::string tel, int et, std::string tipo);
    // Getter
    std::string getCodiceCliente() const;
    std::string getNomeCompleto() const; // Ritorna "Nome Cognome"
    std::string getEmail() const;
    std::string getTelefono() const;
    int getEta() const;
    std::string getTipologiaCliente() const;
    // Metodo per applicare sconto in base alla tipologia
    double applicaSconto(double prezzoBase) const;
    // Standard: 0%, Premium: 10%, VIP: 20%
    void stampaInfo() const;
};


#endif