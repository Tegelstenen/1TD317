#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
{{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
    7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
    0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
    1.89,0.03},
    {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
        7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
        1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
        0.30,0.15},
    {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
        3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
        0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
        0.45,0.00},
    {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
        8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
        0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
        0.69,1.24}};

//--------------------------------------------------------
// Funktionsdeklarationer:
void berakna_histogram_abs(string str, double x[]);
int abs_till_rel(double x[]);
void plotta_histogram_rel(double x[]);
void tolkning(double x[], int summa);
string namn_pa_fil();
string inlasning(string fil);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
    double frek[ANTAL_BOKSTAVER];
    
    string filnamn = namn_pa_fil();
    
    string straeng = inlasning(filnamn);
    
    berakna_histogram_abs(straeng, frek);
    
    int summa = abs_till_rel(frek);
    
    tolkning(frek, summa);
    
    plotta_histogram_rel(frek);
    
    return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
void berakna_histogram_abs(string str, double x[]) {  // ändra till double
    
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

int abs_till_rel(double x[]) {
    double summa = 0.0;
    
    // Beräknar totala antalet bokstäver räknade.
    for(int i = 0; i < ANTAL_BOKSTAVER; i++) {
        summa = summa + x[i];
    }
    
    // Beräknar proportioner.
    for(int i = 0; i < ANTAL_BOKSTAVER; i++) {
        x[i] = 100.0 * x[i] / summa;
    }
    
    return  summa;
    
}

void plotta_histogram_rel(double x[]) {
    
    cout << "Bokstavsfördelning:" << endl;
    
    // Skriver ut med start från ASCII 65 ("A").
    for (int i = 0; i < ANTAL_BOKSTAVER; i++) {
        
        cout << char(i + 65) << ": ";
        
        // Dubblar procentsatsen, skriver ut så många "*"
        int j = 0;
        while (j < floor(x[i] / 0.5)) {
            cout << "*";
            j++;
        }
        cout << endl;
        
    }
}

void tolkning(double x[], int summa) {
    double kvadratsumman[ANTAL_SPRAK];
    string spraak[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};
    
    // Nollställ.
    for (int i = 0; i < ANTAL_SPRAK; i++) {
        kvadratsumman[i] = 0;
    }
    
    // Itererar över alla språk.
    for (int i = 0; i < ANTAL_SPRAK; i++) {
        
        for (int j = 0; j < ANTAL_BOKSTAVER; j++) {
            kvadratsumman[i] = (x[j] - TOLK_HJALP[i][j])*(x[j] - TOLK_HJALP[i][j]) + kvadratsumman[i];
        }
    }
    
    // Hittar minvärdet.
    int min = kvadratsumman[0], min_index = 0;
    for (int i = 1; i < ANTAL_SPRAK; i++) {
        if (kvadratsumman[i] < min) {
            min = kvadratsumman[i];
            min_index = i;
        }
    }
    
    // Utskrift av jämförelse.
    cout << endl;
    cout << "Resultat för bokstäverna A-Z" << endl;
    cout << endl;
    
    cout << "Totala antalet bokstäver: " << summa << endl;
    
    for (int i = 0; i < ANTAL_SPRAK; i++) {
        cout << spraak[i] << " har kvadratsumma =  " << kvadratsumman[i] << endl;
    }
    
    cout << "Det är mest troligt att språket är " << spraak[min_index] << endl;
    cout << endl;
}

string namn_pa_fil() {
    string namn;
    
    // Matar in namnet på filen.
    cout << "Ange ett filnamn: " << endl;
    getline(cin, namn);
    
    // Korrektion av filtyp.
    long suffix = namn.rfind(".txt");
    if (suffix == -1) {
        namn.append(".txt");
    }
    
    return namn;
}

string inlasning(string fil) {
    ifstream fin(fil.c_str());
    char c;
    string inlaest;
    
    // Felkontroll
    if (!fin) {
        cout << "Det finns ingen fil med namnet " << fil << endl;
        exit(EXIT_FAILURE);
    }
    
    // läs tecken för tecken och lägg till sist in strängen.
    while (fin.get(c))
    {
        inlaest.push_back(c);
    }
    
    return inlaest;
}



