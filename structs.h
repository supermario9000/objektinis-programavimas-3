#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


using std::string;
using std::move;
using std::istream;
using std::ostream;

class Zmogus { // Zmogus yra bazinė klasė, kuri bus naudojama kaip pagrindas kitoms klasėms
protected:
    string vardas_, pavarde_; //protected leidžia prieiti prie šių kintamųjų iš paveldėtų klasių
public:
    Zmogus() = default;
    Zmogus(const string& vardas, const string& pavarde) //konstruktorius su parametrais
        : vardas_(vardas), pavarde_(pavarde) {}

    virtual ~Zmogus() = default;  //virtual destruktorius leidžia tinkamai išvalyti išteklius, jei klasė yra paveldima

    // Getteriai
    string vardas() const { return vardas_; }
    string pavarde() const { return pavarde_; }

    // Setteriai
    void setVardas(const string& vardas) { vardas_ = vardas; }
    void setPavarde(const string& pavarde) { pavarde_ = pavarde; }

    // abstraktus metodas, kuris bus privalomas visoms paveldėtoms klasėms
    virtual void spausdinti() const = 0; // sis metodas padaro, kad Zmogus yra abstrakti klase, kuri negali buti sukurta tiesiogiai
};

class stud : public Zmogus { // stud yra studento klasė, kuri paveldi Zmogus klasę
    private: // privatus kintamieji, kurie bus naudojami tik klasės viduje (apibudinti objekta)
        vector<int> pazymiai_;
        int egzrez_; //egzaminų rezultatas
        double galutinis_, med_; //galutiniai rezultatai
    public:
    stud() = default; //defaultinis konstruktorius
    stud(const string& vardas, const string& pavarde,
              const vector<int>& pazymiai, int egzrez)
        : Zmogus(vardas, pavarde), pazymiai_(pazymiai), egzrez_(egzrez) {}

    // Copy
    stud(const stud& other)
        : Zmogus(other.vardas_, other.pavarde_),
          pazymiai_(other.pazymiai_), egzrez_(other.egzrez_),
          galutinis_(other.galutinis_), med_(other.med_) {}

    // Move
    stud(stud&& other) noexcept
        : Zmogus(move(other.vardas_), move(other.pavarde_)),
          pazymiai_(move(other.pazymiai_)), egzrez_(other.egzrez_),
          galutinis_(other.galutinis_), med_(other.med_) {
        other.egzrez_ = 0;
        other.galutinis_ = 0.0;
        other.med_ = 0.0;
    }

    // Copy 
    stud& operator=(const stud& other) //iskvieciamas taip: stud a,b; a=b;
    {
        if (this != &other)//this - tas objektas, i kuri kopijuojame arba perkeliame duomenis
        {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            pazymiai_ = other.pazymiai_;
            egzrez_ = other.egzrez_;
            galutinis_ = other.galutinis_;
            med_ = other.med_;
        }
        return *this;
    }

    // Move operatorius (kuris perkelia objekto vertes i kita objekta)
    stud& operator=(stud&& other) noexcept //noexcept leidzia nurodyti, kad operacija gali nepavykti
    { //iskvieciamas taip: stud a,b; a=move(b); Tai reiskia, b bus perkeltas i a.
        if (this != &other) 
        {
            vardas_ = move(other.vardas_);
            pavarde_ = move(other.pavarde_);
            pazymiai_ = move(other.pazymiai_);
            egzrez_ = other.egzrez_; //sitie perkeliami automatiskai, nes tai yra primityvus tipas
            galutinis_ = other.galutinis_;
            med_ = other.med_;

            other.egzrez_ = 0; //panaikiname objekte uzsilikusius skaicius (kadangi jie nera sudetingesni konteineriai, ju move nepanaikina)
            other.galutinis_ = 0.0;
            other.med_ = 0.0;
        }
        return *this;
    }

    // destruktorius
    ~stud() = default; // default destruktorius, kuris automatiškai išvalys išteklius (neisveda kai istrina, nes trukdo testavimui)

    // Setteriai
    void addPazymys(int pazymys) { pazymiai_.push_back(pazymys); }
    void setEgzaminas(int egz) { egzrez_ = egz; }
    void setGalutinis(double g) { galutinis_ = g; }
    void setMediana(double m) { med_ = m; }

    // Getteriai
    vector<int> pazymiai() const { return pazymiai_; }
    int egzrez() const { return egzrez_; }
    double galutinis() const { return galutinis_; }
    double med() const { return med_; }

    // metodai (prasmatnus setteriai)
    void skaiciuotiVidurki() 
    {
        if (pazymiai_.empty()) 
        {// jei pazymiu nera, tai galutinis rezultatas yra lygus egzaminų rezultatui
            galutinis_ = egzrez_;
            return;
        }
        double sum = 0;
        for (int p : pazymiai_) sum += p;
        double vid = sum / pazymiai_.size();
        galutinis_ = 0.4 * vid + 0.6 * egzrez_;
    }

    void skaiciuotiMediana() 
    {
        if (pazymiai_.empty()) {
            med_ = egzrez_;
            return;
        }
        sort(pazymiai_.begin(), pazymiai_.end());
        size_t n = pazymiai_.size();
        double median = (n % 2 == 0) ? (pazymiai_[n/2 - 1] + pazymiai_[n/2]) / 2.0 : pazymiai_[n/2]; //salyga ? teisinga : klaidinga
        med_ = 0.4 * median + 0.6 * egzrez_;
    }

    // Išvesties metodas (perdengia abstraktų Zmogus klasės metodą)
    void spausdinti() const override {
        cout << setw(15) << left << vardas_ << setw(15) << left << pavarde_ << setw(10) << fixed << setprecision(2) << galutinis_<< fixed << setprecision(2) << med_ << endl;
    }
 
    // friend funkcijos leidzia naudoti operatorius su klase stud
    friend istream& operator>>(istream& in, stud& s);
    friend ostream& operator<<(ostream& out, const stud& s);
};

//skaitymo ir rasymo operatoriai:
istream& operator >>(istream& in, stud& s) {
    in >> s.vardas_ >> s.pavarde_;
    int paz;
    char simbolis;
    while (in >> paz) {
        simbolis = in.peek(); // in.peek pasiziuri koks kitas charas yra sraute.
        if (simbolis == '\n') {
            s.egzrez_ = paz; // paskutinis pazymys yra egzaminų rezultatas (nukopijuojama reiksme)
            in.get(); //panaikiname \n is srauto
            break;
        } else {
            s.pazymiai_.push_back(paz);
            in.get(); //panaikiname tarpa arba kita simboli po pazymio
        }
    }

    s.skaiciuotiVidurki();
    s.skaiciuotiMediana();
    return in;
}

    // isvesties operatorius <<
ostream& operator <<(ostream& out, const stud& s) {
    //antraste apdorojama atskirai
    out << setw(15) << left << s.vardas_ << setw(15) << left << s.pavarde_ << setw(10) << left << fixed << setprecision(2) << s.galutinis_ << fixed << setprecision(2) << s.med_ << endl;
    return out;
}

#endif // STRUCTS_H
