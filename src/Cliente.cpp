#include "../include/Cliente.h"
#include <iostream>
#include "../include/Utils.h"

using namespace std;

Cliente::Cliente(string codice, string nom, string cog, string mail, string tel, int et, string tipo)
    : codiceCliente(codice),
      nome(nom),
      cognome(cog),
      email(mail),
      telefono(tel),
      eta(et),
      tipologiaCliente(tipo) {}

string Cliente::getCodiceCliente() const {
    return codiceCliente;
}


string Cliente::getNomeCompleto() const {  
    return nome + " " + cognome;
} 

string Cliente::getEmail() const {
    return email;
} 

string Cliente::getTelefono() const {
    return telefono;
} 

int Cliente::getEta() const {
    return eta;
}

string Cliente::getTipologiaCliente() const {
    return tipologiaCliente;
}


double Cliente::applicaSconto(double prezzoBase) const {
    double totale = prezzoBase;
    if (tipologiaCliente == "Premium") totale *= 0.90; //10% di sconto
    else if (tipologiaCliente == "VIP") totale *= 0.80; //20% di sconto
    return totale;
}

void Cliente::stampaInfo() const {
    cout << "Codice: " << codiceCliente << "\n"
         << "Nome: " << nome << "\n"
         << "Cognome: " << cognome << "\n"
         << "Email: " << email << "\n"
         << "Numero di telefono: " << telefono << "\n"
         << "Età: " << eta << "\n"
         << "Tipologia cliente: " << tipologiaCliente << "\n";
}



