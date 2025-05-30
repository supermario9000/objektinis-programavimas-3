#include "programaVektoriai.cpp"

int vektoriai(int TEMP)
{
    Vector<stud> S, nuskriaustieji, rimtuoliai;

    if (TEMP == 1)
        vektoriaiRanka(S);
    else if (TEMP == 2)
        pusRandVek(S);
    else if (TEMP == 4)
        skaityk(S);
    else if (TEMP == 6)//ikisau cia, maniau taip lengviau surasti
        {
            testClass();
            return 0; // testavimas baigtas, graziname 0, kad programa baigtu darba
        }
    else if (TEMP == 5)
        generuotif();//failu generavimas, kuriam nereikalingas jokio studento ivedimas
    else //pvz if == 3
    {
        if (TEMP != 3)
            cout << "Pasirinkote klaidingai, aktyvuosime visu duomenu generavima..." << endl;
        visRandVek(S);
    }
    if (TEMP!=5) //jei nepasirinktas failu generavimas, programa vykdoma kaip iprasta
    {
        cout<<"Kaip noresite surikiuoti duomenis?:"<<endl;
        rpasirink();//rikiavimo pasirinkimai
        int laikin;
        cin>>laikin;
        if(laikin>5||cin.fail())
        {
            cout<<"Pasirinkote klaidingai, duomenys nebus rikiuojami"<<endl;
            laikin=1;
        }
        rikiuoti(laikin, S);
        if(TEMP>3)padalinti(S, nuskriaustieji, rimtuoliai);
        if(TEMP!=4){
            cout << setw(15) << left << "Vardas" << setw(15) << left << "Pavarde" << setw(10) << left << "Vidurkis" << "Mediana" << endl;
            for (size_t i = 0; i < S.size(); i++)
            {
                cout << S[i]; // isvesime i ekrana studentus
            }
        }
        else spausfail(nuskriaustieji, rimtuoliai);
    }
    S.clear();
    return 0; //kazka grazinu, nes reikia kazka grazinti. Manau su 0 bus maziausia problemu.
}