// Program för att testa funktionen skrivInfo

#include <iostream>
using namespace std;

//Deklarationer av funktionerna
void skrivInfo();
int lasEttTal();
char lasOp();
void ordna(int &forsta, int &andra);
int berakna(int undre, int ovre, char operation);
void skrivResultat(int svar);


int main() {
    
    int tal1, tal2, svar;
    char op;
  
    // Skriver ut programinfo.
    skrivInfo();
    
    // Läser in önskade tal och operation.
    tal1 = lasEttTal();
    tal2 = lasEttTal();
    op = lasOp();
    
    // Säkertsäller korrekt ordning av tal.
    ordna(tal1, tal2);
    
    // Utför beräkningar.
    svar = berakna(tal1, tal2, op);
    
    // Printar resultat.
    skrivResultat(svar);
  
  return 0;
  
}

//Definitioner av funktionerna

void skrivInfo() {
    // Skriver ut information om programmet.
    cout << "Programmet tar in två heltal och utför sedan önskad beräkning." << endl;
    cout << "De beräkningar som programmet ska klara av att göra är: " << endl;
    cout << " - Addera" << endl;
    cout << " - Multiplicera" << endl;
    cout << " - Beräkna kvadratsumman" << endl;
    cout << endl;
}

int lasEttTal() {
    // Läser in ett tal.
    int tal;
    
    cout << "Ange ett tal: ";
    cin >> tal;
    
    return tal;
}

char lasOp() {
    // Läser in önskad operation som skall anges på dem två talen.
    // Säkerställer att rätt operation anges.
    char operation;
    bool inkorrekt;
    
    do {
        cout << endl;
        cout << " 'a' = Addera" << endl;
        cout << " 'm' = Multiplicera" << endl;
        cout << " 'k' = Beräkna kvadratsumman" << endl;
        cout << endl;
        
        cout << "Ange en operation: ";
        cin >> operation;
        
        if (operation != 'a' && operation != 'm' && operation != 'k') {
            inkorrekt = true;
            cout << endl;
            cout << "Felaktig inmatning, försök igen." << endl;
            cout << endl;
        } else {
            inkorrekt = false;
        }
        
    } while (inkorrekt);
    
    return operation;
}

void ordna(int &forsta, int &andra) {
    // Ordnar om talen så att det minsta alltid är först.
    if ( forsta > andra ) {
        int temp = forsta;
        forsta = andra;
        andra = temp;
    }
}

int berakna(int undre, int ovre, char operation) {
    // Utför önskade beräkningar.
    // Kontrollerar typ av operation i if statements för att sedan itererat över varje heltal mellan undre och övre.
    int resultat = 0;
    
    if (operation == 'a') {
        // addition
        for (undre; undre <= ovre; undre++) {
            resultat += undre;
        }
        
    } else {
        
        if (operation == 'm') {
            // multiplikation
            resultat = 1;
            for (undre; undre <= ovre; undre++) {
                resultat *= undre;
            }
            
        } else {
            // kvadratstumman
            for (undre; undre <= ovre; undre++) {
                resultat += undre * undre;
            }
        }
    }
    
    return resultat;
}

void skrivResultat(int svar) {
    cout << "Resultatet av beräkningarna är: " << svar << endl;
}









void string_counter(string in_string) {
    // Counts the occurances of letters, numbers, and other characters in a string.
    int letters = 0, numbers = 0, others = 0;
    char tmp;
    
    for (int i = 0; i < in_string.length(); i++) {
        tmp = in_string.at(i);
        
        if(isalpha(tmp)) {
            letters++;
        } else if(isdigit(tmp)) {
            numbers++;
        } else {
            others++;
        }
                  
    }
    
    cout << "letters: " << letters << endl;
    cout << "numbers: " << numbers << endl;
    cout << "others: " << others << endl;
                  
}


void histo(const string &str)
{
  
  // En array f att lagra frekvensen i
  // Antal platser är lika med antalet olika bokstäver
  int f[antalBokstaever];
 
  //Nollställ f:
  for (int i=0; i<antalBokstaever; i++)
    f[i] = 0;
 
  // Loopa igenom hela strängen, tecken för tecken
  for ( int i=0; i< (int) str.length(); i++)
    {
      int index;
 
      // Om tecknet är en gemen
      if (str.at(i)>='a' && str.at(i)<='z')
    {
          // räkna ut platsen i arrayen
      index = str.at(i) - 'a';
          // uppdatera räknaren på rätt plats
      f[index]++;
        }
      
      // Om tecknet är en versal
      if (str.at(i)>='A' && str.at(i)<='Z')
    {
      // räkna ut platsen i arrayen
      index = str.at(i) - 'A';
      // uppdatera räknaren på rätt plats
      f[index]++;
        }
    }
  
  //Skriv ut frekvensen i en tabell
  cout<<"\nBokstav\tFrekvens\n";
  // Loopa över alla platser i arrayen
  for (int i=0; i<antalBokstaever; i++)
    {
      // Konvertera platsen till ett teckenvärde
      char b = char (i+'A');
      if (f[i]) cout << b << "\t" << f[i] <<endl;
    }
}
