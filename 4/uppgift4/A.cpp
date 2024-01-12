#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;

//--------------------------------------------------------
// Funktionsdeklarationer:
void berakna_histogram_abs(string str, int x[]);
void skriv_histogram_abs(int x[]);

//--------------------------------------------------------
// Huvudprogram:
int main()
{
    // Deklarera variabler
    int frek[ANTAL_BOKSTAVER];
    string rad;
    
    // Läs in en rad med text från tangentbordet
    cout << "Ange en rad: ";
    getline(cin, rad);
    
    // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
    // och antalet bokst‰ver.
    berakna_histogram_abs(rad, frek);
    
    // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
    skriv_histogram_abs(frek);
    
    return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
void berakna_histogram_abs(string str, int x[]) {

    // Nollställ histogrammet.
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        x[i] = 0;
    }
    
    // Säkerställer att allting är gemener.
    for (int i = 0; i < str.length(); i++) {
        str.at(i) = tolower(str.at(i));
    }
    
    // Räknar antal.
    for (int i = 0; i < str.length(); i++) {
        int position = int(str.at(i)) - 97;
        x[position]++;
    }
}

void skriv_histogram_abs(int x[]) {
    
    // Skriver ut med start från ASCII 65 ("A").
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        cout << char(i + 65) << ": " << x[i] << endl;
    }
    
}

namn_pa_fil(...)

// Redovisning av uppgiften i ord.

