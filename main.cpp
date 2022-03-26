#include <iostream>
#include <string>
#include<fstream>
#include <cstdlib>

using namespace std;

void clear()  //functia de curatare ecran consola
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
    system("clear");
#endif
}

class persoana{
    string nume;
    string prenume;
public:
    persoana(char *a = nullptr, char *b = nullptr);
    persoana & operator = (const persoana &);
    string getnume()
    {
        return this->nume;
    }
    string getprenume()
    {
        return this->prenume;
    }
    void editare_nume(char *x){this->nume = x;}
    void editare_prenume(char *x){this->prenume = x;}
};

persoana::persoana(char *a, char *b)
{
    nume = a;
    prenume = b;
}

persoana& persoana::operator=(const persoana &x)
{
    /*if(&x == this)
        return *this;*/
    this->nume = x.nume;
    this->prenume = x.prenume;
    return *this;
}

class account{
    int id;
    persoana *om;
    int deposit;
    bool inghet;
    string moneda;
public:
    account(int id , int deposit , persoana &a, string b);
    account(int id, int deposit, persoana &a, string b, bool x); // constructor explicit folosit pentru modificarea variabilei bool pentru inghetare cont
    void afisare();
    int get_deposit(){return this->deposit;}
    void adaugare_deposit(int x){this->deposit = this->deposit + x;}
    void retragere_deposit(int x){this->deposit = this->deposit - x;}
    void editare_id(int x){this->id = x;}
    void editare_nume(char *x){om->editare_nume(x);}
    void editare_prenume(char *x){om->editare_prenume(x);}
    void editare_inghet(bool x){this->inghet = x;}
    void editare_moneda(string x){this->moneda = x;}
    int get_id(){return this->id;}
    persoana * get_persoana(){return this->om;}
    bool get_inghet(){return inghet;}
    string get_nume(){return om->getnume();}
    string get_prenume(){return om->getprenume();}
    string get_moneda(){return this->moneda;}
};

account::account(int id, int deposit, persoana &a, string b)
{
    this->id = id;
    this->deposit = deposit;
    om = &a;
    this->inghet = false;
    this->moneda = b;
}

account::account(int id, int deposit, persoana &a, string b, bool x)
{
    this->id = id;
    this->deposit = deposit;
    om = &a;
    this->inghet = x;
    this->moneda = b;
}

void account::afisare()
{
    cout<<"ID: "<<this->id<<endl;
    cout<<"Nume: "<<om->getnume()<<endl;
    cout<<"Prenume: "<<om->getprenume()<<endl;
    cout<<"Soldul: "<<this->deposit<<endl;
    cout<<"Moneda: "<<this->moneda<<endl;
}

class banca{
    int nrconturi;
    account **membri;
public:
    banca()
    {
        nrconturi = 0;
        membri = new account * [100];
    }

    void adaugare_membru(account &a); // functia de adaugare a unui obiect de tipul account in sirul de obiecte de tip account

    void eliminare_membru(int id); //functia de eliminare a unui obiect de tipul account in sirul de obiecte de tip account

    ~banca();

    void afisare(); //functie de afisare toate conturile

    void afisare_cont_anume(int i){membri[i]->afisare();} //functie de afisare un singur cont

    int get_deposit_cont_anume(int i){return membri[i]->get_deposit();}

    void adaugare_deposit_cont_anume(int i, int x){membri[i]->adaugare_deposit(x);}

    void retragere_deposit_cont_anume(int i, int x){membri[i]->retragere_deposit(x);}

    void schimbare_id_cont_anume(int i, int x){membri[i]->editare_id(x);}

    void schimbare_nume_cont_anume(int i, char *x){membri[i]->editare_nume(x);}

    void schimbare_prenume_cont_anume(int i, char *x){membri[i]->editare_prenume(x);}

    void schimbare_inghet_cont_anume(int i, bool x){membri[i]->editare_inghet(x);}

    void schimbare_moneda_cont_anume(int i, string x){membri[i]->editare_moneda(x);}

    int getnrconturi(){return this->nrconturi;}

    string get_nume(int i){return membri[i]->get_nume();}

    string get_prenume(int i){return membri[i]->get_prenume();}

    string get_moneda(int i){return membri[i]->get_moneda();}

    int get_id(int i){return membri[i]->get_id();}

    int get_deposit(int i){return membri[i]->get_deposit();}

    bool get_inghet_cont_anume(int i){return membri[i]->get_inghet();}

    persoana * get_persoana_cont_anume(int i){return membri[i]->get_persoana();}

    //banca(account *a = nullptr);

};

void banca::adaugare_membru(account &a)
{
    membri[nrconturi] = &a;
    nrconturi++;
}

void banca::eliminare_membru(int id)
{
    int i = 0;
    while(i < id - 1)
        i++;
    for(int j = i + 1; j < nrconturi; j++)
    {
        membri[i] = membri[j];
        i++;
    }
    membri[nrconturi] = nullptr;
    nrconturi--;
}

banca::~banca()
{
    if(membri != nullptr)
        delete [] membri;
}

void banca::afisare()
{
    for(int i = 0; i < nrconturi; i++)
        {
            cout<<i+1<<endl;
            membri[i]->afisare();
        }

}

//Functii normale

void adaugare_cont(banca *b)
{
    char nume[50], prenume[50];
    int id, suma, k = 0, alegere = 0, alegere2;
    clear();
    cout<<"Doresti sa adaugi un cont nou ? "<<endl;
    cout<<"1. DA"<<endl;
    cout<<"2. NU"<<endl;
    cin>>alegere2;

    while(alegere2 < 1 || alegere2 > 2)
    {
        clear();
        cout<<"Optiunea selectata anterior nu exista. Alege una din optiunile de mai jos"<<endl;
        cout<<"Doresti sa adaugi un cont nou ? "<<endl;
        cout<<"1. DA"<<endl;
        cout<<"2. NU"<<endl;
        cin>>alegere2;
    }

    if(alegere2 == 1)
    {
    string s;
    cout<<endl;
    cout<<"Introdu Numele: ";
    cin.get();
    cin.get(nume, 50);
    cout<<endl;
    cout<<"Introdu Prenumele: ";
    cin.get();
    cin.get(prenume, 50);
    cout<<endl;
    cout<<"Introdu ID-ul: ";cin>>id;
    cout<<endl;

    for(int i = 0; i < b->getnrconturi(); i++)
    {
        if(b->get_id(i) == id)
        {
            cout<<endl<<"ID-ul introdus exista deja. Reintrodu un alt ID"<<endl;
            cin>>id;
            i = -1;
        }
    }

    while(id < 0)
                {
                    clear();
                    cout<<"ID-ul introdus este invalid. Reintrodu "<<endl;
                    cout<<"Ce ID doresti sa introduci? "<<endl;
                    cin>>id;

                    for(int i = 0; i < b->getnrconturi(); i++)
                    {
                        if(b->get_id(i) == id)
                        {
                            cout<<endl<<"ID-ul introdus exista deja. Reintrodu un alt ID"<<endl;
                            cin>>id;
                            i = -1;
                        }
                    }
                }

    cout<<"Introdu Soldul: ";cin>>suma;

    if(alegere == 0)
    {
        cout<<endl<<"Selecteza optiunea corespunzatoare monedei soldului"<<endl;
        cout<<endl<<"1. Lei"<<endl;
        cout<<endl<<"2. Euro"<<endl;
        cout<<endl<<"3. Dolari/USD"<<endl;
        cout<<endl<<"4. Lire sterline"<<endl;
        cout<<endl;
        cin>>alegere;

        while(alegere < 1 || alegere > 4)
        {
            clear();
            cout<<endl<<"Optiunea selectata este incorecta. Alege una din optiunile de mai jos"<<endl;
            cout<<endl<<"Selecteza optiunea corespunzatoare monedei soldului"<<endl;
            cout<<endl<<"1. Lei"<<endl;
            cout<<endl<<"2. Euro"<<endl;
            cout<<endl<<"3. Dolari/USD"<<endl;
            cout<<endl<<"4. Lire sterline"<<endl;
            cout<<endl;
            cin>>alegere;
        }
    }

    if(alegere == 1)
        s = "Lei";
    else if(alegere == 2)
        s = "Euro";
    else if(alegere == 3)
        s = "USD";
    else s = "Lire sterline";

    //cout<<nume<<endl<<prenume<<endl<<id<<endl<<suma<<endl;
    for(int i = 0; i < b->getnrconturi(); i++)
    {
        if(b->get_nume(i) == nume && b->get_prenume(i) == prenume)
            {
                account *c = new account(id, suma, *b->get_persoana_cont_anume(i), s);
                b->adaugare_membru(*c);
                k = 1;
                i = b->getnrconturi() + 1;
                //cout<<"AICIIIIIIIIIIIIIIIIIIIIIII"<<endl;
            }

    }
    if(k == 0)
    {
        persoana *a = new persoana(nume, prenume);
        account *c = new account(id, suma, *a, s);
        b->adaugare_membru(*c);
    }
    //b->afisare();
    }
}

void meniu_fct_cont(banca *, int);

void afisare_conturi(banca *b)
{
    /*for(int i = 0; i < b.getnrconturi(); i++)
    {
        cout<<i + 1<<endl;
        cout<<"ID: "<<b.get_id(i)<<endl;
        cout<<"Nume: "<<b.get_nume(i)<<endl;
        cout<<"Prenume: "<<b.get_prenume(i)<<endl;
        cout<<"Soldul: "<<b.get_deposit(i)<<endl;
    }*/

    b->afisare();
}

void afisare_lista_conturi(banca *b)
{
    //cout<<"Lista de conturi: "<<endl;
    //afisare_conturi(b);

    int k;
    cout<<endl<<"Optiuni disponibile: "<<endl;
    cout<<endl<<"1. Acceseaza un cont"<<endl;
    cout<<endl<<"2. Back"<<endl;
    cin>>k;

    while(k < 1 || k > 2)
    {
        cout<<endl<<"Optiunea selectata anterior nu exista. Alege una din optiunile de mai jos"<<endl;
        cout<<endl<<"Optiuni disponibile: "<<endl;
        cout<<endl<<"1. Acceseaza un cont"<<endl;
        cout<<endl<<"2. Back"<<endl;
        cin>>k;
    }

    if(k == 1)
    {
        int y;
        cout<<endl<<"Alege un index corespunzator unui cont pentru a-l accesa Sau Scrie 0 pentru a iesi"<<endl;
        cin>>y;

        while(y < 0 || y > b->getnrconturi())
            {cout<<endl<<"Indexul introdus nu exista in lista. Reintrodu indexul corespunzator"<<endl;
            cin>>y;}

        if(y != 0)
            meniu_fct_cont(b, y);
    }

    clear();
}

void meniu_fct_cont(banca *b, int x)
{
    int opt = 0;
    if(b->get_inghet_cont_anume(x - 1) == false)
    while(opt < 5 && b->get_inghet_cont_anume(x - 1) == false)
    {clear();
    b->afisare_cont_anume(x - 1);
    cout<<endl<<"Selecteaza una din optiunile disponibile: "<<endl;
    cout<<endl<<"1. Depozitare suma"<<endl;
    cout<<"2. Retragere suma"<<endl;
    cout<<"3. Modificare date cont"<<endl;
    cout<<"4. Inghetare cont"<<endl;
    cout<<"5. Meniul Principal"<<endl;
    cin>>opt;

    while(opt < 1 || opt > 5)
    {
        clear();
        cout<<"Optiune incorecta. Reintrodu nr. optiunii selectate"<<endl;
        b->afisare_cont_anume(x - 1);
        cout<<endl<<"Selecteaza una din optiunile disponibile: "<<endl;
        cout<<endl<<"1. Depozitare suma"<<endl;
        cout<<"2. Retragere suma"<<endl;
        cout<<"3. Modificare date cont"<<endl;
        cout<<"4. Inghetare cont"<<endl;
        cout<<"5. Meniul Principal"<<endl;
        cin>>opt;
    }

    if(opt == 1)
        {
            clear();
            cout<<"Soldul curent al contului: "<<b->get_deposit_cont_anume(x - 1)<<endl;
            int j;
            cout<<"Ce suma doresti sa depozitezi in cont? "<<endl;
            cin>>j;
            while(j < 0)
            {
                clear();
                cout<<"Soldul introdus este incorect. Rescrie suma"<<endl;
                cout<<"Soldul curent al contului: "<<b->get_deposit_cont_anume(x - 1)<<endl;
                cout<<"Ce suma doresti sa depozitezi in cont? "<<endl;
                cin>>j;
            }
            b->adaugare_deposit_cont_anume(x - 1, j);
        }

    else if(opt == 2)
        {
            clear();
            cout<<"Soldul curent al contului: "<<b->get_deposit_cont_anume(x - 1)<<endl;
            int suma;
            cout<<"Ce suma doresti sa retragi din cont? "<<endl;
            cin>>suma;
            while(suma < 0 || suma > b->get_deposit_cont_anume(x - 1))
            {
                clear();
                cout<<"Soldul introdus este incorect. Rescrie suma"<<endl;
                cout<<"Soldul curent al contului: "<<b->get_deposit_cont_anume(x - 1)<<endl;
                cout<<"Ce suma doresti sa retragi din cont? "<<endl;
                cin>>suma;
            }
            b->retragere_deposit_cont_anume(x - 1, suma);
        }

    else if(opt == 3)
        {
            int opt2 = 0;
            while(opt2 < 5)
            {clear();
            b->afisare_cont_anume(x - 1);
            cout<<endl<<"Ce doresti sa modifici? "<<endl;
            cout<<endl<<"1. Numele titularului"<<endl;
            cout<<"2. Prenumele Titularului"<<endl;
            cout<<"3. ID-ul contului"<<endl;
            cout<<"4. Moneda soldului"<<endl;
            cout<<"5. Back"<<endl;

            cin>>opt2;

            while(opt2 < 1 || opt2 > 5)
            {
                clear();
                cout<<"Optiune incorecta. Reintrodu nr. optiunii"<<endl;
                b->afisare_cont_anume(x - 1);
                cout<<endl<<"Ce doresti sa modifici? "<<endl;
                cout<<endl<<"1. Numele titularului"<<endl;
                cout<<"2. Prenumele Titularului"<<endl;
                cout<<"3. ID-ul contului"<<endl;
                cout<<"4. Moneda soldului"<<endl;
                cout<<"5. Back"<<endl;
                cin>>opt2;
            }

            if(opt2 == 1)
            {
                clear();
                cout<<"Numele titularului contului: "<<b->get_nume(x - 1)<<endl;
                char nume[50];
                cout<<"Ce nume doresti sa introduci? "<<endl;
                cin.get();
                cin.get(nume, 50);
                b->schimbare_nume_cont_anume(x - 1, nume);
            }

            else if(opt2 == 2)
            {
                clear();
                cout<<"Prenumele titularului contului: "<<b->get_prenume(x - 1)<<endl;
                char nume[50];
                cout<<"Ce prenume doresti sa introduci? "<<endl;
                cin.get();
                cin.get(nume, 50);
                b->schimbare_prenume_cont_anume(x - 1, nume);
            }

            else if(opt2 == 3)
            {
                clear();
                cout<<"ID-ul titularului contului: "<<b->get_id(x - 1)<<endl;
                int id;
                cout<<"Ce ID doresti sa introduci? "<<endl;
                cin>>id;

                for(int i = 0; i < b->getnrconturi(); i++)
                {
                    if(b->get_id(i) == id)
                    {
                        cout<<endl<<"ID-ul introdus exista deja. Reintrodu un alt ID"<<endl;
                        cin>>id;
                        i = -1;
                    }
                }

                while(id < 0)
                {
                    clear();
                    cout<<"ID-ul introdus este invalid. Reintrodu "<<endl;
                    cout<<"ID-ul titularului contului: "<<b->get_id(x - 1)<<endl;
                    cout<<"Ce ID doresti sa introduci? "<<endl;
                    cin>>id;

                    for(int i = 0; i < b->getnrconturi(); i++)
                    {
                        if(b->get_id(i) == id)
                        {
                            cout<<endl<<"ID-ul introdus exista deja. Reintrodu un alt ID"<<endl;
                            cin>>id;
                            i = -1;
                        }
                    }
                }
                b->schimbare_id_cont_anume(x - 1, id);
            }

            else if(opt2 == 4)
            {
                clear();
                int alegere;
                string s;
                cout<<"Moneda actuala a soldului"<<b->get_moneda(x - 1)<<endl;
                cout<<endl<<"Selecteza optiunea corespunzatoare monedei"<<endl;
                cout<<endl<<"1. Lei"<<endl;
                cout<<endl<<"2. Euro"<<endl;
                cout<<endl<<"3. Dolari/USD"<<endl;
                cout<<endl<<"4. Lire sterline"<<endl;
                cout<<endl;
                cin>>alegere;

                while(alegere < 1 || alegere > 4)
                {
                    clear();
                    cout<<endl<<"Optiunea selectata este incorecta. Alege una din optiunile de mai jos"<<endl;
                    cout<<endl<<"Selecteza optiunea corespunzatoare monedei"<<endl;
                    cout<<endl<<"1. Lei"<<endl;
                    cout<<endl<<"2. Euro"<<endl;
                    cout<<endl<<"3. Dolari/USD"<<endl;
                    cout<<endl<<"4. Lire sterline"<<endl;
                    cout<<endl;
                    cin>>alegere;
                }

                if(alegere == 1)
                    s = "Lei";
                else if(alegere == 2)
                    s = "Euro";
                else if(alegere == 3)
                    s = "USD";
                else s = "Lire sterline";

                b->schimbare_moneda_cont_anume(x - 1, s);
            }

        }

        }

        else if(opt == 4)
        {
            clear();
            cout<<"Doresti sa ingheti contul bancar, cu datele: "<<endl;
            b->afisare_cont_anume(x - 1);
            cout<<endl;
            int k;
            cout<<endl<<"1. DA"<<endl;
            cout<<"2. NU"<<endl;
            cin>>k;
            while(k < 1 || k > 2)
            {
                clear();
                cout<<"Optiune incorecta. Reintrodu nr. optiunii selectate"<<endl;
                cout<<endl<<"Doresti sa ingheti contul bancar, cu datele: "<<endl;
                b->afisare_cont_anume(x - 1);
                cout<<endl;
                cout<<endl<<"1. DA"<<endl;
                cout<<"2. NU"<<endl;
                cin>>k;
            }

            if(k == 1)
                b->schimbare_inghet_cont_anume(x - 1, true);
        }
    }

    else
        while(opt < 2 && b->get_inghet_cont_anume(x - 1) == true)
        {
            clear();
            b->afisare_cont_anume(x - 1);
            cout<<endl<<"Selecteaza una din optiunile disponibile: "<<endl;
            cout<<endl<<"1. Dezghetare cont"<<endl;
            cout<<"2. Meniul Principal"<<endl;
            cin>>opt;

        while(opt < 1 || opt > 2)
        {
            clear();
            cout<<"Optiune incorecta. Reintrodu nr. optiunii selectate"<<endl;
            b->afisare_cont_anume(x - 1);
            cout<<endl<<"Selecteaza una din optiunile disponibile: "<<endl;
            cout<<endl<<"1. Dezghetare cont"<<endl;
            cout<<"2. Meniul Principal"<<endl;
            cin>>opt;
        }

        if(opt == 1)
        {
            clear();
            cout<<"Doresti sa dezgheti contul bancar, cu datele: "<<endl;
            b->afisare_cont_anume(x - 1);
            cout<<endl;
            int k;
            cout<<endl<<"1. DA"<<endl;
            cout<<"2. NU"<<endl;
            cin>>k;
            while(k < 1 || k > 2)
            {
                clear();
                cout<<"Optiune incorecta. Reintrodu nr. optiunii selectate"<<endl;
                cout<<endl<<"Doresti sa dezgheti contul bancar, cu datele: "<<endl;
                b->afisare_cont_anume(x - 1);
                cout<<endl;
                cout<<endl<<"1. DA"<<endl;
                cout<<"2. NU"<<endl;
                cin>>k;
            }

            if(k == 1)
                b->schimbare_inghet_cont_anume(x - 1, false);
        }

        }

}

void stergere_cont(banca *b)
{
    cout<<"Lista de conturi: "<<endl;
    afisare_conturi(b);

    cout<<endl<<"Optiuni disponibile: "<<endl;
    cout<<endl<<"1. Sterge un cont"<<endl;
    cout<<endl<<"2. Sterge toate conturile "<<endl;
    cout<<endl<<"3. Back"<<endl;
    int x;
    cin>>x;

    while(x < 1 || x > 3)
    {
        cout<<endl<<"Optiunea selectata anterior nu exista. Alege una din optiunile de mai jos"<<endl;
        cout<<endl<<"Optiuni disponibile: "<<endl;
        cout<<endl<<"1. Sterge un cont"<<endl;
        cout<<endl<<"2. Sterge toate conturile "<<endl;
        cout<<endl<<"3. Back"<<endl;
        cin>>x;
    }

    if(x == 1)
    {
        int y;
        cout<<endl<<"Alege un index corespunzator unui cont pentru a-l sterge Sau Scrie 0 pentru a iesi"<<endl;
        cin>>y;

        while(y < 0 || y > b->getnrconturi())
            {cout<<endl<<"Indexul introdus nu exista in lista. Reintrodu indexul corespunzator"<<endl;
            cin>>y;}

        if(y != 0)
            b->eliminare_membru(y);
    }

    else if(x == 2)
    {
        clear();
        int alegere;
        cout<<"Doresti sa stergi toate conturile ? "<<endl;
        cout<<"1. DA "<<endl;
        cout<<"2. NU "<<endl;
        cin>>alegere;

        while(alegere < 1 || alegere > 2)
        {
            clear();
            cout<<"Optiunea selectata anterior nu exista. Alege una din optiunile de mai jos"<<endl;
            cout<<"Doresti sa stergi toate conturile ? "<<endl;
            cout<<"1. DA "<<endl;
            cout<<"2. NU "<<endl;
            cin>>alegere;
        }

        if(alegere == 1)
            for(int i = 0; i < b->getnrconturi(); i++)
            {
                b->eliminare_membru(i + 1);
                i--;
            }
    }

    clear();
    //cout<<"Contul a fost sters cu succes"<<endl;
}

void meniu_accesare_dupa_id(banca *b)
{
    int id, k = 0;

    while(k == 0)
    {

        cout<<"Introdu ID-ul: ";cin>>id;
    cout<<endl;

    for(int i = 0; i < b->getnrconturi(); i++)
    {
        if(b->get_id(i) == id)
        {
            meniu_fct_cont(b, i + 1);
            i = b->getnrconturi() + 1;
            k = 1;
        }
    }

    if(k == 0)
    {
        int alegere;
        clear();
        cout<<"Nu exista un cont cu ID-ul introdus. Doresti sa reintroduci un ID ?"<<endl;
        cout<<"1. DA"<<endl;
        cout<<"2. NU"<<endl;
        cout<<endl;
        cin>>alegere;

        while(alegere < 1 || alegere > 2)
        {
            clear();
            cout<<"Optiunea selectata anterior nu exista. Alege una din optiunile de mai jos"<<endl;
            cout<<"Doresti sa reintroduci un ID ?"<<endl;
            cout<<"1. DA"<<endl;
            cout<<"2. NU"<<endl;
            cout<<endl;
            cin>>alegere;
        }

        if(alegere == 2)
            k = 1;
    }

    }
    clear();
}

void meniu_stergere_dupa_id(banca *b)
{
    int id, k = 0, x;

    cout<<endl<<"Optiuni disponibile: "<<endl;
    cout<<endl<<"1. Sterge un cont dupa ID "<<endl;
    cout<<endl<<"2. Back"<<endl;
    cin>>x;
    clear();

    while(x < 1 || x > 2)
    {
        clear();
        cout<<endl<<"Optiunea selectata anterior nu exista. Alege una din optiunile de mai jos"<<endl;
        cout<<endl<<"Optiuni disponibile: "<<endl;
        cout<<endl<<"1. Sterge un cont dupa ID"<<endl;
        cout<<endl<<"2. Back"<<endl;
        cin>>x;
    }

    while(k == 0 && x == 1)
    {

        cout<<"Introdu ID-ul: ";cin>>id;
    cout<<endl;

    for(int i = 0; i < b->getnrconturi(); i++)
    {
        if(b->get_id(i) == id)
        {
            b->eliminare_membru(i + 1);
            i = b->getnrconturi() + 1;
            k = 1;
        }
    }

    if(k == 0)
    {
        int alegere;
        clear();
        cout<<"Nu exista un cont cu ID-ul introdus. Doresti sa reintroduci un ID ?"<<endl;
        cout<<"1. DA"<<endl;
        cout<<"2. NU"<<endl;
        cout<<endl;
        cin>>alegere;

        while(alegere < 1 || alegere > 2)
        {
            clear();
            cout<<"Optiunea selectata anterior nu exista. Alege una din optiunile de mai jos"<<endl;
            cout<<"Doresti sa reintroduci un ID ?"<<endl;
            cout<<"1. DA"<<endl;
            cout<<"2. NU"<<endl;
            cout<<endl;
            cin>>alegere;
        }

        if(alegere == 2)
            k = 1;
    }

    }
    clear();
}

void output_fisier(banca *b) // functie de afisare conturi in fisier
{
    ofstream f("date.txt");
    if(f.is_open())
    {
    f<<b->getnrconturi()<<endl;
    for(int i = 0; i < b->getnrconturi(); i++)
    {
        f<<b->get_nume(i)<<endl;
        f<<b->get_prenume(i)<<endl;
        f<<b->get_id(i)<<endl;
        f<<b->get_deposit(i)<<endl;
        f<<b->get_inghet_cont_anume(i)<<endl;
        f<<b->get_moneda(i)<<endl;
    }
    f.close();
    }
}

void input_fisier(banca *b) // functie de citire conturi din fisier
{
    ifstream f("date.txt");
    char nume[50], prenume[50];
    int id, suma, conturi, k = 0;
    bool inghet;
    string s;

    if(f.is_open())
    {
    f>>conturi;

    for(int i = 0; i < conturi; i++)
    {
        f>>nume>>prenume>>id>>suma>>inghet>>s;
        k = 0;
        for(int j = 0; j < b->getnrconturi(); j++)
        {
        if(b->get_nume(j) == nume && b->get_prenume(j) == prenume)
            {
                account *c = new account(id, suma, *b->get_persoana_cont_anume(j), s);
                b->adaugare_membru(*c);
                k = 1;
                j = b->getnrconturi() + 1;
                //cout<<"AICIIIIIIIIIIIIIIIIIIIIIII"<<endl;
            }

        }
        if(k == 0)
        {
            persoana *a = new persoana(nume, prenume);
            account *c = new account(id, suma, *a, s, inghet);
            b->adaugare_membru(*c);
        }
    }
    }
    else ofstream f("date.txt");
    f.close();
}

int main()
{
    banca b;
    input_fisier(&b);
    int x = -1;

    while(x != 6)
    {
        cout<<"Main Menu";
        cout<<"\n1.Creare cont.";
        cout<<"\n2.Lista conturi.";
        cout<<"\n3.Accesare cont dupa ID";
        cout<<"\n4.Stergere cont";
        cout<<"\n5.Stergere cont dupa ID";
        cout<<"\n6.Exit";
        cout<<"\nIntroduceti optiunea (1-6):";
        cin>>x;

        while(x <= 0 || x > 6)
        {
            clear();
            cout<<"Optiunea selectata anterior nu exista. Alege una din optiunile de mai jos"<<endl;
            cout<<"Main Menu";
            cout<<"\n1.Creare cont.";
            cout<<"\n2.Lista conturi.";
            cout<<"\n3.Accesare cont dupa ID";
            cout<<"\n4.Stergere cont";
            cout<<"\n5.Stergere cont dupa ID";
            cout<<"\n6.Exit";
            cout<<"\nIntroduceti optiunea (1-6):";
            cin>>x;
        }

        if(x == 1)
        {
            adaugare_cont(&b);
            clear();
            //cout<<"\nContul a fost creat"<<endl;
        }

        if(x == 2)
        {
            clear();
            //afisare_lista_conturi(b);
            //clear();
            cout<<"Lista de conturi: "<<endl;
            b.afisare();
            afisare_lista_conturi(&b);
        }

        if(x == 3)
        {
            clear();
            meniu_accesare_dupa_id(&b);
        }

        if(x == 4)
        {
            clear();
            stergere_cont(&b);
        }

        if(x == 5)
        {
            clear();
            meniu_stergere_dupa_id(&b);
        }
    }
    output_fisier(&b);
    return 0;
}
