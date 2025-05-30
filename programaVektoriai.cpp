#include "mylib.h"
#include "structs.h"
#include "vector.hpp"

void vektoriaiRanka(Vector<stud> &S)
{
    int i = 0;
    while (true)
    {
        string vardas="", pavarde="";
        S.push_back(stud()); // perejimas i kita  eilute, vietos alokavimas
        cout << "Iveskite studento varda (arba 'n', jei ivedete visus studentu duomenis):" << endl;
        cin >> vardas;
        if (vardas == "n")
            {
                S.pop_back(); // jei ivestas 'n', istriname paskutini studento objekta
                break;
            }
        S[i].setVardas(vardas); // nustatome varda studentui
        cout << "Iveskite studento pavarde:" << endl;
        cin >> pavarde;
        S[i].setPavarde(pavarde); // nustatome pavarde studentui
        cout << "Iveskite studento namu darbu pazymius, po kiekvieno spauskite enter, jei studentas negavo visu pazymiu, ivedus visus iveskite n:" << endl;
        int j=0;
        string input;
        //pazymiu ivedimas
        while (true) {
            cout << "Iveskite studento " << j + 1 << " namu darbu pazymi (arba 'n', jei norite baigti pazymiu ivedima): ";
            cin >> input;

            if (input == "n")
                break;

            try {
                int pazymys = stoi(input);
                if (!arpazymys(pazymys)) {
                    throw std::out_of_range("Pazymys turi buti tarp 0 ir 10!");
                }
                S[i].addPazymys(pazymys); //setteris pushbackina automatiskai
                cout << pazymys << endl;
                j++;
            }
            catch (const std::invalid_argument&) {
                cout << "Netinkama ivestis. Iveskite skaiciu!" << endl;
            }
            catch (const std::out_of_range& e) {
                cout << e.what() << endl;
            }
        }

        // Egzamino rezultato ivedimas
        while (true)
        {
            cout << "Iveskite studento egzamino rezultata: ";
            cin >> input;
            try {
                if (arpazymys(stoi(input)) == false) //input deklaruotas pries pazymiu ivedima
                    throw std::out_of_range("Egzamino rezultatas turi buti tarp 0 ir 10!");
                S[i].setEgzaminas(stoi(input));
                break;
            }
            catch (const std::invalid_argument&) {
                cout << "Netinkama ivestis. Iveskite skaiciu!" << endl;
            }
            catch (const std::out_of_range& e) {
                cout << e.what() << endl;
            }
            input = "";//isvalome input, kad nebutu ivesta neteisinga ivestis ir nesikartotu nuolat
        }
        S[i].skaiciuotiVidurki(); // skaiciuojame vidurki
        S[i].skaiciuotiMediana(); // skaiciuojame mediana
        i++;//loopas kartojasi kol neparasoma 'n' vedant varda
    }
}

void pusRandVek(Vector<stud> &S)
{
    int m;
    cout<<"Iveskite namu darbu pazymiu skaiciu:";
    cin>>m;

    int i = 0;
    while (true)
    {
        string vardas= "", pavarde= "";
        S.push_back(stud());
        cout << "Iveskite kito studento varda (arba 'n', jei ivedete visus studentu duomenis):" << endl;
        cin >> vardas;
        if (vardas == "n")
        {
            S.pop_back(); //istriname paskutini objekta
            break;
        }
        S[i].setVardas(vardas);
        cout << "Iveskite studento pavarde: ";
        cin >> pavarde;

        cout << "Sugeneruoti namu darbu pazymiai: ";
        for (int j = 0; j < m; j++)
        {
            S[i].addPazymys(randominis());
            cout << S[i].pazymiai()[j] << " "; // prieiname prie j elemento pazymiai_ vektoriuje
        }

        cout << endl << "Sugeneruotas egzamino rezultato pazymys: ";
        S[i].setEgzaminas(randominis());
        cout << S[i].egzrez() << endl;
        S[i].skaiciuotiVidurki(); // skaiciuojame vidurki
        S[i].skaiciuotiMediana(); // skaiciuojame mediana
        i++;
    }
}

void visRandVek(Vector<stud> &S)
{
    int n,m;
    cout<<"Iveskite studentu skaiciu:";
    cin>>n;
    cout<<"Iveskite namu darbu pazymiu skaiciu:";
    cin>>m;

    for (int i = 0; i < n; i++)
    {
        S.push_back(stud()); // alokuojama vieta naujam studentui
        S[i].setVardas(Vardas[randominis()]);
        S[i].setPavarde(Pavarde[randominis()]);

        for (int j = 0; j < m; j++)
        {
            S[i].addPazymys(randominis());
        }
        S[i].setEgzaminas(randominis());
        S[i].skaiciuotiVidurki(); // skaiciuojame vidurki
        S[i].skaiciuotiMediana(); // skaiciuojame mediana
    }
}

void txtfailai(const string &path, Vector<string> &fileList) // Failu parodymas pagal operacine sistema
{
    int i = 0; // i - indeksas, kuri gali naudoti abi operacines sistemos.
#ifdef _WIN32
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA((path + "\\*.txt").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "No .txt files found or error opening directory!" << endl;
        return;
    }
    do
    {
        fileList.push_back(findFileData.cFileName);
        i++; // iskart indeksuojam failus
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);

#else
    //  Linux/macOS su dirent.h
    DIR *dir = opendir(path.c_str()); // linuxine versija netestuota
    if (dir == nullptr)
    {
        cout << "Error opening directory!" << endl;
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        string filename = entry->d_name;
        if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt")
        {
            i++;
            fileList.push_back(filename);
        }
    }

    closedir(dir);
#endif
}

void skaityk(Vector<stud> &S)
{
    string path = "./Student_Files"; // kur ieskoti failu. Irasydami . gausime visus esame aplanke
    Vector<string> fileList;
    Vector<string> patikrList;
    try 
    {// tikriname ar egzistuoja bent kokie failai
        txtfailai(path, fileList);
        if (fileList.empty()) {
            throw runtime_error("Nerasta .txt failu!");
        }
    } 
    catch (const exception &e) 
    {
        std::cerr << "Klaida: " << e.what() << endl;
        exit(1); // nustoja veikti programa jei failu nerasta.
    }
    int tem;
    while (true)
    {
        cout << "Galite rinktis is siu failu:" << endl;
        for(size_t i=0; i<fileList.size(); i++)
        {
            cout << i+1 << " - " << fileList[i] << endl;
        }
        cout << "Iveskite failo, kuri norite pasirinkti, numeri: ";
        cin >> tem;
        if (cin.fail()) // jei ivesti blogi duomenys
        { //cia exeptions kaip ir handlinama be try/catch metodo, tad nieko nekeisiu
            cin.clear();
            cin.ignore(1000, '\n'); // ignoruoja enter
            cout << "Neteisinga ivestis, bandykite dar karta!" << endl;
            continue;//ciklas pasikartoja iki kol ivesti duomenys atitinka pasirinkimo logika
        }
        if (tem >= 1 && tem <= (int)fileList.size())
        {
            txtfailai(path, patikrList); //tikriname ar failai nebuvo istrinti ar pakeisti pries pasirenkant
            try {
                if (fileList[tem-1]!= patikrList[tem-1]) {
                    throw runtime_error("Failas buvo pakeistas arba istrintas!");
                }
                cout << "Pasirinkote: " << fileList[tem - 1] << endl;
                break;
            }
            catch (const exception &e) {
                cerr << "Klaida: " << e.what() << endl; 
            }
            cout<<"Failai bus nuskaitomi is naujo!"<<endl;
            fileList.clear(); // istriname failu sarasa, kad nebutu indeksavimo klaidu
            txtfailai(path, fileList); // jei failas pakeistas programa is naujo patikrina kokie failai egzistuoja
        }
        else
            cout << "Blogas pasirinkimas, bandykite is naujo!" << endl;
        patikrList.clear();
    }
    // baigta failo pasirinkimo dalis, zemiau pats duomenu nuskaitymas
    /*===============================================================*/
    ifstream in(path+"/"+fileList[tem - 1]);
    string pavadinimas;
    getline(in, pavadinimas); // Praleidziame pirmaja eilute (turiu itarima, kad cia gali buti data leakas, bet nesu tikras)

    char simbolis;
    string zodis = ""; // tuscias zodzis, kuris sukaups visa varda ir irasys ji i struktura
    int temp = 0;      // integeris, padedantis atskirti kintamuju ivedima.
    int i = -1;
    startTimer(); // pradedame skaiciuoti laika
    while (in.get(simbolis))
    {
        if (simbolis == ' ' || simbolis == '\n' || simbolis == '\t')
        {
            if (zodis.empty())
                continue; // ignoruojam kelis tarpus ar tabs is eiles
            else if (temp == 0)
            {
                S.push_back(stud()); // perejimas i kita  eilute, vietos alokavimas
                i++;

                S[i].setVardas(zodis);
                zodis = "";
                temp++;
            }
            else if (temp == 1)
            {
                S[i].setPavarde(zodis);
                zodis = "";
                temp++;
            }
            else if (temp >= 2 && simbolis != '\n')
            {
                if(arskaicius(zodis)==true)// skaiciaus ivedimas is string i int
                {
                    if (arpazymys(stoi(zodis))==true) // tikriname ar ivestas skaicius yra pazymys
                    {
                        S[i].addPazymys(stoi(zodis));
                    }
                    else
                    {
                        cout << "Klaida faile: Pazymys turi buti tarp 0 ir 10!" << endl;
                    }
                }
                zodis = "";
            }
            else if (simbolis == '\n') // reikia atskirti kad simbolis yra \n
            {
                if (arskaicius(zodis)==true) // skaiciaus ivedimas is string i int
                {
                    if (arpazymys(stoi(zodis))==true) // tikriname ar ivestas skaicius yra pazymys
                    {
                        S[i].setEgzaminas(stoi(zodis));
                        S[i].skaiciuotiVidurki(); // skaiciuojame vidurki
                        S[i].skaiciuotiMediana(); // skaiciuojame mediana
                    }
                    else
                    {
                        cout << "Klaida: Pazymys turi buti tarp 0 ir 10!" << endl;
                    }
                }
                zodis = "";
                temp = 0;//parodome, kad kita elementa irasytu i s.vardas  
            }
        }
        else
            zodis += simbolis;
    }
    // nuskaitome paskutini egzamino rezultata (kai dokumentas nebepasibaigia newline)
    if (!zodis.empty() && temp >= 2)
    {
        if (arskaicius(zodis) || zodis == "10") // skaiciaus ivedimas is string i int
        {
            if(arpazymys(stoi(zodis))==true) // tikriname ar ivestas skaicius yra pazymys
            {
                S[i].setEgzaminas(stoi(zodis));
                S[i].skaiciuotiVidurki(); // skaiciuojame vidurki
                S[i].skaiciuotiMediana(); // skaiciuojame mediana
            }
            else
            {
                cout << "Klaida faile: Pazymys turi buti tarp 0 ir 10!" << endl;
            }
        }
    }
    // duomenu nuskaitymo is failo pabaiga || NUSKAITYMAS VEIKIA, WOOHOO!!!
    in.close();
    fileList.clear();
}

void rikiuoti(int laikin, Vector<stud> &S)
{
    if(laikin==1)return;
    if (laikin == 2) { //pamazinau algoritmo sudetinguma, is O n^2 i O logn
        sort(S.begin(), S.end(), [](const auto& a, const auto& b) {
            return a.vardas() < b.vardas();
        });
    }
    else if (laikin == 3) {
        sort(S.begin(), S.end(), [](const auto& a, const auto& b) {
            return a.pavarde() < b.pavarde();
        });
    }
    else if (laikin == 4) {
        sort(S.begin(), S.end(), [](const auto& a, const auto& b) {
            return a.galutinis() > b.galutinis();
        });
    }
    else if (laikin == 5) {
        sort(S.begin(), S.end(), [](const auto& a, const auto& b) {
            return a.med() > b.med();
        });
    }    
}

void padalinti(Vector<stud> &S, Vector<stud> &nuskriaustieji, Vector<stud> &rimtuoliai)
{
    //patobulinta versija, veikianti greiciausiai is visu
    for (const auto &student : S)
    {
        if (student.galutinis() >= 5)
            rimtuoliai.push_back(move(student)); //taip iskart perkeliamas studentas i kita vektoriu, o ne kopijuojamas - sutaupom laiko ir resursu
        else
            nuskriaustieji.push_back(move(student));
    }
    S.clear(); // isvalome originalu vektoriu, kad jis neuzimtu vietos
}

void spausfail(Vector<stud> &nuskriaustieji, Vector<stud> &rimtuoliai)
{
    ofstream out("nuskriaustieji.txt");
    ofstream out2("rimtuoliai.txt");

    out << setw(15) << left << "Vardas" << setw(15) << left << "Pavarde" << setw(10) << left << "Vidurkis" << "Mediana" << endl;
    out << "----------------------------------------------------------------"<<endl;
    out2 << setw(15) << left << "Vardas" << setw(15) << left << "Pavarde" << setw(10) << left << "Vidurkis" << "Mediana" << endl;
    out2 << "----------------------------------------------------------------"<<endl;

    for (size_t i = 0; i < nuskriaustieji.size(); i++)
    {
        out << nuskriaustieji[i]; // isvesime i faila nuskriaustuju studentus
        // tai daro operatorius <<, kuris yra apibrėžtas klasėje stud
    }
    for (size_t i = 0; i < rimtuoliai.size(); i++)
    {
        out2 << rimtuoliai[i]; // isvesime i faila rimtuoliu studentus
    }
    out.close();
    out2.close();
    stopTimer(); // sustabdome laiko skaiciavima
}

void generuotif()
{
    cout<<"Irasykite, kaip norite pavadinti sugeneruota faila (be .txt): ";
    string failas;
    cin>>failas;
    create_directories("Student_Files"); // sukuria direktorija, jei jos nera
    ofstream out("Student_Files/" + failas + ".txt");
    cout<<"Kiek studentu norite sugeneruoti? ";
    int n;
    while (true)
    {
        cin >> n;
        if (cin.fail() || n <= 0) // tikriname ar ivestas skaicius yra teigiamas
        {
            cin.clear();
            cin.ignore(1000, '\n'); // ignoruoja enter
            cout << "Neteisinga ivestis, bandykite dar karta!" << endl;
            continue; // ciklas pasikartoja iki kol ivesti duomenys atitinka pasirinkimo logika
        }
        else break; // jei ivestas teigiamas skaicius, nutraukiame cikla
    }
    cout<<"Kiek namu darbu pazymiu norite sugeneruoti? ";
    int m;
    while (true)
    {
        cin >> m;
        if (cin.fail() || m <= 0) // tikriname ar ivestas skaicius yra teigiamas
        {
            cin.clear();
            cin.ignore(1000, '\n'); // ignoruoja enter
            cout << "Neteisinga ivestis, bandykite dar karta!" << endl;
            continue; // ciklas pasikartoja iki kol ivesti duomenys atitinka pasirinkimo logika
        }
        else break; // jei ivestas teigiamas skaicius, nutraukiame cikla
    }
    out << left << setw(25) << "Vardas"<< left << setw(25) << "Pavarde";
    for(int i=0; i<m; i++)
    {
        out << right << setw(15) << ("ND" + to_string(i + 1)); // naudoju to_string, kad nebutu klaidu su setw
    }
    out << right << setw(15) << "Egz." << endl;
    for (int i = 0; i < n; i++) 
    {
        out << left << setw(25) << ("Vardas" + to_string(i + 1))<< left << setw(25) << ("Pavarde" + to_string(i + 1));
        for (int j = 0; j < m; j++) 
        {
            out << right << setw(15) << randominis();
        }
        out << right << setw(15) << randominis() << endl;
    }
    out.close();
    cout << "Sugeneruotas failas: " << failas << ".txt" << endl;
}

void testClass()
{
    stud a, b, c;
    //sukuriame pradini studenta
    a.setVardas("Jonas");
    a.setPavarde("Jonaitis");
    a.addPazymys(8);
    a.addPazymys(9);
    a.addPazymys(10);
    a.addPazymys(7);
    a.addPazymys(6);
    a.setEgzaminas(9);
    a.skaiciuotiVidurki();
    a.skaiciuotiMediana();
    cout<<"sukurtas studentas: " << endl;
    cout<< a << endl;
    b = a; // copy assignment operatorius
    cout<<"kopijuotas studentas: " << endl;
    cout<< b << endl;
    c = move(a); // move assignment operatorius
    cout<<"perkeliamas studentas: " << endl;
    cout<< c << endl;
    cout<<"originalus studentas po perkelimo: " << endl;
    cout<< a << endl; // a turetu buti tuscias, nes buvo perkeltas i c

    //nuskaitysime a is failo
    //norint, kad sita funkcija veiktu, reikia sukurti 1 iraso faila su generavimo funkcija (t.y. pasirinkti 5 ir generuoti test.txt faila)
    ifstream in("Student_Files/test.txt");
    string pavadinimas;
    getline(in, pavadinimas); // praleidziame pirmaja eilute
    in>>a; // naudosime operatoriu >>, kuris yra friend funkcija
    in.close();
    cout<<"Nuskaitytas studentas is failo: " << endl;
    cout<< a << endl; // turetu buti toks pats kaip b, nes nuskaitytas is failo
    cout<<"Testavimas baigtas!" << endl;

    //a.~stud(); destruktoriai veikia, bet jie ir taip automatiskai iskvieciami, kai objektas baigia gyvavimo cikla
    //tuomet atminti bandoma atlaisvinti 2 kartus, programa baigia darba su klaida
    //del to ju netestuosime
}