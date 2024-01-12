#include <iostream>
using namespace std;

int main()
{
    int startnummer, starttim, startmin, startsek, stoptim, stopmin, stopsek;
    int ledande_nummer = 0, ledande_seks = 999999999, antal = 0;
    
    // Repeterar tills startnummer är mindre eller lika med noll.
    do {
        cout << "Startnummer? ";
        cin >> startnummer;
        
        // Ifall startnummer inte upfyller, hoppa över resterande inläsning och loopen avbryts.
        if (startnummer > 0) {
            cout << "Starttid? ";
            cin >> starttim >> startmin >> startsek;
            
            cout << "Måltid? ";
            cin >> stoptim >> stopmin >> stopsek;
            
            // Omvandlar till sekunder för enkel jämförelse.
            int startsekunder, stopsekunder;
            
            startsekunder = starttim*3600 + startmin*60 + startsek;
            stopsekunder = stoptim*3600 + stopmin*60 + stopsek;

            if (stopsekunder < startsekunder) { // Hantering för om stoptiden är nästa dag.
                stopsekunder += 24 * 3600;
                }
            
            int diffen = stopsekunder - startsekunder;
            
            // Är tiden snabbare än föregående? I så fall, ersätt som ledande löpare.
            if (diffen < ledande_seks) {
                ledande_nummer = startnummer;
                ledande_seks = diffen;
            }
            antal++;
        }
        
    } while (startnummer > 0);
    
    // När alla löpare är inlästa, omvandlar ledande till rätt format igen.
    // Använder modulo för att finna antalet hela timmar och minuter.
    int timmen = ledande_seks / 3600;
    ledande_seks %= 3600;
    int minuten = ledande_seks / 60;
    int sekunden = ledande_seks % 60;
    
    // Utskrift för resultat.
    if (antal == 0) {
        cout << "Inga tävlande" << endl;
    } else {
        cout << "Vinnare är startnr: " << ledande_nummer << endl;
        cout << "Tim: " << timmen << " Min: " << minuten << " Sek: " << sekunden << endl;
        cout << "Antal tävlande: " << antal << endl;
    }
    
    cout << "Programmet avslutas" << endl;
    
    return 0;
}

