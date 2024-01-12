#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// =================================================================
// ======================= Globala variabler =======================
// =================================================================
string path = "/Users/filipsjostrand/Documents/sommarkurser/uppsala/filer/";

// =================================================================
// ======================== Klassdefinition ========================
// =================================================================
class Transaktion
{
private:
    string  datum;
    string  typ;
    string  namn;
    double  belopp;
    int     antal_kompisar;
    string *kompisar;
    
public:
    Transaktion();
    ~Transaktion();
    Transaktion& operator=( const Transaktion& t);
    string hamtaNamn() const;
    double hamtaBelopp() const;
    int    hamtaAntalKompisar() const;
    bool   finnsKompis(const string &namnet) const;
    bool   lasIn(istream &is);
    void   skrivUt(ostream &os) const;
    void   skrivTitel(ostream &os) const;
    string hamtaKompis(int index) const;
};

class Person
{
private:
    string namn;
    double betalat_andras; // ligger ute med totalt
    double skyldig;        // skyldig totalt
    
public:
    Person();
    Person(const string &namn, double betalat_andras, double skyldig);
    string hamtaNamn();
    double hamtaBetalat();
    double hamtaSkyldig();
    void   skrivUt(ostream &os);
};

class PersonLista
{
private:
    int     antal_personer;
    Person *personer;
    
public:
    PersonLista();
    ~PersonLista();
    void   laggTill(Person ny_person);
    void   skrivUtOchFixa(ostream &os);
    double summaSkyldig() const;
    double summaBetalat() const;
    bool   finnsPerson(const string &namn);
};


class TransaktionsLista
{
private:
    int          antal_transaktioner;
    Transaktion *transaktioner;
    
public:
    TransaktionsLista();
    ~TransaktionsLista();
    void   lasIn(istream & is);
    void   skrivUt(ostream & os);
    void   laggTill(Transaktion & t);
    double totalKostnad() const;
    double liggerUteMed(const string &namnet);
    double arSkyldig(const string &namnet);
    PersonLista fixaPersoner();
};

// =================================================================
// ========================== Mainprogram ==========================
// =================================================================
int main()
{
    cout << "Startar med att läsa från en fil." << endl;
    
    TransaktionsLista transaktioner;
    std::ifstream     is(path.append("resa.txt"));
    transaktioner.lasIn(is);
    
    int operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Välj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Läs in en transaktion från tangentbordet." << endl;
        cout << "3. Beräkna totala kostnaden." << endl;
        cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;
        
        cin >> operation;
        cout << endl;
        
        switch (operation)
        {
            case 1:
            {
                transaktioner.skrivUt(cout);
                break;
            }
            case 2:
            {
                Transaktion transaktion;
                cout << "Ange transaktion i följande format" << endl;
                transaktion.skrivTitel(cout);
                transaktion.lasIn(cin);
                transaktioner.laggTill(transaktion);
                break;
            }
            case 3:
            {
                cout << "Den totala kostnanden för resan var "
                << transaktioner.totalKostnad() << endl;
                break;
            }
            case 4:
            {
                cout << "Ange personen: ";
                string namn;
                cin >> namn;
                double ar_skyldig = transaktioner.arSkyldig(namn);
                if (ar_skyldig == 0.)
                    cout << "Kan inte hitta personen " << namn << endl;
                else
                    cout << namn << " är skyldig " << ar_skyldig << endl;
                break;
            }
            case 5:
            {
                cout << "Ange personen: ";
                string namn;
                cin >> namn;
                double ligger_ute_med = transaktioner.liggerUteMed(namn);
                if (ligger_ute_med == 0.)
                    cout << "Kan inte hitta personen " << namn << endl;
                else
                    cout << namn << " ligger ute med " << ligger_ute_med << endl;
                break;
            }
            case 6:
            {
                cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
                PersonLista lista = transaktioner.fixaPersoner();
                lista.skrivUtOchFixa(cout);
                break;
            }
        }
    }
    
    std::ofstream os(path.append("transaktioner.txt"));
    transaktioner.skrivUt(os);
    
    return 0;
}

// =================================================================
// ============================ Metoder ============================
// =================================================================

// ---------- Transaktion ----------
Transaktion::Transaktion(): antal_kompisar(0), kompisar(0) {
    //
    // Standardkonstruktor
    //
    
}

Transaktion::~Transaktion() {
    //
    // Destruktor
    //
    delete[] kompisar;
    
}

Transaktion& Transaktion::operator=(const Transaktion& t)
{
    if (this != &t)
    {
        if (kompisar != 0)
        {
            delete[] kompisar;
        }
        
        datum = t.datum;
        typ = t.typ;
        namn = t.namn;
        belopp = t.belopp;
        antal_kompisar = t.antal_kompisar;
        
        if (antal_kompisar > 0)
        {
            kompisar = new string[antal_kompisar];
            for (int i = 0; i < antal_kompisar; i++)
                kompisar[i] = t.kompisar[i];
        }
        else
        {
            kompisar = nullptr;
        }
    }
    return *this;
}


string Transaktion::hamtaNamn() const {
    //
    // Getter för namn på den som lagt ut.
    //
    return namn;
}

double Transaktion::hamtaBelopp() const {
    //
    // Getter för det belopp som lagts ut.
    //
    return belopp;
}

int Transaktion::hamtaAntalKompisar() const {
    //
    // Getter för antal människor som delat på transaktionen.
    //
    return antal_kompisar;
}

string Transaktion::hamtaKompis(int index) const {
    //
    // Getter för kompisars namn.
    //
    if (index >= 0 && index < antal_kompisar) {
        return kompisar[index];
    }
    
    return "";
}


bool Transaktion::finnsKompis(const string &namnet) const {
    //
    // Går igenom alla namnen på de skyldiga i en transaktion och jämför med ett givet namne.
    // Om namnet finns med, returnera sant, annars falskt.
    //
    for (int i = 0; i < antal_kompisar; i++) {
        if (namnet == kompisar[i]) {
            return true;
        }
    }
    return false;
}

bool Transaktion::lasIn(istream &is) {
    //
    // Läser in en transaktion från fil eller inmatning. Fortsätter tills filen är slut.
    //
    is >> datum >> typ >> namn >> belopp >> antal_kompisar;
    
    delete[] kompisar;
    kompisar = new string[antal_kompisar];
    
    for (int i = 0; i < antal_kompisar; i++) {
        is >> kompisar[i];
    }
    
    return !is.eof();
}

void Transaktion::skrivUt(ostream &os) const {
    //
    // Skriver ut information om en transaktion. Antigen till fil eller till konsol.
    //
    os << setfill(' ') << setiosflags(ios::left)
    << setw(10) << datum
    << setw(10) << typ
    << setw(10) << namn
    << setw(10) << belopp
    << setw(10) << antal_kompisar;
    
    
    for (int i = 0; i< antal_kompisar; i++) {
        os << setfill(' ') << setiosflags(ios::left) << setw(10) << kompisar[i];
    }
    os << endl;
    
}

void Transaktion::skrivTitel(ostream &os) const {
    //
    // En "header" för transaktionstabellen.
    //
    os << setfill(' ') << setiosflags(ios::left)
    << setw(10) << "Datum"
    << setw(10) << "Typ"
    << setw(10) << "Namn"
    << setw(10) << "Belopp"
    << setw(10) << "Antal och lista av kompisar"
    << endl;
}

// ---------- Person ----------
Person::Person() {
    //
    // Standardkonstruktor.
    //
}

Person::Person(const string &namn, double betalat_andras, double skyldig) {
    //
    // Extrakonstruktor.
    //
    this->namn = namn;
    this->betalat_andras = betalat_andras;
    this->skyldig = skyldig;
}

string Person::hamtaNamn() {
    //
    // Getter för personnens namn.
    //
    return namn;
}

double Person::hamtaBetalat() {
    //
    // Getter för personnens utlägg.
    //
    return betalat_andras;
}

double Person::hamtaSkyldig() {
    //
    // Getter för personnens skulder.
    //
    return skyldig;
    
}

void   Person::skrivUt(ostream &os) {
    //
    // Information om namn, skuld, utlägg, och netto in/utbetalning från "transaktionspotten".
    //
    double netto;
    
    netto = betalat_andras - skyldig;
    
    os << namn
    << " ligger ute med " << betalat_andras
    << " och är skyldig "  << skyldig;
    if (netto == 0) {
        os << ". Skall inta ha någonting från potten!" << endl;
    } else {
        if (netto > 0) {
            os << ". Skall ha " << netto << " från potten!" << endl;
        } else {
            os << ". Skall lägga " << -netto << " till potten!" << endl;
        }
    }
}

// ---------- Personlista ----------
PersonLista::PersonLista() : antal_personer(0), personer(0) {
    //
    // Standardkonstruktor
    //
}

PersonLista::~PersonLista() {
    //
    // Destruktor
    //
    delete[] personer;
}

void PersonLista::laggTill(Person ny_person) {
    //
    // Adderar en till person till listan.
    //
    Person *tempArr = new Person[antal_personer + 1];
    
    for (int i = 0; i < antal_personer; i++) {
        tempArr[i] = personer[i];
    }
    
    tempArr[antal_personer] = ny_person;
    delete[] personer;
    personer = tempArr;
    antal_personer++;
}

void PersonLista::skrivUtOchFixa(ostream &os) {
    //
    //
    //
    
    for (int i = 0; i < antal_personer; i++) {
        personer[i].skrivUt(os);
    }
    
    double diff = summaBetalat() - summaSkyldig();
    if (diff != 0) {
        cout << "FELBERÄKNINGAR!" << " Nettopotten ligger på: " << diff << endl;
    }
}

double PersonLista::summaSkyldig() const {
    //
    // Finner den kumulativa skulden.
    //
    double skulder = 0.0;
    
    for (int i = 0; i < antal_personer; i++) {
        skulder += personer[i].hamtaSkyldig();
    }
    
    return skulder;
}

double PersonLista::summaBetalat() const {
    //
    // Finner det kumulativa utlägget.
    //
    double betalat = 0.0;
    
    for (int i = 0; i < antal_personer; i++) {
        betalat += personer[i].hamtaBetalat();
    }
    
    return betalat;
}

bool PersonLista::finnsPerson(const string& namn) {
    //
    // Går igenom alla namnen på alla i personlistan, jämför med angivet.
    // Om namnet finns med, returnera sant, annars falskt.
    //
    for (int i = 0; i < antal_personer; i++) {
        if (namn == personer[i].hamtaNamn()) {
            return true;
        }
    }
    return false;
}

// ---------- TransaktionsLista ----------
TransaktionsLista::TransaktionsLista() : antal_transaktioner(0), transaktioner(0) {
    //
    // Standardkonstruktor
    //
}

TransaktionsLista::~TransaktionsLista(){
    //
    // Destruktor
    //
    delete[] transaktioner;
}

void TransaktionsLista::lasIn(istream & is) {
    //
    // Läser in från fil och lagrar alla transaktioner i en array. Beräknar antalet transaktioner.
    //
    Transaktion enTransaktion;
    
    while (enTransaktion.lasIn(is)) {
        if (antal_transaktioner == 0) {
            transaktioner = new Transaktion[1];
        } else {
            Transaktion *temp = new Transaktion[antal_transaktioner + 1];
            for (int i = 0; i < antal_transaktioner; i++) {
                temp[i] = transaktioner[i];
            }
            delete[] transaktioner;
            transaktioner = temp;
        }
        
        transaktioner[antal_transaktioner] = enTransaktion;
        antal_transaktioner++;
    }
}

void TransaktionsLista::skrivUt(ostream & os) {
    //
    // Skriver ut transaktionstabellen till fil eller konsol.
    //
    transaktioner[1].skrivTitel(os);
    
    for (int i = 0; i < antal_transaktioner; i++) {
        transaktioner[i].skrivUt(os);
    }
}

void TransaktionsLista::laggTill(Transaktion & t) {
    Transaktion *tempArr = new Transaktion[antal_transaktioner + 1];
    
    for (int i = 0; i < antal_transaktioner; i++) {
        tempArr[i] = transaktioner[i];
    }
    
    tempArr[antal_transaktioner] = t;
    delete[] transaktioner;
    transaktioner = tempArr;
    antal_transaktioner++;
}

double TransaktionsLista::totalKostnad() const {
    //
    // Summerar alla transaktionsutlägg.
    //
    double summa = 0;
    
    for (int i = 0; i < antal_transaktioner; i++) {
        summa += transaktioner[i].hamtaBelopp();
    }
    
    return summa;
}

double TransaktionsLista::liggerUteMed(const string &namnet)
{
    //
    // Beräknar summan som en person ligger ute för andra med.
    // Söker igenom alla transaktioner och jämför med ett givet namn.
    // Om namnet matchar, tar summan, drar av deras egna andel,
    // och adderar till "potten" av vad hen har lagt ut.
    //
    double summa = 0.;
    
    for (int i = 0; i < antal_transaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namnet)
            summa += transaktioner[i].hamtaBelopp() *
            (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
    
    return summa;
}

double TransaktionsLista::arSkyldig(const string &namnet) {
    //
    // Beräknar den kumulerade skulden en given person har.
    // likt `liggerUteMed()`, söker metoden igenom transaktioner och jämför med givet namn i listan av kompisar.
    // Om match, adderar en andel i "potten" av totala skulder.
    //
    double summa = 0.;
    
    for (int i = 0; i < antal_transaktioner; i++) {
        if (transaktioner[i].finnsKompis(namnet)) {
            summa += transaktioner[i].hamtaBelopp() *
            (1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
        }
    }
    
    return summa;
}

PersonLista TransaktionsLista::fixaPersoner() {
    //
    // Skapar och returnerar en lista av unika personer som förekommer
    // i transaktionerna. För varje person beräknas hur mycket hen ligger
    // ute med samt hur mycket hon är skyldig.
    //
    PersonLista persList;
    
    for (int i = 0; i < antal_transaktioner; i++) {
        string namn = transaktioner[i].hamtaNamn();
        
        if (!persList.finnsPerson(namn)) {
            double betalat = liggerUteMed(namn);
            double skyldig = arSkyldig(namn);
            Person p(namn, betalat, skyldig);
            persList.laggTill(p);
        }
        
        for (int j = 0; j < transaktioner[i].hamtaAntalKompisar(); j++) {
            string kompisNamn = transaktioner[i].hamtaKompis(j);
            if (!persList.finnsPerson(kompisNamn)) {
                double betalat = liggerUteMed(kompisNamn);
                double skyldig = arSkyldig(kompisNamn);
                Person p(kompisNamn, betalat, skyldig);
                persList.laggTill(p);
            }
        }
    }
    
    return persList;
}
