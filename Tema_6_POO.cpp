
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <exception>

using namespace std;


class ExceptieCustom : public exception
{
private:
    string mesaj;

public:
    ExceptieCustom(const char* mesaj) : mesaj(mesaj)
    {
    }

    const char* what() const noexcept override
    {
        return mesaj.c_str();
    }
};

enum Zona { CENTRALA = 1, PERIFERICA = 2 };

class Inchisoare
{
private:
    const int id;
    string denumire;
    Zona zona;
    int nr_celule;
    int nr_prizonieri;
    float chirie;
    float* vector_prizonieri;

public:
    static int nr_inchisori;
    static const float CHIRIE_MINIMA;

  
    Inchisoare() : id(++nr_inchisori)
    {
        denumire = "Default";
        zona = PERIFERICA;
        nr_celule = 0;
        nr_prizonieri = 0;
        chirie = 0;
        vector_prizonieri = nullptr;
    }

   
    Inchisoare(int c) : id(++nr_inchisori)
    {
        denumire = "Default";
        zona = PERIFERICA;
        nr_celule = c;
        nr_prizonieri = 5;
        chirie = 0;
        vector_prizonieri = nullptr;
    }


    Inchisoare(int c, int p) : id(++nr_inchisori)
    {
        denumire = "Default";
        zona = PERIFERICA;
        nr_celule = c;
        nr_prizonieri = p;
        chirie = 0;
        vector_prizonieri = nullptr;
    }

   
    Inchisoare(int c, int p, float* v) : id(++nr_inchisori)
    {
        denumire = "Default";
        zona = PERIFERICA;
        nr_celule = c;
        nr_prizonieri = p;
        chirie = 0;
        vector_prizonieri = nullptr;

        if (c > 0 && v != nullptr)
        {
            vector_prizonieri = new float[c];

            for (int i = 0; i < c; i++)
            {
                vector_prizonieri[i] = v[i];
            }
        }
    }


    Inchisoare(string d, Zona z, int c, int p, float* v, float ch = 0)
        : id(++nr_inchisori)
    {
        if (ch < 0 || (ch > 0 && ch < CHIRIE_MINIMA))
        {
            throw ExceptieCustom("Chiria este prea mica!");
        }

        denumire = d;
        zona = z;
        nr_celule = c;
        nr_prizonieri = p;
        chirie = ch;
        vector_prizonieri = nullptr;

        if (c > 0 && v != nullptr)
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
        chirie = i.chirie;

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
            chirie = i.chirie;

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

 
    virtual void afisare()
    {
        cout << endl << "Sediu: " << id;
        cout << endl << "Denumire: " << denumire;
        cout << endl << "Numar celule: " << nr_celule;
        cout << endl << "Numar prizonieri: " << nr_prizonieri;
        cout << endl << "Chirie: " << chirie << " euro";

        cout << endl << "Zona: ";

        if (zona == CENTRALA)
            cout << "CENTRALA";
        else
            cout << "PERIFERICA";

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

 
    virtual float getProcentReducere()
    {
        return 0;
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
            throw ExceptieCustom("Numar de celule negativ!");
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
            throw ExceptieCustom("Numar de celule negativ!");
        }

        if (vector_prizonieri != nullptr)
        {
            delete[] vector_prizonieri;
            vector_prizonieri = nullptr;
        }

        nr_celule = nr;

        if (nr > 0 && v != nullptr)
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

    
    void operator+=(float chirieDeAdaugat)
    {
        chirie += chirieDeAdaugat;
    }

    
    bool operator!()
    {
        return chirie > 0;
    }

   
    float operator()(float valoareDeAdaugat)
    {
        return chirie + valoareDeAdaugat;
    }

    
    float& operator[](int index)
    {
        if (index >= 0 && index < nr_celule &&
            vector_prizonieri != nullptr)
        {
            return vector_prizonieri[index];
        }
        else
        {
            throw ExceptieCustom("Index invalid!");
        }
    }

    
    friend ostream& operator<<(ostream& out, const Inchisoare& i)
    {
        out << endl << "Operator de afisare: ";
        out << endl << "Sediu: " << i.id;
        out << endl << "Denumire: " << i.denumire;
        out << endl << "Chirie: " << i.chirie;
        out << endl << "Zona: ";

        if (i.zona == CENTRALA)
            out << "CENTRALA";

        if (i.zona == PERIFERICA)
            out << "PERIFERICA";

        out << endl << "Numar celule: " << i.nr_celule;
        out << endl << "Numar prizonieri: " << i.nr_prizonieri;

        if (i.vector_prizonieri != nullptr)
        {
            out << endl << "Vector prizonieri: ";

            for (int j = 0; j < i.nr_celule; j++)
            {
                out << i.vector_prizonieri[j] << " ";
            }
        }

        return out;
    }

    
    friend istream& operator>>(istream& in, Inchisoare& i);

    
    Inchisoare operator++(int)
    {
        Inchisoare copie = *this;
        chirie++;

        return copie;
    }

    
    Inchisoare& operator++()
    {
        chirie++;

        return *this;
    }

    
    explicit operator int()
    {
        return nr_celule;
    }

    
    virtual ~Inchisoare()
    {
        if (vector_prizonieri != nullptr)
        {
            delete[] vector_prizonieri;
        }
    }
};


int Inchisoare::nr_inchisori = 0;
const float Inchisoare::CHIRIE_MINIMA = 1;



class InchisoareRedusa : public Inchisoare
{
private:
    float procentReducere;

public:

    InchisoareRedusa() : Inchisoare()
    {
        procentReducere = 0;
    }

    InchisoareRedusa(string d, Zona z, int c, int p,
        float* v, float ch, float reducere)
        : Inchisoare(d, z, c, p, v, ch)
    {
        procentReducere = reducere;
    }

    
    void afisare() override
    {
        Inchisoare::afisare();

        cout << "Procent reducere: "
            << procentReducere << "%" << endl;
    }

   
    float getProcentReducere() override
    {
        return procentReducere;
    }
};



istream& operator>>(istream& in, Inchisoare& i)
{
    cout << endl << "Denumire: ";
    in >> i.denumire;

    cout << endl << "Chirie: ";
    in >> i.chirie;

    if (i.chirie < 0 ||
        (i.chirie > 0 && i.chirie < Inchisoare::CHIRIE_MINIMA))
    {
        throw ExceptieCustom("Chiria este prea mica!");
    }

    cout << endl << "Zona (1-CENTRALA, 2-PERIFERICA): ";

    int zona;
    in >> zona;

    if (zona == 1)
        i.zona = CENTRALA;
    else if (zona == 2)
        i.zona = PERIFERICA;
    else
        throw ExceptieCustom("Zona invalida!");

    cout << endl << "Numar celule: ";
    in >> i.nr_celule;

    if (i.nr_celule < 0)
    {
        throw ExceptieCustom("Numar de celule negativ!");
    }

    cout << endl << "Numar prizonieri: ";
    in >> i.nr_prizonieri;

    if (i.vector_prizonieri != nullptr)
    {
        delete[] i.vector_prizonieri;
        i.vector_prizonieri = nullptr;
    }

    if (i.nr_celule > 0)
    {
        i.vector_prizonieri = new float[i.nr_celule];

        cout << endl << "Vector prizonieri: ";

        for (int j = 0; j < i.nr_celule; j++)
        {
            cout << endl << "vector_prizonieri[" << j << "]: ";
            in >> i.vector_prizonieri[j];
        }
    }

    return in;
}



int main()
{
    try
    {
        InchisoareRedusa sediuDefault;

        float* vectorPrizonieri = new float[3] { 1, 2, 3 };

        InchisoareRedusa* sediuCentral =
            new InchisoareRedusa(
                "Sediul Central", CENTRALA, 3, 12,
                vectorPrizonieri, 800, 10);

        delete[] vectorPrizonieri;

        float vector2[3] = { 4, 5, 6 };

        InchisoareRedusa sediuPeriferic(
            "Sediul Periferic", PERIFERICA, 3, 15,
            vector2, 600, 5);

        
        Inchisoare* vectorInchisori[3];

        vectorInchisori[0] = &sediuDefault;
        vectorInchisori[1] = sediuCentral;
        vectorInchisori[2] = &sediuPeriferic;

        cout << endl << "Informatii sedii:";

        for (int i = 0; i < 3; i++)
        {
            vectorInchisori[i]->afisare();

            cout << "Reducere: "
                << vectorInchisori[i]->getProcentReducere()
                << "%" << endl;
        }

        cout << endl << "Am structurat "
            << Inchisoare::nr_inchisori << " inchisori!";

        delete sediuCentral;
    }
    catch (exception& e)
    {
        cout << endl << "Eroare: " << e.what();
    }

    return 0;
}
