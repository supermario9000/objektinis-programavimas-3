#include "mylib.h"
#include "structs.h"

void masyvaiRanka(stud S[])
{
    int i = 0;
    while (true)
    {
        string vardas = "", pavarde = "";
        cout << "Iveskite studento varda (arba 'n', jei ivedete visus studentu duomenis):" << endl;
        cin >> vardas;
        if (vardas == "n")
            {
                break;
            }
        S[i].setVardas(vardas);
        cout << "Iveskite studento pavarde:" << endl;
        cin >> pavarde;
        S[i].setPavarde(pavarde);
        cout << "Iveskite studento namu darbu pazymius, po kiekvieno spauskite enter, jei studentas negavo visu pazymiu, ivedus visus iveskite n:" << endl;
        int j=0;
        //pazymiu ivedimas
        while (true)
        {
            string input;//reikia dar paziuret ar deklaravimas nesukels problemu
            cout << "Iveskite studento " << j + 1 << " namu darbu pazymi (arba 'n', jei norite baigti pazymiu ivedima): ";
            cin >> input;
            if (input == "n")
                break;
            try {
                if (arpazymys(stoi(input)) == false)
                    {
                        throw std::out_of_range("Pazymys turi buti tarp 0 ir 10!");
                        j--;
                    }
                else S[i].addPazymys(stoi(input));
            }
            catch (const std::invalid_argument&) {
                cout << "Netinkama ivestis. Iveskite skaiciu!" << endl;
            }
            j++;
        }

        // Egzamino rezultato ivedimas
        while (true)
        {
            string input;
            cout << "Iveskite studento egzamino rezultata: ";
            cin >> input;
            try {
                if (arpazymys(stoi(input)) == false)
                    throw std::out_of_range("Egzamino rezultatas turi buti tarp 0 ir 10!");
                S[i].setEgzaminas(stoi(input));
                break;
            }
            catch (const std::invalid_argument&) {
                cout << "Netinkama ivestis. Iveskite skaiciu!" << endl;
            }
        }
        i++;//loopas kartojasi kol neparasoma 'n'
    }
}

void puseRandMas(stud S[], int n, int m) // puse random sugeneruotu reiksmiu masyvine versija
{
    int i = 0; // nusinulinu indeksa
    for (int i = 0; i < n; i++)
    {
        string vardas = "", pavarde = "";
        cout << "Iveskite kito studento varda (arba 'n', jei ivedete visus studentu duomenis):" << endl;
        cin >> vardas;
        if (vardas == "n")
        {
            break; // jei ivedamas n, nutraukiam cikla
        }
        S[i].setVardas(vardas);
        cout << "Iveskite studento pavarde:" << endl;
        cin >> pavarde;
        S[i].setPavarde(pavarde);
        cout << "Sugeneruoti namu darbu pazymiai:";
        for (int j = 0; j < m; j++)
        {
            S[i].addPazymys(randominis());
        }
        cout << endl
             << "Sugeneruotas egzamino rezultato pazymys:";
        S[i].setEgzaminas(randominis());
        cout << S[i].egzrez() << endl;
    }
}

void visRandMas(stud S[], int n, int m) //pasirodo netvarkiau masyvu funkciju :(
{
    for (int i = 0; i < n; i++)
    {
        S[i].setVardas(Vardas[randominis()]);
        S[i].setPavarde(Pavarde[randominis()]);
        for (int j = 0; j < m; j++)
        {
            S[i].addPazymys(randominis());
        }
        S[i].setEgzaminas(randominis());
    }
}

void vidurkis(stud S[], int n) // vidurkio suskaiciavimo funkcija
{
    for (int i = 0; i < n; i++)
    {
        S[i].skaiciuotiVidurki(); // kiekvienam studentui skaiciuojame vidurki
    }
}

// tikrinau funkcija, mediana tikrai surandama teisingai, tik keistai skiriasi nuo vidurkio po skaiciavimu
void mediana(int n, int m, stud S[]) // medianos apskaiciavimas (pasirodo reik rezultata padaugint is 0.4 ir pridet egzo rezultata)
{
    for (int i = 0; i < n; i++)
    {
        S[i].skaiciuotiMediana(); // kiekvienam studentui skaiciuojame mediana
    }
}

void spausdinimas(stud S[], int n)
{
    cout << setw(15) << left << "Vardas " << setw(15) << left << "Pavarde " << setw(10) << left << "Vidurkis " << "Mediana" << endl;
    for (int i = 0; i < n; i++)
    {
        if (S[i].vardas() == "n") // jei netycia ivestas n
            break;
        cout << setw(15) << left << S[i].vardas() << setw(15) << left << S[i].pavarde() << setw(10) << left << fixed << setprecision(2) << S[i].galutinis() << S[i].med() << endl;
    }
}
