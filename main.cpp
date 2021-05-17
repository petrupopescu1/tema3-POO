#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

bool an_bisect(int an)
{
    if(an % 4 == 0)
    {
        if(an % 100 == 0)
        {
            if(an % 400 == 0)
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}


class Persoana
{
private:
    string nume, cnp;
public:
    void set_cnp(string cnp);
    void set_nume(string nume);
    string get_cnp();
    string get_nume();
    int calculVarsta();
    virtual bool verificare();
    Persoana();
    Persoana(string cnp, string nume);
    Persoana(const Persoana &persoana);
    ~Persoana();
    friend istream& operator>>(istream &in, Persoana &persoana);
    friend ostream& operator<<(ostream &out, Persoana &persoana);
    Persoana operator=(Persoana persoana);
};

bool Persoana :: verificare()
{
    try
    {
        int  l = cnp.length();
        for(int i = 0; i < l; i++)
        {
            if(cnp[i] < '0' || cnp[i] > '9')
            {
                throw -1;
            }
        }
        if(l != 13)
        {
            throw -1;
        }
        time_t acum = time(0);
        tm* data_curenta = localtime(&acum);
        int an_curent = data_curenta->tm_year + 1900;
        string an_nastereaux = cnp.substr(1,2);
        if(an_nastereaux <= to_string(an_curent - 2000))
        {
            an_nastereaux = "20" + an_nastereaux;
        }
        else
        {
            an_nastereaux = "19" + an_nastereaux;
        }
        string luna_nastereaux = cnp.substr(3,2);
        if(luna_nastereaux < "10")
        {
            luna_nastereaux = luna_nastereaux.substr(1,1);
        }
        string zi_nastereaux = cnp.substr(5,2);
        if(zi_nastereaux < "10")
        {
            zi_nastereaux = zi_nastereaux.substr(1,1);
        }
        int an_nastere = stoi(an_nastereaux);
        int luna_nastere = stoi(luna_nastereaux);
        int zi_nastere = stoi(zi_nastereaux);
        if(luna_nastere < 1 || luna_nastere > 12)
        {
            throw -1;
        }
        switch(luna_nastere)
        {
        case 2:
            if(an_bisect(an_nastere))
            {
                if(zi_nastere < 1 || zi_nastere > 29)
                {
                    throw -1;
                }
            }
            else
            {
                if(zi_nastere < 1 || zi_nastere > 28)
                {
                    throw -1;
                }
            }
            break;
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if(zi_nastere < 1 || zi_nastere > 31)
            {
                throw -1;
            }
            break;
        default:
            if(zi_nastere < 1 || zi_nastere > 30)
            {
                throw -1;
            }
            break;
        }
    }
    catch(...)
    {
        cout << "CNP invalid";
        return false;
    }
    return true;
}

Persoana :: Persoana()
{
    nume = "";
    cnp = "1111111111111";
}

Persoana :: Persoana(string cnp, string nume)
{
    if(!this->Persoana::verificare())
    {
        exit(0);
    }
    this->cnp = cnp;
    this-> nume = nume;
}

Persoana :: Persoana(const Persoana &persoana)
{
    this->nume = persoana.nume;
    this->cnp = persoana.cnp;
}

Persoana :: ~Persoana()
{

}

string Persoana :: get_cnp()
{
    return this->cnp;
}

string Persoana :: get_nume()
{
    return this->nume;
}

void Persoana :: set_cnp(string cnp)
{
    this->cnp = cnp;
}

void Persoana :: set_nume(string nume)
{
    this->nume = nume;
}

istream& operator>>(istream &in, Persoana &persoana)
{
    cout << "Introduceti CNP\n";
    in >> persoana.cnp;
    cout << "Introduceti nume\n";
    in >> persoana.nume;
    if(!persoana.Persoana::verificare())
    {
        exit(0);
    }
    return in;
}

ostream &operator<<(ostream &out, Persoana &persoana)
{
    out << "CNP: " << persoana.cnp << '\n';
    out << "Nume: " << persoana.nume << '\n';
    return out;
}

Persoana Persoana :: operator=(Persoana persoana)
{
    this->cnp = persoana.cnp;
    this->nume = persoana.nume;
    return *this;
}

int Persoana :: calculVarsta()
{
    time_t acum = time(0);
    tm* data_curenta = localtime(&acum);
    int an_curent = data_curenta->tm_year + 1900;
    int luna_curenta = data_curenta->tm_mon + 1;
    int zi_curenta = data_curenta->tm_mday;
    string an_nastereaux = cnp.substr(1,2);
    if(an_nastereaux <= to_string(an_curent - 2000))
    {
        an_nastereaux = "20" + an_nastereaux;
    }
    else
    {
        an_nastereaux = "19" + an_nastereaux;
    }
    string luna_nastereaux = cnp.substr(3,2);
    if(luna_nastereaux < "10")
    {
        luna_nastereaux = luna_nastereaux.substr(1,1);
    }
    string zi_nastereaux = cnp.substr(5,2);
    if(zi_nastereaux < "10")
    {
        zi_nastereaux = zi_nastereaux.substr(1,1);
    }
    int an_nastere = stoi(an_nastereaux);
    int luna_nastere = stoi(luna_nastereaux);
    int zi_nastere = stoi(zi_nastereaux);
    int varsta = an_curent - an_nastere;
    if(luna_nastere > luna_curenta)
    {
        varsta--;
    }
    else if(luna_nastere == luna_curenta)
    {
        if(zi_nastere > zi_curenta)
        {
            varsta--;
        }
    }
    return varsta;
}

class Abonat : public Persoana
{
private:
    int nrMaxCarti, nrCartiImprumutate, pretAbonament;

public:
    void set_nrMaxCarti(int nrMaxCarti);
    void set_nrCartiImprumutate(int nrCartiImprumutate);
    void set_pretAbonament(int pretAbonament);
    int get_nrMaxCarti();
    int get_nrCartiImprumutate();
    int get_pretAbonament();
    bool verificare();
    Abonat();
    Abonat(const Abonat &abonat);
    Abonat(string cnp, string nume, int nrMaxCarti, int nrCartiImprumutate, int pretAbonament);
    ~Abonat();
    friend istream& operator>>(istream &in, Abonat &abonat);
    friend ostream& operator<<(ostream &out, Abonat &abonat);
    Abonat operator=(Abonat abonat);
};

void Abonat :: set_nrMaxCarti(int nrMaxCarti)
{
    this->nrMaxCarti = nrMaxCarti;
}

void Abonat :: set_nrCartiImprumutate(int nrCartiImprumutate)
{
    this->nrCartiImprumutate = nrCartiImprumutate;
}

void Abonat :: set_pretAbonament(int pretAbonament)
{
    this->pretAbonament = pretAbonament;
}

int Abonat :: get_nrMaxCarti()
{
    return this->nrMaxCarti;
}

int Abonat :: get_nrCartiImprumutate()
{
    return this->nrCartiImprumutate;
}

int Abonat :: get_pretAbonament()
{
    return this->pretAbonament;
}

bool Abonat :: verificare()
{
    try
    {
        if(nrCartiImprumutate > nrMaxCarti)
        {
            throw -1;
        }
        if(nrMaxCarti > pretAbonament)
        {
            throw -1;
        }
    }
    catch(...)
    {
        cout << "Abonat invalid\n";
        return false;
    }
    return true;
}

Abonat :: Abonat():Persoana()
{
    nrMaxCarti = 2;
    nrCartiImprumutate = 1;
    pretAbonament = 0;
}

Abonat :: Abonat(const Abonat &abonat):Persoana(abonat)
{
    this->nrMaxCarti = abonat.nrMaxCarti;
    this->nrCartiImprumutate = abonat.nrCartiImprumutate;
    this->pretAbonament = abonat.pretAbonament;
}

Abonat :: Abonat(string cnp, string nume, int nrMaxCarti, int nrCartiImprumutate, int pretAbonament):Persoana(cnp, nume)
{
    this->nrMaxCarti = nrMaxCarti;
    this->nrCartiImprumutate = nrCartiImprumutate;
    this->pretAbonament = pretAbonament;
    if(!this->verificare())
    {
        exit(0);
    }
}

Abonat :: ~Abonat()
{

}

istream& operator>>(istream &in, Abonat &abonat)
{
    Persoana *aux = &abonat;
    in >> *aux;
    cout << "Introduceti numarul maxim de carti:\n";
    in >> abonat.nrMaxCarti;
    cout << "Intorduceti numarul de carti imprumutate:\n";
    in >> abonat.nrCartiImprumutate;
    cout << "Introduceti pretul abonamentului:\n";
    in >> abonat.pretAbonament;
    if(!abonat.Abonat::verificare())
    {
        exit(0);
    }
    return in;
}

ostream& operator<<(ostream &out, Abonat &abonat)
{
    Persoana aux = abonat;
    out << aux;
    out << "Numarul maxim de carti: " << abonat.nrMaxCarti << '\n';
    out << "Numarul de carti imprumutate: " << abonat.nrCartiImprumutate << '\n';
    out << "Pretul abonamentului: " << abonat.pretAbonament << '\n';
    return out;
}

Abonat Abonat :: operator=(Abonat abonat)
{
    this->Persoana::operator=(abonat);
    this->nrMaxCarti = abonat.nrMaxCarti;
    this->nrCartiImprumutate = abonat.nrCartiImprumutate;
    this->pretAbonament = abonat.pretAbonament;
    return *this;
}


template <typename Type>
class Dosar
{
private:
    vector<Type*> vec;
    int l;
    static const int lmax = 1001;
public:
    Dosar();
    ~Dosar();
    static int get_lmax();
    void adaugare(Type a);
    Type get_abonat(int poz);
    void afisare();
    //Type get_vec();
    //friend ostream& operator<<(ostream &out, Dosar<Type> &dosar);
};

template <typename Type>
int  Dosar <Type> :: get_lmax()
{
    return lmax;
}

template <typename Type>
Dosar <Type> :: Dosar()
{
    l = 0;
}

template <typename Type>
Dosar <Type> :: ~Dosar()
{
    l = 0;
    vec.clear();
}

template <typename Type>
void Dosar <Type> :: adaugare(Type a)
{
    Type* aux = new Type(a);
	vec.push_back(aux);
	l++;
}

template <typename Type>
Type Dosar <Type> :: get_abonat(int poz)
{
    return *vec[poz];
}

/*template <typename Type>
Type Dosar <Type> :: get_vec()
{
    return vec;
}*/

template <typename Type>
void Dosar<Type> :: afisare()
{
    for(int i = 0; i < l; i++)
    {
        cout << "Abonatul " << i + 1 <<":\n\n";
        Type a = this->get_abonat(i);
        cout << a << '\n';
    }
    cout << '\n';
}

template <>
class Dosar<Abonat>
{
private:
    vector<Abonat*> vec;
    int l;
    static const int lmax = 1001;
public:
    Dosar();
    ~Dosar();
    static int get_lmax();
    void adaugare(Abonat a);
    Abonat get_abonat(int poz);
    void afisare();
    int pretTotal();
    int nrTotalCarti();
};


int  Dosar <Abonat> :: get_lmax()
{
    return lmax;
}

Dosar<Abonat> :: Dosar()
{
    l = 0;
}

Dosar<Abonat> :: ~Dosar()
{
    l = 0;
    vec.clear();
}

void Dosar<Abonat> :: adaugare(Abonat a)
{
    Abonat* aux = new Abonat(a);
	vec.push_back(aux);
	l++;
}

Abonat Dosar<Abonat> :: get_abonat(int poz)
{
    return *vec[poz];
}

void Dosar<Abonat> :: afisare()
{
    for(int i = 0; i < l; i++)
    {
        cout << "Abonatul " << i + 1 <<":\n\n";
        Abonat a = this->get_abonat(i);
        cout << a << '\n';
    }
    cout << '\n';
}


int Dosar<Abonat> :: pretTotal()
{
    int p = 0;
    for(int i = 0; i < l; i++)
    {
        p += vec[i]->get_pretAbonament();
    }
    return p;
}

int Dosar<Abonat> :: nrTotalCarti()
{
    int n = 0;
    for(int i = 0; i < l; i++)
    {
        n += vec[i]->get_nrCartiImprumutate();
    }
    return n;
}

void meniu()
{
    int optiune;
    Dosar<Abonat> d;
    Abonat a;
    Abonat b;
    bool ok = true;
    while(ok)
    {
        cout << "Ce doriti sa faceti?\n";
        cout << "Optiunea 1- citire si adaugare abonat la dosar\n";
        cout << "Optiunea 2 - afisare dosar\n";
        cout << "Optiunea 3 - afisare varsta abonat numarul i\n";
        cout << "Optiunea 4 - afisare detalii biblioteca\n";
        cout << "Alta optiune - oprire program\n";
        cin >> optiune;
        switch(optiune)
        {
        case 1:
            cin >> a;
            d.adaugare(a);
            break;
        case 2:
            d.afisare();
            break;
        case 3:
            cout << "Introduceti numarul abonatului\n";
            int x;
            cin >> x;
            b = d.get_abonat(x-1);
            cout << b.calculVarsta()<<"\n";
            break;
        case 4:
            cout << "S-au imprumutat " << d.nrTotalCarti() << " carti si s-a obtinut un profit de " << d.pretTotal() << " lei.\n";
        default:
            exit(0);
        }
        cout << "\n\n";
    }
}

int main()
{
    meniu();
    return 0;
}
