#include "programaMasyvai.cpp"

int masyvai(int TEMP)
{
    int n, m;
    cout << "Kiek studentu turite?:";
    cin >> n;
    if (n == 0)
    {
        cout << "Tai ka jus cia veikiate?" << endl;
        return 0;
    }
    stud *S = new stud[n];
    cout << "Po kiek namu darbu pazymiu noresite suvesti studentams?:";
    cin >> m;
    if (m == 0)
        cout << "Bus isvedamas vidurkis tik is egzamino (egzamino rezultatas = vidurkis). Mediana neskaiciuojama." << endl;
    int *C = new int[n * m]; // m - nd pazymiu skaicius
    int *sum = new int[n];   // studentu pazymiu suma
    if (TEMP == 1)
        masyvaiRanka(S);
    else if (TEMP == 2)
        puseRandMas(S, n, m);
    else
    {
        if (TEMP != 3)
            cout << "Pasirinkote klaidingai, aktyvuosime visu duomenu sugeneravima" << endl;
        visRandMas(S, n, m);
    }
    double *galutinis = new double[n]; // vidurkiui saugoti
    vidurkis(S, n);
    double *med = new double[n];
    if (m != 0)
        mediana(n, m, S);
    spausdinimas(S, n);
    delete[] S; // atminties atlaisvinimas
    delete[] C;
    delete[] sum;
    delete[] galutinis;
    delete[] med;
    return true;
}
