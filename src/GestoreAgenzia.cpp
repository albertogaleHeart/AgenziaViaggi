#include "../include/GestoreAgenzia.h"
#include "../include/PacchettoCitta.h"
#include "../include/PacchettoMare.h"
#include "../include/PacchettoMontagna.h"
#include "../include/PacchettoAvventura.h"
#include "../include/Utils.h"
#include <iostream> 
#include <iomanip>  
#include <fstream>
using namespace std; 

// Costruttore: inizializza i counttori per i codici univoci 
GestoreAgenzia::GestoreAgenzia() 
    : prossimoCodicePacchetto(1), prossimoCodiceCliente(1), prossimoCodicePrenotazione(1) {}

// Distruttore: libera tutta la memoria allocata dinamicamente 
GestoreAgenzia::~GestoreAgenzia() {
    for (auto p : catalogo) delete p; // ciclo for che scorre i pacchetti nel catalogo
    for (auto c : clienti) delete c;
    for (auto pr : prenotazioni) delete pr;
    
    catalogo.clear();
    clienti.clear();
    prenotazioni.clear();
}

// === UTILITY ===
// Genera codici nel formato richiesto, es: PKG-0001 
string GestoreAgenzia::generaCodiceUnico(char tipo) {
    string prefisso;
    int numero;

    if (tipo == 'P') {
        prefisso = "PKG-"; 
        numero = prossimoCodicePacchetto++;
    } else if (tipo == 'C') {
        prefisso = "CLT-";
        numero = prossimoCodiceCliente++;
    } else {
        prefisso = "BKG-";
        numero = prossimoCodicePrenotazione++;
    }

    // Formatta il numero con 4 cifre (es: 0001)
    string numStr = to_string(numero);
    return prefisso + string(4 - numStr.length(), '0') + numStr;
}

// === GESTIONE PACCHETTI ===
void GestoreAgenzia::aggiungiPacchettoManuale() {
    int scelta;
    cout << "\nTipo di pacchetto (1: Citta, 2: Mare, 3: Montagna, 4: Avventura): ";
    cin >> scelta;

    string dest, cod = generaCodiceUnico('P');
    int giorni;
    double prezzo;
    cout << "Destinazione: "; cin >> dest;
    cout << "Durata (giorni): "; giorni = takePositiveInt();
    cout << "Prezzo base: "; prezzo = takePositiveInt();

    if (scelta == 1) {
        int musei; bool guida; string hotel;
        cout << "Num. Musei: "; musei = takePositiveInt(); 
        cout << "Guida (1:si, 0:no): "; cin >> guida;
        hotel = takeStelleHotel ();
        catalogo.push_back(new PacchettoCitta(cod, dest, giorni, prezzo, musei, guida, hotel));
    }
    else if(scelta==2) {
        bool ombrellone; string trattamento; bool attrezziSport;
        cout << "Ombrellone compreso(1:si, 0:no) "; cin >> ombrellone;
        trattamento = takeTrattamento();
        cout << "Attrezzatura sportiva compresa(1:si, 0:no): "; cin>>attrezziSport; 
        catalogo.push_back(new PacchettoMare(cod, dest, giorni, prezzo, ombrellone, trattamento, attrezziSport));
    }
    else if(scelta==3) {
        bool skipassIncluso; int numeroEscursioni; string difficolta; 
        cout << "Ski pass compreso(1:si, 0:no) "; cin >> skipassIncluso;
        cout << "Numero Escursioni: "; numeroEscursioni = takePositiveInt(); 
        difficolta = takeDifficolta();
        catalogo.push_back(new PacchettoMontagna(cod, dest, giorni, prezzo, skipassIncluso, numeroEscursioni, difficolta));
    }
    else if(scelta==4) {
        vector<string> attivita; string livelloAdrenalina; bool assicurazioneExtra; int numAtt;
        cout << "Quante attività vuoi inserire? "; numAtt = takePositiveInt();
        cout << "Inserisci attività: "; 
        for (size_t i = 0; i < numAtt; i++) {
            string tempAtt;
            cout << "Attività " << i+1 << ": ";
            if (i == 0) cin.ignore(); // Pulisce solo la prima volta
            getline(cin, tempAtt);
            attivita.push_back(tempAtt); 
        }
        livelloAdrenalina = takeLivAdrenalina();
        cout << "Assicurazione extra(1:si, 0:no): "; cin>>assicurazioneExtra;
        catalogo.push_back(new PacchettoAvventura(cod, dest, giorni, prezzo, attivita, livelloAdrenalina, assicurazioneExtra));
        }

    PacchettoViaggio* nuovo = catalogo.back();
    cout << "Pacchetto creato con codice: " << cod << "\n";
    cout << "Prezzo finale calcolato: " << nuovo->calcolaPrezzoFinale() << " Euro";
    
}

PacchettoViaggio* GestoreAgenzia::cercaPacchetto(string codice) { 
    for (auto p : catalogo) {                                     
        if (p->getCodicePacchetto() == codice) return p;
    }
    return nullptr;
}

void GestoreAgenzia::visualizzaCatalogo() const {
    cout << "\n--- CATALOGO PACCHETTI ---\n";
    for (auto p : catalogo) {
        p->stampaDettagli();
        cout << "--------------------------\n";
    }
}


void GestoreAgenzia::visualizzaPacchettiXTipo() const {
    cout << "Che tipo di pacchetto stai cercando? (1: Citta, 2: Mare, 3: Montagna, 4: Avventura)";
    int pack = 0;
    cin >> pack;
    if (pack == 1) {
        for (auto p: catalogo) {
            if (p->getTipologia() == "Citta") p->stampaDettagli();
        }
    }
    else if (pack == 2) {
        for (auto p: catalogo) {
            if (p->getTipologia() == "Mare") p->stampaDettagli();
        }
    }
    else if (pack == 3) {
        for (auto p: catalogo) {
            if (p->getTipologia() == "Montagna") p->stampaDettagli();
        }
    }
    else if (pack == 4) {
        for (auto p: catalogo) {
            if (p->getTipologia() == "Avventura") p->stampaDettagli();
        }
    }
}


void GestoreAgenzia::visualizzaPacchettiDisponibili() const {
    for (auto p: catalogo) {
        if (p->isDisponibile()) p->stampaDettagli();
    }
}


// === GESTIONE CLIENTI ===
void GestoreAgenzia::aggiungiCliente() {
    string nome, cognome, email, telefono, tipo;
    int eta;
    string cod = generaCodiceUnico('C');

    cout << "Nome: "; cin >> nome;
    cout << "Cognome: "; cin >> cognome;
    email = takeEmail();
    cout << "Telefono: "; cin >> telefono; 
    if(!validaTelefono(telefono)) { cout << "Numero di telefono inserito non valido\n"; return;}
    cout << "Età: "; eta = takePositiveInt();
    tipo = takeTipologia();

    clienti.push_back(new Cliente(cod, nome, cognome, email, telefono, eta, tipo));
    cout << "Cliente registrato con codice: " << cod << "\n";
}


Cliente* GestoreAgenzia::cercaCliente(string codice) {
    for (auto c : clienti) {
        if (c->getCodiceCliente() == codice) return c;
    }
    return nullptr;
}


void GestoreAgenzia::visualizzaClienti() const {
    cout << "\n--- CLIENTI ---\n";
    for (auto c : clienti) {
        c->stampaInfo();
        cout << "--------------------------\n";
    }
}


void GestoreAgenzia::visualizzaClientiXTipo() const {
    cout << "Che tipo di cliente stai cercando? (1: Standard, 2: Premium, 3: VIP)";
    int type = 0;
    cin >> type;
    if (type == 1) {
        for (auto c: clienti) {
            if (c->getTipologiaCliente() == "Standard") c->stampaInfo();
        }
    }
    else if (type == 2) {
        for (auto c: clienti) {
            if (c->getTipologiaCliente() == "Premium") c->stampaInfo();
        }
    }
    else if (type == 3) {
        for (auto c: clienti) {
            if (c->getTipologiaCliente() == "VIP") c->stampaInfo();
        }
    }
}


// === GESTIONE PRENOTAZIONI ===
void GestoreAgenzia::creaPrenotazione() {
    string codC, codP, data;
    int persone;

    cout << "Codice Cliente: "; cin >> codC;
    Cliente* cli = cercaCliente(codC);
    
    cout << "Codice Pacchetto: "; cin >> codP;
    PacchettoViaggio* pac = cercaPacchetto(codP);

    if (cli && pac && pac->isDisponibile()) {
        cout << "Numero persone: "; persone = takePositiveInt();
        cout << "Data (gg/mm/aaaa): "; cin >> data;
        if (!validaData (data)) {cout << "Data inserita non valida\n"; return;}
        string codB = generaCodiceUnico('B');
        Prenotazione* nuova = new Prenotazione(codB, cli, pac, persone);
        nuova->calcolaPrezzoTotale();
        prenotazioni.push_back(nuova);
        cout << "Prenotazione creata con codice: " << codB << "\n";
        cout << "Prezzo finale: " << nuova->getPrezzoTotale();
    } else {
        cout << "Errore: Cliente o Pacchetto non validi/disponibili.\n";
    }
}


Prenotazione* GestoreAgenzia::cercaPrenotazione(string codice) {
    for (auto pr : prenotazioni) {
        if (pr->getCodicePrenotazione() == codice) return pr;
    }
    return nullptr;
}

void GestoreAgenzia::visualizzaPrenotazioni() const{
    if (prenotazioni.empty()) {cout << "Non sono presenti prenotazioni\n"; return;}
    cout << "\n--- PRENOTAZIONI ---\n";
    for (auto pr : prenotazioni) {
        pr->stampaPrenotazione();
        cout << "--------------------------\n";
    }
}

void GestoreAgenzia::visualizzaPrenotazioniCliente(string codice) const {
    if (prenotazioni.empty()) {cout << "Non sono presenti prenotazioni\n"; return;}
    cout << "\n--- PRENOTAZIONI  DI " << codice << " ---\n";
    for (auto pr : prenotazioni) {
        if (pr->getCliente()->getCodiceCliente() == codice) pr->stampaPrenotazione();
        cout << "--------------------------\n";
    }
}

void GestoreAgenzia::visualizzaPrenotazioniConfermate() const{
    if (prenotazioni.empty()) {cout << "Non sono presenti prenotazioni\n"; return;}
    cout << "\n--- PRENOTAZIONI CONFERMATE ---\n";
    for (auto pr : prenotazioni) {
        if (pr->isConfermata()) {
            pr->stampaPrenotazione();
            cout << "--------------------------\n";
        }
    }
}


// === STATISTICHE ===
void GestoreAgenzia::statisticheGenerali() const {
    double fatturato = 0;

    
    for (auto pr : prenotazioni) {
        if (pr->isConfermata()) fatturato += pr->getPrezzoTotale();
    }

    string migliorPacchetto = "Nessuno"; 
    int maxPrenotazioni = 0;

    for (auto p : catalogo) {
        int count = 0;
        // Per ogni pacchetto nel catalogo, conto quante volte appare nelle prenotazioni
        for (auto pr : prenotazioni) {
            if (pr->getPacchetto()->getCodicePacchetto() == p->getCodicePacchetto()) {
                count++;
            }
        }
        // Se questo pacchetto ne ha più del record attuale, aggiorno il record
        if (count > maxPrenotazioni) {
            maxPrenotazioni = count;
            migliorPacchetto = p->getCodicePacchetto() + " (" + p->getDestinazione() + ")";
        }
    }

    string migliorDest = "Nessuna";
    int maxDest = 0;

    for (auto p : catalogo) {
        string destCorrente = p->getDestinazione();
        int countDest = 0;
        for (auto pr : prenotazioni) {
            if (pr->getPacchetto()->getDestinazione() == destCorrente) {
                countDest++;
            }
        }
        if (countDest > maxDest) {
            maxDest = countDest;
            migliorDest = destCorrente;
        }
    }

    cout << "\n=== STATISTICHE GENERALI ===\n";
    cout << "Totale Pacchetti: " << catalogo.size() << "\n";
    cout << "Totale Clienti: " << clienti.size() << "\n";
    cout << "Totale Prenotazioni: " << prenotazioni.size() << "\n";
    cout << "Fatturato Totale (Confermate): " << fatturato << " Euro\n";
    cout << "Pacchetto piu' prenotato: " << migliorPacchetto << " [" << maxPrenotazioni << " volte]\n";
    cout << "Destinazione piu' popolare: " << migliorDest << " [" << maxDest << " prenotazioni totali]\n";
}

void GestoreAgenzia::statistichePerTipologia() const {
    int nCitta = 0, nMare = 0, nMontagna = 0, nAvventura = 0;
    int preCitta = 0, preMare = 0, preMontagna = 0, preAvventura = 0;

    // 1. Contiamo i pacchetti nel catalogo usando getTipologia()
    for (auto p : catalogo) {
        string tipo = p->getTipologia();
        if (tipo == "Citta") nCitta++;
        else if (tipo == "Mare") nMare++;
        else if (tipo == "Montagna") nMontagna++;
        else if (tipo == "Avventura") nAvventura++;
    }

    // 2. Contiamo le prenotazioni per ogni tipo
    for (auto pr : prenotazioni) {
        string tipo = pr->getPacchetto()->getTipologia();
        if (tipo == "Citta") preCitta++;
        else if (tipo == "Mare") preMare++;
        else if (tipo == "Montagna") preMontagna++;
        else if (tipo == "Avventura") preAvventura++;
    }

    cout << "\n=== REPORT PER TIPOLOGIA ===\n";
    cout << "Citta: " << nCitta << " pacchetti, " << preCitta << " prenotazioni\n";
    cout << "Mare: " << nMare << " pacchetti, " << preMare << " prenotazioni\n";
    cout << "Montagna: " << nMontagna << " pacchetti, " << preMontagna << " prenotazioni\n";
    cout << "Avventura: " << nAvventura << " pacchetti, " << preAvventura << " prenotazioni\n";
}

Cliente* GestoreAgenzia::clienteMigliore() const {
    if (clienti.empty()) return nullptr;

    Cliente* migliore = nullptr;
    double maxSpesa = -1.0;

    for (auto c : clienti) {
        double spesaAttuale = 0;
        for (auto pr : prenotazioni) {
            if (pr->getCliente()->getCodiceCliente() == c->getCodiceCliente() && pr->isConfermata()) {
                spesaAttuale += pr->getPrezzoTotale();
            }
        }
        if (spesaAttuale > maxSpesa) {
            maxSpesa = spesaAttuale;
            migliore = c;
        }
    }
    return migliore; 
}


void GestoreAgenzia::reportDestinazioni() const {
    cout << "\n=== POPOLARITA' DESTINAZIONI ===\n";
    
    // Usiamo un vettore per non stampare due volte la stessa destinazione
    vector<string> giaStampate;

    for (auto p : catalogo) {
        string d = p->getDestinazione();
        
        // Controllo se ho già questa destinazione
        bool giaFatto = false;
        for (const string& s : giaStampate) {
            if (s == d) giaFatto = true;
        }
        if (giaFatto) continue;
        // Se è nuova conto quante prenotazioni ha quella destinazione
        int count = 0;
        for (auto pr : prenotazioni) {
            if (pr->getPacchetto()->getDestinazione() == d) {
                count++;
            }
        }
        cout << "- " << d << ": " << count << " prenotazioni\n";
        giaStampate.push_back(d);
    }
}


// === GESTIONE FILE ===
void GestoreAgenzia::salvaDatiSuFile() const {
    ofstream file_p("pacchetti_agenzia.txt");
    if (!file_p.is_open()) cout << "Errore nell'apertura del file pacchetti\n"; 
    // Salvataggio Pacchetti 
    else {
        file_p << "TIPO;CODICE;DESTINAZIONE;GIORNI;PREZZO_BASE;DISPONIBILE;DATI_SPECIFICI\n";
        for (auto p : catalogo) file_p << p->toString();
        file_p.close();
    }
    // Salvataggio clienti
    ofstream file_c("clienti_agenzia.txt");
    if (!file_c.is_open()) cout << "Errore nell'apertura del file clienti\n"; 
    else {
        file_c << "CODICE;NOME_COMPLETO;MAIL;TELEFONO;ETA;TIPO\n";
        for (auto c : clienti) {
            file_c << c->getCodiceCliente() << ";" << c->getNomeCompleto() << ";" << c->getEmail() << ";" << c->getTelefono() << ";";
            file_c << c->getEta() << ";" << c->getTipologiaCliente() << "\n";
        }
        file_c.close();
    }
    // Salvataggio prenotazioni
    ofstream file_pr("prenotazioni_agenzia.txt");
    if (!file_pr.is_open()) cout << "Errore nell'apertura del file prenotazioni\n";
    else {
        file_pr << "CODICE;CLIENTE;PACCHETTO;PERSONE;CONFERMATA\n";
        for (auto pr : prenotazioni) {
            file_pr << pr->getCodicePrenotazione() << ";" << pr->getCliente()->getCodiceCliente() << ";" <<
            pr->getPacchetto()->getCodicePacchetto() << ";" << pr->isConfermata() << "\n";
        }
    }
    file_pr.close();
    cout << "Dati salvati con successo.\n";
}

void GestoreAgenzia::caricaDatiDaFile() {
    ifstream file_p("pacchetti_agenzia.txt");
    if (!file_p.is_open()) {
        cout << "Errore nell'apertura del file pacchetti\n";
    } 
    else {
        for (auto p : catalogo) delete p; // prima di caricare i nuovi dati, svuotiamo catalogo, clienti e prenotazioni
        for (auto c : clienti) delete c;
        for (auto pr : prenotazioni) delete pr;
        catalogo.clear();
        clienti.clear();
        prenotazioni.clear();
        prossimoCodicePacchetto = 1; // reinizializziamo a 1 i codici dei pacchetti
        prossimoCodiceCliente = 1;
        prossimoCodicePrenotazione = 1;
        string line = "";
        getline(file_p, line); // Salta intestazione
        while (getline(file_p, line)) {
            string tipo, cod, dest, durata, prezzo, disp, spec1, spec2, spec3;
            
            tipo = line.substr(0, line.find(";"));
            line = line.substr(tipo.length() + 1);

            cod = line.substr(0, line.find(";"));
            line = line.substr(cod.length() + 1);

            dest = line.substr(0, line.find(";"));
            line = line.substr(dest.length() + 1);

            durata = line.substr(0, line.find(";"));
            line = line.substr(durata.length() + 1);

            prezzo = line.substr(0, line.find(";"));
            line = line.substr(prezzo.length() + 1);

            disp = line.substr(0, line.find(";")); 
            line = line.substr(disp.length() + 1);

            if (tipo == "Citta") {
                spec1 = line.substr(0, line.find(";")); // musei
                line = line.substr(spec1.length() + 1);
                spec2 = line.substr(0, line.find(";")); // guida
                line = line.substr(spec2.length() + 1);
                spec3 = line; // hotel
                catalogo.push_back(new PacchettoCitta(cod, dest, stoi(durata), stod(prezzo), stoi(spec1), stoi(spec2), spec3));
            } 
            else if (tipo == "Mare") {
                spec1 = line.substr(0, line.find(";")); // ombrellone
                line = line.substr(spec1.length() + 1);
                spec2 = line.substr(0, line.find(";")); // trattamento
                line = line.substr(spec2.length() + 1);
                spec3 = line; // attrezzi
                catalogo.push_back(new PacchettoMare(cod, dest, stoi(durata), stod(prezzo), stoi(spec1), spec2, stoi(spec3)));
            }
            else if (tipo == "Montagna") {
                spec1 = line.substr(0, line.find(";")); // skipass
                line = line.substr(spec1.length() + 1);
                spec2 = line.substr(0, line.find(";")); // escursioni
                line = line.substr(spec2.length() + 1);
                spec3 = line; // difficolta
                catalogo.push_back(new PacchettoMontagna(cod, dest, stoi(durata), stod(prezzo), stoi(spec1), stoi(spec2), spec3));
            }
            else if (tipo == "Avventura") {
                spec1 = line.substr(0, line.find(";")); // attività (separate da |)
                line = line.substr(spec1.length() + 1);
                spec2 = line.substr(0, line.find(";")); // adrenalina
                line = line.substr(spec2.length() + 1);
                spec3 = line; // assicurazione
                
                vector<string> att;
                int pos = spec1.find("|");
                while (pos != -1) {
                    att.push_back(spec1.substr(0, pos));
                    spec1 = spec1.substr(pos + 1);
                    pos = spec1.find("|");
                }
                att.push_back(spec1);
                
                catalogo.push_back(new PacchettoAvventura(cod, dest, stoi(durata), stod(prezzo), att, spec2, stoi(spec3)));
            }
        }
        file_p.close();
    }

    ifstream file_c("clienti_agenzia.txt");
    if (!file_c.is_open()) cout << "Errore nell'apertura del file clienti\n"; 
    else {
        string line = "";
        getline(file_c, line); 
        while (getline(file_c, line)){
            string cod, nome, cognome, email, telefono, eta, tipo;
            cod = line.substr(0, 8);
            line = line.substr(cod.length() + 1);

            nome = line.substr(0, line.find(" "));
            line = line.substr(nome.length() + 1);

            cognome = line.substr(0, line.find(";"));  
            line = line.substr(cognome.length() + 1);

            email = line.substr(0, line.find(";"));
            line = line.substr(email.length() + 1);

            telefono = line.substr(0, line.find(";"));
            line = line.substr(telefono.length() + 1);
            eta = line.substr(0, line.find(";"));
            line = line.substr(eta.length() + 1);

            tipo = line.substr(0, line.length());
            clienti.push_back(new Cliente(cod, nome, cognome, email, telefono, stoi(eta), tipo));
        }
        file_c.close();
    }
    ifstream file_pr("prenotazioni_agenzia.txt");
    if (!file_pr.is_open()) cout << "Errore nell'apertura del file prenotazioni\n"; 
    else {
        string line = "";
        getline(file_pr, line); 
        while (getline(file_pr, line)) {
            string codB, codC, codP, persone, confermata;

            codB = line.substr(0, line.find(";"));
            line = line.substr(codB.length() + 1);

            codC = line.substr(0, line.find(";"));
            line = line.substr(codC.length() + 1);

            codP = line.substr(0, line.find(";"));
            line = line.substr(codP.length() + 1);

            persone = line.substr(0, line.find(";"));

            confermata = line.substr(persone.length());

            Cliente* cli = cercaCliente(codC);
            PacchettoViaggio* pac = cercaPacchetto(codP);
            Prenotazione* pr = new Prenotazione(codB, cli, pac, stoi(persone));
            if (confermata == "1") pr->confermaPrenotazione();
            prenotazioni.push_back(pr);
        }
        file_pr.close();
        cout << "File caricati con successo";
    }
}