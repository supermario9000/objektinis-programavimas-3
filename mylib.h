#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm> //sort funkcijai
#include <random>
#include <fstream>
#include <chrono>
#include <deque> //v1.0
#include <list>
#include <iterator> //naudosiu std::advance list iteraciju skaiciavime
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::right;
using std::setprecision;
using std::setw;
using std::stoi;
using std::to_string;
using std::exception;
using std::runtime_error;
using std::cerr;
using std::sort;
using std::swap;
using std::string;
using std::vector;
using std::deque;
using std::list;
using std::ifstream;
using std::ofstream;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::filesystem::create_directories; //kad galetu sukurti student_files aplanka

// bendrai naudojamos funkcijos
// saugau po 11, kad uztikrinti jog nenuskaito pavardes vietoj vardo netyciom
string Vardas[11] = {"Tomas", "Rokas", "Teofilija", "Remigijus", "Sigmute", "Tautvile", "Ona", "Jonas", "Stasys", "Marijus", "Arvydas"};
string Pavarde[11] = {"Povilaitis", "Mikutavicius", "Surajev", "Meschino", "Paulauskas", "Stonkus", "Katleris", "Nauseda", "Teodosija", "Kuprys", "Sabonis"};
std::mt19937 gen(std::random_device{}()); // atsitiktiniu skaiciu generatorius, sugeneruotas viena karta kad kaskart nereiktu sukurti atskiro mt19937

int randominis()
{
    static std::uniform_int_distribution<int> distrib(0, 10); // paskirsto sugeneruotus skaicius vienodu desningumu
    return distrib(gen);
}

bool arskaicius(string a) // tikrina ar ivestas string yra skaicius
{
    try{
        stoi(a); // bandome konvertuoti string i int
        return true;
    }
    catch (const std::invalid_argument&) {
        return false; // jei konvertavimas nepavyko, graziname false
    }
}

bool arpazymys(int a)
{
    if (a >= 0 && a <= 10)
        return true;
    else
        return false;
}

void pasirinkimai()
{
    cout << "Pasirinkite kokiu budu norite, kad programa nuskaitytu duomenis" << endl;
    cout << "1 - Visus duomenis suvesti ranka" << endl;
    cout << "2 - Ranka suvesti vardus ir pavardes, sugeneruoti namu darbu ir egzamino rezultatus" << endl;
    cout << "3 - Sugeneruoti visus duomenis atsitiktine tvarka" << endl;
}

void rpasirink()
{
    cout<<"1 - nerikiuoti"<<endl;
    cout<<"2 - pagal varda"<<endl;
    cout<<"3 - pagal pavarde"<<endl;
    cout<<"4 - pagal Vid galutini rezultata"<<endl;
    cout<<"5 - pagal Med galutini rezultata"<<endl;
}

high_resolution_clock::time_point startTime;//globalus kintamasis laiko matavimui

void startTimer() {
    startTime = high_resolution_clock::now();
}

void stopTimer() {
    auto stopTime = high_resolution_clock::now();
    duration<double> duration = (stopTime - startTime);
    cout << "Laikas: " << fixed << setprecision(5) << duration.count() << " sekundziu" << endl;
}

#endif // MYLIB_H_INCLUDED
