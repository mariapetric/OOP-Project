#include <iostream>
#include <vector>
#include <string>

using namespace std;
// SIMULATOR DE TRAFIC URBAN

class Vehicul {
public:
    enum class Directie {Sus, Jos, Stanga, Dreapta};
private:
    int id = 0;
    string tip;
    double viteza = 0.0;
    pair <int, int> pozitie;
    Directie directie = Directie::Sus;

public:
    //constructor de initializare fara param
    Vehicul() = default;

    //constructor parametrizabil
    explicit Vehicul(const int id, const string& tip, const double viteza, const pair <int, int> pozitie, Directie directie) :
        id {id}, tip {tip}, viteza {viteza}, pozitie {pozitie}, directie {directie} {}

    //constructor de copiere
    Vehicul(const Vehicul& other) : id {other.id}, tip {other.tip}, viteza {other.viteza}, pozitie {other.pozitie}, directie {other.directie} {}

    //operator de copiere
    Vehicul& operator=(const Vehicul& other) {
        this->id = other.id;
        this->tip = other.tip;
        this->viteza = other.viteza;
        this->pozitie = other.pozitie;
        this->directie = other.directie;
        return *this;
    }

    //destructor
    ~Vehicul() = default;

private:
    string directieToString() const {
        switch(directie) {
            case Directie::Sus: return "Sus";
            case Directie::Jos: return "Jos";
            case Directie::Stanga: return "Stanga";
            case Directie::Dreapta: return "Dreapta";
            default: return "Necunoscut";
        }
    }

public:
    //incarcare de operator
    friend ostream& operator<<(ostream& os, const Vehicul& obj) {
        os << "[ Vehicul ID: " << obj.id
           << ", tip: " << obj.tip
           << ", viteza: " << obj.viteza
           << ", pozitie: " << obj.pozitie.first << ", " << obj.pozitie.second
           << ", directie: " << obj.directieToString() << " ]";
        return os;
    }

    // Functii membre
    void SetPozitie(pair <int, int> p);
    void Muta (int distanta);
    void SchimbaViteza (int nouaViteza);
    void SchimbaDirectia (Directie nouaDirectie);
    bool DepasesteLimita (int limita) const;
};

// Setter pentru pozitie
void Vehicul::SetPozitie (const pair<int, int> p) {
    pozitie = p;
}

// Functie care muta vehiculul
void Vehicul::Muta (int distanta) {
    switch (directie) {
        case Directie::Sus: { pozitie.second += distanta;  break; }
        case Directie::Jos: { pozitie.second -= distanta;  break; }
        case Directie::Stanga: { pozitie.first -= distanta;  break; }
        case Directie::Dreapta: { pozitie.first += distanta;  break; }
    }
}

// Functie care schimba viteza masinii
void Vehicul::SchimbaViteza (int nouaViteza) {
    if (nouaViteza >= 0)
        viteza = nouaViteza;
}

// Functie care schimba directia vehiculului
void Vehicul::SchimbaDirectia (Directie nouaDirectie) {
    directie = nouaDirectie;
}

// Functia care verifica daca vehiculul depaseste limita de viteza
bool Vehicul::DepasesteLimita (int limita) const {
    return viteza > limita;
}




class Semafor {
public:
    enum class Culoare { Rosu, Galben, Verde };
private:
    Culoare culoare = Culoare::Verde;
    int durataVerde = 0, durataGalben = 0, durataRosu = 0, timpCurent = 0;

public:
    //constructor fara param
    Semafor() = default;

    //constructor parametrizabil
    explicit Semafor(Culoare culoare, const int durataVerde, const int durataGalben, const int durataRosu, const int timpCurent) :
        culoare {culoare}, durataVerde {durataVerde}, durataGalben {durataGalben}, durataRosu {durataRosu}, timpCurent {timpCurent} {}

    //constructor de copiere
    Semafor(const Semafor& other) : culoare {other.culoare}, durataVerde {other.durataVerde}, durataGalben {other.durataGalben},
            durataRosu {other.durataRosu}, timpCurent {other.timpCurent} {}

    //operator de copiere
    Semafor& operator=(const Semafor& other) {
        this->culoare = other.culoare;
        this->durataVerde = other.durataVerde;
        this->durataGalben = other.durataGalben;
        this->durataRosu = other.durataRosu;
        this->timpCurent = other.timpCurent;
        return *this;
    }

    //destructor
    ~Semafor() = default;

private:
    string culoareToString() const {
        switch (culoare) {
            case Culoare::Rosu: return "Rosu";
            case Culoare::Galben: return "Galben";
            case Culoare::Verde: return "Verde";
            default: return "Necunoscut";
        }
    }

public:
    //incarcare de operator
    friend ostream& operator<<(ostream& os, const Semafor& obj) {
        os << "[ Semafor culoare: " << obj.culoareToString()
           << ", durata verde: " << obj.durataVerde
           << ", durata galben: " << obj.durataGalben
           << ", durata rosu: " << obj.durataRosu
           << ", timp curent: " << obj.timpCurent << " ]";
        return os;
    }

    // Functii membre
    void TrecereTimp (int secunde);
    bool EsteRosu () const;
    bool EsteGalben () const;
    bool EsteVerde () const;
};


// Functie pentru actualizarea timpului si resetarea culorii, daca e cazul
void Semafor::TrecereTimp (int secunde) {
    timpCurent += secunde;
    switch (culoare) {
        case Culoare::Rosu: {
            if (timpCurent >= durataRosu) {
                culoare = Culoare::Verde;
                timpCurent = 0;
            }
            break;
        }
        case Culoare::Galben: {
            if (timpCurent >= durataGalben) {
                culoare = Culoare::Rosu;
                timpCurent = 0;
            }
            break;
        }
        case Culoare::Verde: {
            if (timpCurent >= durataVerde) {
                culoare = Culoare::Galben;
                timpCurent = 0;
            }
            break;
        }
    }
}

// Functii pentru verificarea starii semaforului
bool Semafor::EsteRosu () const {
    return culoare == Culoare::Rosu;
}

bool Semafor::EsteGalben () const {
    return culoare == Culoare::Galben;
}

bool Semafor::EsteVerde () const {
    return culoare == Culoare::Verde;
}




class Strada { //are compunere
private:
    string nume;
    int lungime = 0;
    Vehicul::Directie directie = Vehicul::Directie::Sus;
    pair <int, int> coordonataStart;

    vector <Vehicul> vehicule;
    vector < pair<Semafor, int> > semafoare;

public:
    //constructor fara parametri
    Strada() = default;

    //constructor parametrizabil
    explicit Strada(const string& nume, const int lungime, Vehicul::Directie directie, const pair<int, int> coordonataStart,
        const vector <Vehicul>& vehicule, const vector <pair<Semafor, int> >& semafoare) :
        nume {nume}, lungime {lungime}, directie {directie}, coordonataStart{coordonataStart},
        vehicule {vehicule}, semafoare {semafoare} {}

    //constructor de copiere
    Strada(const Strada& other) : nume {other.nume}, lungime {other.lungime}, directie {other.directie}, coordonataStart{other.coordonataStart},
        vehicule {other.vehicule}, semafoare {other.semafoare} {}

    //operator de copiere
    Strada& operator=(const Strada& other) {
        this->nume = other.nume;
        this->lungime = other.lungime;
        this->directie = other.directie;
        this->coordonataStart = other.coordonataStart;
        this->vehicule = other.vehicule;
        this->semafoare = other.semafoare;
        return *this;
    }

    //destructor
    ~Strada() = default;

private:
    string directieToString() const {
        switch(directie) {
            case Vehicul::Directie::Sus: return "Sus";
            case Vehicul::Directie::Jos: return "Jos";
            case Vehicul::Directie::Stanga: return "Stanga";
            case Vehicul::Directie::Dreapta: return "Dreapta";
            default: return "Necunoscut";
        }
    }

public:
    //incarcare de operator
    friend ostream& operator<<(ostream& os, const Strada& obj) {
        os << "[ Strada nume: " << obj.nume
           << ", lungime: " << obj.lungime
           << ", directie: " << obj.directieToString()
           << ", coordonataStart: (" << obj.coordonataStart.first << ", " << obj.coordonataStart.second << ")"
           << ", vehicule: ";
        if (!obj.vehicule.empty()) {
            for (const auto& v : obj.vehicule) {
                os << v << ", ";
            }
        }
        os << ", semafoare: ";
        if (!obj.semafoare.empty()) {
            for (const auto& v : obj.semafoare) {
                os << v.second << ", ";
            }
        }
        os << " ]";
        return os;
    }

    // Functii membre
    pair <int, int> GetCoordonataStart() const;
    int GetLungime() const;
    Vehicul::Directie GetDirectie() const;
    vector<Vehicul>& GetVehicule();

    void AdaugaVehicul (const Vehicul& v, bool sens = true);
    void AdaugaSemafor (const Semafor& s, int distanta);
    void EliminaSemaforLaDistanta (int distanta);

private:
    void SincronizareSemafor (int index);
};

pair<int, int> Strada::GetCoordonataStart() const {
    return coordonataStart;
}

int Strada::GetLungime () const {
    return lungime;
}

Vehicul::Directie Strada::GetDirectie() const {
    return directie;
}

vector<Vehicul>& Strada::GetVehicule() {
    return vehicule;
}

// Functie pentru adaugarea unui vehicul pe strada la coord de start sau lungime
void Strada::AdaugaVehicul (const Vehicul& v, bool sens) {
    Vehicul copie = v;
    pair <int, int> pozitieStart = coordonataStart;
    if (sens)
        copie.SchimbaDirectia (directie);
    else {
        switch (directie) {
            case Vehicul::Directie::Sus: {
                copie.SchimbaDirectia (Vehicul::Directie::Jos);
                pozitieStart.second += lungime;
                break;
            }
            case Vehicul::Directie::Jos: {
                copie.SchimbaDirectia (Vehicul::Directie::Sus);
                pozitieStart.second -= lungime;
                break;
            }
            case Vehicul::Directie::Dreapta: {
                copie.SchimbaDirectia (Vehicul::Directie::Stanga);
                pozitieStart.first -= lungime;
                break;
            }
            case Vehicul::Directie::Stanga: {
                copie.SchimbaDirectia (Vehicul::Directie::Dreapta);
                pozitieStart.first += lungime;
                break;
            }
        }
    }
    copie.SetPozitie (pozitieStart);
    vehicule.push_back(copie);
}

// Functie pentru sincronizare semafor nou adaugat
void Strada::SincronizareSemafor(int index) {
    if (!semafoare.empty() && index > 0 && index < (int)semafoare.size()) {
        semafoare[index].first = semafoare[0].first;
    }
}

// Functie pentru adaugarea unui semafor la o anumita coordonata
void Strada::AdaugaSemafor (const Semafor& s, int distanta) {
    if (distanta >= 0 && distanta <= lungime) {
        semafoare.push_back({s, distanta});
        SincronizareSemafor ( semafoare.size() - 1 );
    }
}

// Functie care elimina semaforul de la o anumita distanta, daca acesta exista
void Strada::EliminaSemaforLaDistanta (int distanta) {

    for (auto it = semafoare.begin(); it !=semafoare.end(); ++it)
        if (it->second == distanta) {
            semafoare.erase(it);
            return;
        }
}


class Intersectie {
    string nume;
    pair <int, int> coordonate;
    vector <Strada> strazi;
    vector <Semafor> semafoare;

public:
    //constructor fara param
    Intersectie() = default;

    //constructor parametrizabil
    explicit Intersectie(const string& nume, const pair<int, int> coordonate, const vector <Strada>& strazi, const vector <Semafor>& semafoare) :
        nume {nume}, coordonate {coordonate}, strazi {strazi}, semafoare {semafoare} {}

    //constructor de copiere
    Intersectie(const Intersectie& other) : nume {other.nume}, coordonate {other.coordonate}, strazi {other.strazi}, semafoare {other.semafoare} {}

    //operator de copiere
    Intersectie& operator=(const Intersectie& other) {
        this->nume  = other.nume;
        this->coordonate = other.coordonate;
        this->strazi = other.strazi;
        this->semafoare = other.semafoare;
        return *this;
    }

    //destructor
    ~Intersectie() = default;

    //incarcare de operator
    friend ostream& operator<<(ostream& os, const Intersectie& obj) {
        os << "[ Semafor nume: " << obj.nume
        << ", coordonate: ( " << obj.coordonate.first << ", " << obj.coordonate.second << " )"
        << ", strazi: ";
        if (!obj.strazi.empty()) {
            for (const auto& s : obj.strazi) {
                os << s << ", ";
            }
        }
        os << "  , semafoare: ";
        if (!obj.semafoare.empty()) {
            for (const auto& s : obj.semafoare) {
                os << s << ", ";
            }
        }
        os << " ]";
        return os;
    }

    // Functii membre
    void AdaugaStrada (const Strada& s);
    void AdaugaSemaforizareStrazi ();
    int NumarTotalVehicule ();

};

// Functie pentru adaugarea unei strazi in intersectie
void Intersectie::AdaugaStrada (const Strada& s) {
    strazi.push_back(s);
}

// Pune semafoare la intersectie pe strazile care compun intersectia
void Intersectie::AdaugaSemaforizareStrazi() {
    for (auto& strada: strazi) {
        pair <int, int> start = strada.GetCoordonataStart();
        Vehicul::Directie directie = strada.GetDirectie();

        int distSens = 0, distContrasens = 0;

        switch (directie) {
            case Vehicul::Directie::Dreapta: {
                distSens = coordonate.first - start.first - 1;
                distContrasens = coordonate.first - start.first + 1;
                break;
            }
            case Vehicul::Directie::Stanga: {
                distSens = start.first - coordonate.first - 1;
                distContrasens = start.first - coordonate.first + 1;
                break;
            }
            case Vehicul::Directie::Sus: {
                distSens = coordonate.second - start.second - 1;
                distContrasens = coordonate.second - start.second + 1;
                break;
            }
            case Vehicul::Directie::Jos: {
                distSens = start.second - coordonate.second - 1;
                distContrasens = start.second - coordonate.second + 1;
                break;
            }
        }

        strada.EliminaSemaforLaDistanta (distSens);
        strada.EliminaSemaforLaDistanta (distContrasens);

        Semafor s1;
        Semafor s2;
        if (distSens >= 0 && distSens <= strada.GetLungime())
            strada.AdaugaSemafor (s1, distSens);
        if (distContrasens >= 0 && distContrasens <= strada.GetLungime())
            strada.AdaugaSemafor (s2, distContrasens);
    }
}

// Functie care returneaza numarul de vehicule de pe toate strazile din intersectie
int Intersectie::NumarTotalVehicule () {
    int total = 0;
    for (auto& strada: strazi) {
        total += strada.GetVehicule().size();
    }
    return total;
}

int main() {
    //Cream vehicule
    Vehicul v1(1, "Masina", 60, {0, 0}, Vehicul::Directie::Dreapta);
    Vehicul v2(2, "Autobuz", 40, {0, 0}, Vehicul::Directie::Dreapta);


    v1.Muta(5);
    v1.SchimbaViteza(70);
    v1.SchimbaDirectia(Vehicul::Directie::Jos);
    cout << "V1 depaseste limita 50? " << (v1.DepasesteLimita(50) ? "Da" : "Nu") << endl;

    v2.SetPozitie({5, 5});
    v2.Muta(3);
    cout << v1 << endl;
    cout << v2 << endl;

    //Cream un semafor
    Semafor s1(Semafor::Culoare::Rosu, 10, 3, 7, 0);
    s1.TrecereTimp(8);
    cout << "Semaforul este rosu? " << (s1.EsteRosu() ? "Da" : "Nu") << endl;
    cout << "Semaforul este galben? " << (s1.EsteGalben() ? "Da" : "Nu") << endl;
    cout << "Semaforul este verde? " << (s1.EsteVerde() ? "Da" : "Nu") << endl;
    cout << s1 << endl;

    //Cream o stradă
    Strada strada1("Bd. Unirii", 20, Vehicul::Directie::Dreapta, {0, 0}, {}, {});
    strada1.AdaugaVehicul(v1);
    strada1.AdaugaVehicul(v2, false); // adaugat in sens opus
    strada1.AdaugaSemafor(s1, 5); // adaugam un semafor la distanta 5
    strada1.EliminaSemaforLaDistanta(5); // il eliminam
    strada1.AdaugaSemafor(s1, 7); // adaugam din nou

    cout << strada1 << endl;

    //Cream o intersectie
    Intersectie intersectie("Piata Universitatii", {10, 0}, {}, {});
    intersectie.AdaugaStrada(strada1);

    intersectie.AdaugaSemaforizareStrazi();

    int nrVehicule = intersectie.NumarTotalVehicule();
    cout << "Numar total vehicule in intersectie: " << nrVehicule << endl;

    cout << intersectie << endl;

    return 0;
}


// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.
