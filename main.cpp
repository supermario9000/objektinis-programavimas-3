// pagrindine funkcija, kuri jungia visus kitus failus
//ja galima vadinti ir misria programa
#include "MasyvMain.cpp"
#include "VectorMain.cpp"

int main() // is esmes pagrindinio meniu funkcija
{
    cout << "Pazymiu surasymo studentams programa (PSSP)" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Produkta kure Marijus Kuprys" << endl;
    cout << "Kopijuoti ar plagijuoti draudziama" << endl;
    cout << "Isbandant koda uz jusu duomenis ir failus kurejai neatsako" << endl;
    cout << "Tokiu atveju jei jusu irenginys bus uzkrestas virusu, kurejai neatsako"<<endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << '\n'
         << endl;
    cout << "Kokia versija norite pasirinkti?" << endl;
    int temp;
    string input;
    while (true)
    {
        cout << "1 - pasirinkti versija su masyvais" << endl;
        cout << "2 - pasirinkti versija su vektoriais (Pagrindine)" << endl;
        cout << "Pasirinkite: ";

        cin >> input;

        try {
            temp = stoi(input); // convert string to int
            if (temp < 1 || temp > 3) {
                throw std::out_of_range("Pasirinkimas turi buti tarp 1 ir 3.");
            }
            break; // valid input, exit the loop
        } catch (const std::invalid_argument&) {
            cout << "Netinkama ivestis. Iveskite skaiciu!" << endl;
        } catch (const std::out_of_range& e) {
            cout << e.what() << endl;
        }
    }

    if (temp == 1)
    {
        pasirinkimai();
        cin >> temp;
        masyvai(temp);
    }
    else if (temp == 2)
    {
        pasirinkimai();
        cout<<"4 - duomenu ivestis ir isvedimas is failu"<<endl;
        cout<<"5 - failu su studentu rezultatais generavimas"<<endl;
        cout<<"6 - klases operatoriu, konstruktoriu testavimas"<<endl; 
        cin >> temp;
        vektoriai(temp);
    }
    cout << '\n'
         << endl;
    cout << "Aciu, kad naudojotes mano programa" << endl;
    cout << "Ar patiko?[y/n]:";
    char temporarinis;
    cin >> temporarinis;//kad programa iskart neuzsidarytu
    return 0;
}