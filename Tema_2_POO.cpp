#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Inchisoare
{
private:
    const int id;
    int nr_celule;
    int nr_prizonieri;
    float* vector_prizonieri;

public:
    static int nr_inchisori;

    Inchisoare() : id(++nr_inchisori)
    {
        nr_celule = 0;
        nr_prizonieri = 0;
        vector_prizonieri = nullptr;
    }

    Inchisoare(int c) : id(++nr_inchisori)
    {
        nr_celule = c;
        nr_prizonieri = 5;
        vector_prizonieri = nullptr;
    }

    Inchisoare(int c, int p) : id(++nr_inchisori)
    {
        nr_celule = c;
        nr_prizonieri = p;
        vector_prizonieri = nullptr;
    }

    Inchisoare(int c, int p, float* v) : id(++nr_inchisori)
    {
        nr_celule = c;
        nr_prizonieri = p;

        vector_prizonieri = new float[c];

        for (int i = 0; i < c; i++)
        {
            vector_prizonieri[i] = v[i];
        }
    }

    void afisare()
    {
        cout << endl << "Sediu: " << id;
        cout << endl << "Numar celule: " << nr_celule;
        cout << endl << "Numar prizonieri: " << nr_prizonieri;

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
    Inchisoare inchisoare(10);
    inchisoare.afisare();

    Inchisoare celule(20, 8);
    celule.afisare();

    float v[3] = { 1, 2, 3 };

    Inchisoare prizonieri(3, 12, v);
    prizonieri.afisare();

    int total_prizonieri = inchisoare.getNr_prizonieri()
        + celule.getNr_prizonieri()
        + prizonieri.getNr_prizonieri();

    cout << endl << "Noul numar de prizonieri este: "
        << total_prizonieri << endl;

    cout << endl << "Am structurat "
        << Inchisoare::nr_inchisori
        << " inchisori!";

    return 0;
}



