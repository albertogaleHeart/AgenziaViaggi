#ifndef GESTOREAGENZIA_H
#define GESTOREAGENZIA_H

#include <string>
#include <vector>
#include "Cliente.h"
#include "PacchettoViaggio.h"
#include "Prenotazione.h"


class GestoreAgenzia{
private:
    std::vector<PacchettoViaggio*> catalogo; // Tutti i pacchetti disponibili
    std::vector<Cliente*> clienti; // Tutti i clienti registrati
    std::vector<Prenotazione*> prenotazioni; // Tutte le prenotazioni
    int prossimoCodicePacchetto; // Per generare codici univoci
    int prossimoCodiceCliente; 
    int prossimoCodicePrenotazione; 

public:
    // Costruttore e Distruttore
    GestoreAgenzia();
    ~GestoreAgenzia(); // Deve liberare TUTTA la memoria allocata!


    // === GESTIONE PACCHETTI ===
    void aggiungiPacchettoManuale(); // Chiede dati da tastiera
    PacchettoViaggio* cercaPacchetto(std::string codice);
    void visualizzaCatalogo() const;
    void visualizzaPacchettiXTipo() const;
    void visualizzaPacchettiDisponibili() const;


    // === GESTIONE CLIENTI ===
    void aggiungiCliente();
    Cliente* cercaCliente(std::string codice);
    void visualizzaClienti() const;
    void visualizzaClientiXTipo() const;


    // === GESTIONE PRENOTAZIONI ===
    void creaPrenotazione(); // Chiede codice cliente e codice pacchetto
    Prenotazione* cercaPrenotazione(std::string codice);
    void confermaPrenotazione(std::string codicePrenotazione);
    void visualizzaPrenotazioni() const;
    void visualizzaPrenotazioniCliente(std::string codiceCliente) const;
    void visualizzaPrenotazioniConfermate() const;


    // === STATISTICHE ===
    void statisticheGenerali() const;
    // - Numero totale pacchetti
    // - Numero totale clienti
    // - Numero totale prenotazioni
    // - Fatturato totale
    // - Pacchetto più prenotato
    // - Destinazione più popolare
    void statistichePerTipologia() const;
    // Conteggio prenotazioni per ogni tipo di pacchetto
    Cliente* clienteMigliore() const;
    // Cliente con maggior spesa totale
    void reportDestinazioni() const;


    // === GESTIONE FILE ===
    void salvaDatiSuFile() const;
    void caricaDatiDaFile();
    // Usa formato testo (CSV o simile) per semplicità
    // === UTILITY ===
    std::string generaCodiceUnico(char tipo);
    // 'P' per pacchetti, 'C' per clienti, 'B' per prenotazioni

};

#endif