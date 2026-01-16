#include <iostream>
#include <string>
#include "include/GestoreAgenzia.h"
#include "include/Utils.h"

using namespace std;

int main() {
    GestoreAgenzia agenzia; 
    int scelta;

    do {
        cout << "\n=== SISTEMA GESTIONE AGENZIA VIAGGI ===\n";
        
        cout << "\n--- GESTIONE CATALOGO PACCHETTI ---\n";
        cout << "1. Aggiungi nuovo pacchetto\n";
        cout << "2. Visualizza tutti i pacchetti\n"; 
        cout << "3. Cerca pacchetto per codice\n"; 
        cout << "4. Visualizza pacchetti per tipologia\n"; 
        cout << "5. Visualizza solo pacchetti disponibili\n"; 

        cout << "\n--- GESTIONE CLIENTI ---\n";
        cout << "6. Registra nuovo cliente\n"; 
        cout << "7. Visualizza tutti i clienti\n"; 
        cout << "8. Cerca cliente per codice\n"; 
        cout << "9. Visualizza clienti per tipologia\n"; 

        cout << "\n--- GESTIONE PRENOTAZIONI ---\n";
        cout << "10. Crea nuova prenotazione\n"; 
        cout << "11. Conferma prenotazione\n";
        cout << "12. Visualizza tutte le prenotazioni\n";
        cout << "13. Visualizza prenotazioni di un cliente\n";
        cout << "14. Visualizza prenotazioni confermate\n"; 

        cout << "\n--- STATISTICHE E REPORT ---\n";
        cout << "15. Statistiche generali\n"; 
        cout << "16. Statistiche per tipologia pacchetto\n"; 
        cout << "17. Trova cliente migliore (maggior spesa)\n";
        cout << "18. Report destinazioni più popolari\n"; 

        cout << "\n--- GESTIONE FILE ---\n";
        cout << "19. Salva dati su file\n";
        cout << "20. Carica dati da file\n";
        cout << "21. Esci\n"; 

        cout << "\nSeleziona un'opzione: ";
        cin >> scelta;

        switch (scelta) {
            case 1:
                agenzia.aggiungiPacchettoManuale(); 
                break;
            case 2:
                agenzia.visualizzaCatalogo(); 
                break;
            case 3: {
                cout << "Inserisci codice pacchetto da cercare: ";
                string codice;
                cin >> codice;
                PacchettoViaggio* p = agenzia.cercaPacchetto(codice);
                if (p == nullptr) cout << "Pacchetto non trovato!\n";
                else p->stampaDettagli();
                break; }
            case 4:
                agenzia.visualizzaPacchettiXTipo(); 
                break;
            case 5:
                agenzia.visualizzaPacchettiDisponibili(); 
                break;
            case 6:
                agenzia.aggiungiCliente(); 
                break;
            case 7:
                agenzia.visualizzaClienti(); 
                break;
            case 8: {
                cout << "Inserisci codice cliente da cercare: ";
                string codice;
                cin >> codice;
                Cliente* c = agenzia.cercaCliente(codice);
                if (c == nullptr) cout << "Cliente non trovato!\n";
                else c->stampaInfo();
                break; } 
            case 9:
                agenzia.visualizzaClientiXTipo(); 
                break;
            case 10:
                agenzia.creaPrenotazione(); 
                break;
            case 11: {
                cout << "Inserisci codice prenotazione da confermare: ";
                string codice;
                cin >> codice;
                Prenotazione* pr = agenzia.cercaPrenotazione(codice);
                if (pr == nullptr) cout << "Prenotazione non trovata!\n";
                else {
                    pr->confermaPrenotazione();
                    cout << "Prenotazione confermata con successo\n";
                }
                break; } 
            case 12:
                 agenzia.visualizzaPrenotazioni();
                break;
            case 13: {
                cout << "Inserisci codice cliente di cui vuoi sapere le prenotazioni: ";
                string codice;
                cin >> codice;
                if (agenzia.cercaCliente(codice) == nullptr) cout << "Cliente non trovato!\n";
                else agenzia.visualizzaPrenotazioniCliente(codice);
                break; }
            case 14:
                agenzia.visualizzaPrenotazioniConfermate(); 
                break;
            case 15:
                agenzia.statisticheGenerali();
                break;
            case 16:
                 agenzia.statistichePerTipologia(); 
                break;
            case 17: {
                Cliente* migliorCli = agenzia.clienteMigliore();
                if (migliorCli != nullptr) {
                    cout << "\n=== RISULTATO RICERCA MIGLIOR CLIENTE ===\n";
                    cout << "Il cliente che ha speso di piu' e': " << migliorCli->getNomeCompleto() << endl;
                } 
                else {
                    cout << "\nNessun cliente trovato o nessuna prenotazione confermata presente.\n";
                }
                break; }
            case 18:
                agenzia.reportDestinazioni();
                break;
            case 19:
                cout << "Sei sicuro di voler salvare? I file verranno sovrascritti\n(1:si, 0:no)";
                bool save;
                cin >> save;
                if (!save) continue;
                agenzia.salvaDatiSuFile(); 
                break;
            case 20:
                agenzia.caricaDatiDaFile(); 
                break;
            case 21:
                cout << "Uscita dal sistema. Arrivederci!\n";
                break;
            default:
                cout << "Opzione non valida. Riprova.\n";
        }
    } while (scelta != 21);

    return 0;
}