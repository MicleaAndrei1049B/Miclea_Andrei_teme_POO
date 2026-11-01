
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

enum Zona { CENTRALA = 1, PERIFERICA = 2 };

class Inchisoare
{
private:
    const int id;
    string denumire;
    Zona zona;
    int nr_celule;
    int nr_prizonieri;
    float* vector_prizonieri;

public:
    static int nr_inchisori;

    
    Inchisoare() : id(++nr_inchisori)
    {
        denumire = "Default";
        zona = PERIFERICA;
        nr_celule = 0;
        nr_prizonieri = 0;
        vector_prizonieri = nullptr;
    }

    
    Inchisoare(int c) : id(++nr_inchisori)
    {
        denumire = "Default";
        zona = PERIFERICA;
        nr_celule = c;
        nr_prizonieri = 5;
        vector_prizonieri = nullptr;
    }

    
    Inchisoare(int c, int p) : id(++nr_inchisori)
    {
        denumire = "Default";
        zona = PERIFERICA;
        nr_celule = c;
        nr_prizonieri = p;
        vector_prizonieri = nullptr;
    }

    
    Inchisoare(int c, int p, float* v) : id(++nr_inchisori)
    {
        denumire = "Default";
        zona = PERIFERICA;
        nr_celule = c;
        nr_prizonieri = p;

        vector_prizonieri = new float[c];

        for (int i = 0; i < c; i++)
        {
            vector_prizonieri[i] = v[i];
        }
    }

   
    Inchisoare(string d, Zona z, int c, int p, float* v)
        : id(++nr_inchisori)
    {
        denumire = d;
        zona = z;
        nr_celule = c;
        nr_prizonieri = p;

        vector_prizonieri = nullptr;

        if (c > 0)
        {
            vector_prizonieri = new float[c];

            for (int i = 0; i < c; i++)
            {
                vector_prizonieri[i] = v[i];
            }
        }
    }

    
    Inchisoare(const Inchisoare& i) : id(++nr_inchisori)
    {
        denumire = i.denumire;
        zona = i.zona;
        nr_celule = i.nr_celule;
        nr_prizonieri = i.nr_prizonieri;

        if (i.vector_prizonieri != nullptr)
        {
            vector_prizonieri = new float[nr_celule];

            for (int j = 0; j < nr_celule; j++)
            {
                vector_prizonieri[j] = i.vector_prizonieri[j];
            }
        }
        else
        {
            vector_prizonieri = nullptr;
        }
    }

    
    Inchisoare& operator=(const Inchisoare& i)
    {
        if (this != &i)
        {
            denumire = i.denumire;
            zona = i.zona;
            nr_celule = i.nr_celule;
            nr_prizonieri = i.nr_prizonieri;

            if (vector_prizonieri != nullptr)
            {
                delete[] vector_prizonieri;
                vector_prizonieri = nullptr;
            }

            if (i.vector_prizonieri != nullptr)
            {
                vector_prizonieri = new float[nr_celule];

                for (int j = 0; j < nr_celule; j++)
                {
                    vector_prizonieri[j] = i.vector_prizonieri[j];
                }
            }
        }

        return *this;
    }

    
    void afisare()
    {
        cout << endl << "Sediu: " << id;
        cout << endl << "Denumire: " << denumire;
        cout << endl << "Numar celule: " << nr_celule;
        cout << endl << "Numar prizonieri: " << nr_prizonieri;

        cout << endl << "Zona: ";

        if (zona == CENTRALA)
        {
            cout << "CENTRALA";
        }
        else
        {
            cout << "PERIFERICA";
        }

        if (vector_prizonieri != nullptr && nr_celule > 0)
        {
            cout << endl << "Numar prizonieri per celula: ";

            for (int i = 0; i < nr_celule - 1; i++)
            {
                cout << vector_prizonieri[i] << ", ";
            }

            cout << vector_prizonieri[nr_celule - 1];
        }

        cout << endl;
    }

    
    int getNr_celule()
    {
        return nr_celule;
    }

    void setNr_celule(int c)
    {
        if (c >= 0)
        {
            nr_celule = c;
        }
        else
        {
            throw "Numar de celule negativ!";
        }
    }

    
    int getNr_prizonieri()
    {
        return nr_prizonieri;
    }

   
    float* getVector_prizonieri()
    {
        if (vector_prizonieri == nullptr)
        {
            return nullptr;
        }

        float* vector_nou = new float[nr_celule];

        for (int i = 0; i < nr_celule; i++)
        {
            vector_nou[i] = vector_prizonieri[i];
        }

        return vector_nou;
    }

    void setVector_prizonieri(float* v, int nr)
    {
        if (nr < 0)
        {
            throw "Numar de celule negativ!";
        }

        if (vector_prizonieri != nullptr)
        {
            delete[] vector_prizonieri;
        }

        nr_celule = nr;

        if (nr > 0)
        {
            vector_prizonieri = new float[nr];

            for (int i = 0; i < nr; i++)
            {
                vector_prizonieri[i] = v[i];
            }
        }
        else
        {
            vector_prizonieri = nullptr;
        }
    }

    
    bool operator<(const Inchisoare& i)
    {
        return nr_celule < i.nr_celule;
    }

    
    ~Inchisoare()
    {
        if (vector_prizonieri != nullptr)
        {
            delete[] vector_prizonieri;
        }
    }
};

int Inchisoare::nr_inchisori = 0;


int main()
{
    Inchisoare sediuDefault;
    sediuDefault.afisare();

    float* vectorPrizonieri = new float[3] { 1, 2, 3 };

    Inchisoare* sediuCentral = new Inchisoare(
        "Sediul Central", CENTRALA, 3, 12, vectorPrizonieri);

    delete[] vectorPrizonieri;

    sediuCentral->afisare();

    Inchisoare sediuPeriferic = *sediuCentral;
    sediuPeriferic.afisare();

    sediuDefault = *sediuCentral;

    cout << endl << "Am structurat "
        << Inchisoare::nr_inchisori << " inchisori!";

    if (sediuDefault < sediuPeriferic)
    {
        cout << endl << "Sediul Default are mai putine celule!";
    }
    else
    {
        cout << endl << "Sediul Central are mai putine celule!";
    }

    delete sediuCentral;

    return 0;
}