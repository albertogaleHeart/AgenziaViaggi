#include "../include/Utils.h"
#include <iostream>
#include <algorithm> // Per count()
#include <cctype>    // Per isdigit()

using namespace std;

bool validaTelefono(string telefono) {
    // 1. Controllo lunghezza 
    if (telefono.length() != 10) return false;

    // 2. Controllo che siano tutti numeri
    for (char c : telefono) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int takePositiveInt() {
    int numero;
    cin >> numero;
    while (numero <= 0) {
        cout << "Errore! Inserire un valore numerico positivo: ";
        cin >> numero;
    }
    return numero;
}

double takePositiveDouble() {
    double numero;
    cin >> numero;
    while (numero <= 0) {
        cout << "Errore! Inserire un valore numerico positivo: ";
        cin >> numero;
    }
    return numero;
}

string takeEmail() {
    string email = "";
    int chiocciola = 0;
    while (chiocciola != 1) {
        cout << "L'email deve contenere esattamente una @\n";
        cout << "Inserisci l'indirizzo email: ";
        cin >> email;
        chiocciola = count(email.begin(), email.end(), '@');
    }
    return email;
}

string takeTipologia() {
    string tipo = "";
    while (tipo != "Standard" && tipo != "Premium" && tipo != "VIP") {
        cout << "La tipologia cliente deve essere: Standard, Premium o VIP\n";
        cout << "Inserisci tipologia cliente: ";
        cin >> tipo;
    }
    return tipo;
}

bool validaData (string data) {  // gg/mm/aaaa --> 01/06/2019
    if (data.length() != 10) return false;
    if (data[2] != '/' || data[5] != '/') return false;
    for (size_t i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue; // in quelle posizioni ci sono le barre /
        if (!isdigit(data[i])) return false;
    }
    int giorno = stoi(data.substr(0,2));
    int mese = stoi(data.substr(3,2));
    int giorniXmese[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (giorno < 1 || giorno > giorniXmese[mese-1]) return false; 
    if (mese < 1 || mese > 12) return false;
    
    return true;
}

string takeTrattamento () {
    string trattamento = "";
    while (trattamento != "Solo colazione" && trattamento != "Mezza pensione" && trattamento != "Pensione completa") {
        cout << "Tipologie di trattamento: Solo colazione, Mezza pensione o Pensione completa\n";
        cout << "Inserisci tipo trattamento: ";
        getline(cin >>ws, trattamento);
    }
    return trattamento;
}

string takeDifficolta() {
    string difficolta = "";
    while (difficolta != "Facile" && difficolta != "Medio" && difficolta != "Difficile") {
        cout << "Il livello di difficoltà deve essere Facile, Medio o Difficile\n";
        cout << "Inserire livello di difficoltà: ";
        cin >> difficolta;
    }
    return difficolta;
}

string takeStelleHotel () {
    int stelle = 0;
    string hotel = "";
    while (stelle < 1 || stelle > 5 ) {
        cout << "L'hotel va da 1 a 5 stelle\n";
        cout << "Inserisci quante stelle ha l'hotel: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> stelle;
    }
    if (stelle == 1) hotel = "1 stella";
    else hotel = to_string(stelle) + " stelle";
    return hotel;
}

string takeLivAdrenalina() {
    string livelloAdrenalina;
    while (livelloAdrenalina != "Basso" && livelloAdrenalina != "Medio" && livelloAdrenalina != "Alto") {
        cout << "Il livello di adrenalina può essere Basso, Medio o Alto\n";
        cout << "Inserisci livello di adrenalina: ";
        cin >> livelloAdrenalina;
    }
    return livelloAdrenalina;
}



