#include <iostream>
#include <string>

using namespace std;

class Inchisoare
{
private:
    const int id;
    string denumire;
    int nr_celule;
    int nr_prizonieri;

public:
    static int nr_inchisori;

    
    Inchisoare() : id(++nr_inchisori)
    {
        denumire = "Default";
        nr_celule = 0;
        nr_prizonieri = 0;
    }

    
    Inchisoare(string d, int c, int p) : id(++nr_inchisori)
    {
        denumire = d;
        nr_celule = c;
        nr_prizonieri = p;
    }

    
    Inchisoare(const Inchisoare& i) : id(++nr_inchisori)
    {
        denumire = i.denumire;
        nr_celule = i.nr_celule;
        nr_prizonieri = i.nr_prizonieri;
    }

    
    Inchisoare operator+(const Inchisoare& i)
    {
        Inchisoare copie(*this);

        copie.nr_celule = nr_celule + i.nr_celule;
        copie.nr_prizonieri = nr_prizonieri + i.nr_prizonieri;

        return copie;
    }

    
    Inchisoare operator-(const Inchisoare& i)
    {
        Inchisoare copie(*this);

        copie.nr_celule = nr_celule - i.nr_celule;
        copie.nr_prizonieri = nr_prizonieri - i.nr_prizonieri;

        return copie;
    }

    bool operator==(const Inchisoare& i) const
    {
        return nr_celule == i.nr_celule;
    }

    
    bool operator<(const Inchisoare& i)
    {
        return nr_celule < i.nr_celule;
    }

    
    Inchisoare& operator=(const Inchisoare& i)
    {
        if (this != &i)
        {
            denumire = i.denumire;
            nr_celule = i.nr_celule;
            nr_prizonieri = i.nr_prizonieri;
        }

        return *this;
    }

    
    void afisare()
    {
        cout << endl << "Sediu: " << id;
        cout << endl << "Denumire: " << denumire;
        cout << endl << "Numar celule: " << nr_celule;
        cout << endl << "Numar prizonieri: " << nr_prizonieri;
        cout << endl;
    }

    
    
};

int Inchisoare::nr_inchisori = 0;

int main()
{
    Inchisoare sediu1("Central", 10, 50);
    Inchisoare sediu2("Periferic", 5, 20);

    cout << "Inchisorile initiale:";
    sediu1.afisare();
    sediu2.afisare();

    
    Inchisoare sediu3 = sediu1 + sediu2;

    cout << endl << "Dupa adunare:";
    sediu3.afisare();

    
    Inchisoare sediu4 = sediu1 - sediu2;

    cout << endl << "Dupa scadere:";
    sediu4.afisare();

   
    if (sediu1 == sediu2)
    {
        cout << endl << "Inchisorile au acelasi numar de celule!";
    }
    else
    {
        cout << endl << "Inchisorile au numar diferit de celule!";
    }

    
    if (sediu1 < sediu2)
    {
        cout << endl << "Sediul Central are mai putine celule!";
    }
    else
    {
        cout << endl << "Sediul Periferic are mai putine celule!";
    }

   
    Inchisoare sediu5;
    sediu5 = sediu1;

    cout << endl << "Dupa atribuire:";
    sediu5.afisare();

    cout << endl << "Am structurat "
        << Inchisoare::nr_inchisori << " inchisori!";

    return 0;
}



