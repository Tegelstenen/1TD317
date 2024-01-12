#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Person {
public:
    Person( const string& name ) : name(name) {}
    string namnet() const { return name; }
private:
    string name;
};

class Arbetsgivare {
public:
    Arbetsgivare( const string& name) : name( name) {}
    string namnet() const { return name; }
private:
    string name;
};

class Anstallning {
private:
    Person* person;
    Arbetsgivare* arbetsgivare;
public:
    Anstallning();
    Anstallning(Person* p, Arbetsgivare* a);
    string getPerson() const;
    string getArbetsgivare() const;
};

class AnstallningsLista {
private:
    int antal;
    Anstallning** anstallningar;
public:
    AnstallningsLista();
    ~AnstallningsLista();
    void laggIn(const Anstallning& anstallning);
    void listArbetsgivare(ostream& os, Person* p);
    void listAnstallda(ostream& os, Arbetsgivare* a);
};


int main(){
    
    AnstallningsLista anst;
    Person p1("Kalle");
    Person p2("Pelle");
    Person p3("Olle");
    Person p4("Eva");
    Person p5("Stina");
    Arbetsgivare a1( "Uppsala universitet");
    Arbetsgivare a2( "Uppsala kommun");
    Arbetsgivare a3( "Ericsson");
    Arbetsgivare a4( "Microsoft");
    
    anst.laggIn( Anstallning(&p1,&a1) ); // p1 arbetar hos a1
    anst.laggIn( Anstallning(&p2,&a1) );
    anst.laggIn( Anstallning(&p3,&a2) );
    anst.laggIn( Anstallning(&p1,&a3) );
    anst.laggIn( Anstallning(&p3,&a3) );
    
    anst.listArbetsgivare( cout, &p1);  // lista alla Kalles arbetsgivare
    anst.listAnstallda( cout, &a3);     // lista alla Ericsson anställda
    
    return 0;
}


Anstallning::Anstallning() : person(0), arbetsgivare(0) {}

Anstallning::Anstallning(Person* p, Arbetsgivare* a) : person(p), arbetsgivare(a) {}

string Anstallning::getPerson() const {
    return person->namnet();
}

string Anstallning::getArbetsgivare() const {
    return arbetsgivare->namnet();
}


AnstallningsLista::AnstallningsLista(): antal(0), anstallningar(0) {}

AnstallningsLista::~AnstallningsLista() {
    for (int i = 0; i < antal; i++) {
        delete anstallningar[i];
    }
    delete[] anstallningar;
}

void AnstallningsLista::laggIn(const Anstallning& anstallning) {
    Anstallning** tempArr = new Anstallning*[antal + 1];
    for (int i = 0; i < antal; ++i) {
        tempArr[i] = anstallningar[i];
    }
    tempArr[antal] = new Anstallning(anstallning);
    
    delete[] anstallningar;
    
    anstallningar = tempArr;
    antal++;
}

void AnstallningsLista::listArbetsgivare(ostream &os, Person* p) {
    for (int i = 0; i < antal; i++) {
        if (anstallningar[i]->getPerson() == p->namnet()) {
            os << p->namnet() << " jobbar hos " << anstallningar[i]->getArbetsgivare() << endl;
        }
    }
}


void AnstallningsLista::listAnstallda(ostream& os, Arbetsgivare* a) {
    
    
    for (int i = 0; i < antal; i ++) {
        if (anstallningar[i]->getArbetsgivare() == a->namnet()) {
            os << a->namnet() << " har " << anstallningar[i]->getPerson() << " anställd" << endl;;
        }
    }
    
}
