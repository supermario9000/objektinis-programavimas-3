#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "vector.hpp"
#include "mylib.h"
#include "structs.h"

vector<int> s; //pirmam testui
Vector<int> S;

bool test1(vector<int> &s, Vector<int> &S, int count) {
    startTimer();
    for(int i=0;i<10000*count;++i) s.push_back(i); //tikriname kiek laiko uztrunka uzpildyti paprastais int elementais
    cout<<"Baigtas paprasto vektoriaus uzpildymas su " <<to_string(s.size())<< " elementais ";
    stopTimer();

    startTimer();
    for(int i=0;i<10000*count;++i) S.push_back(i);
    cout<<"Baigtas mano sukurto Vektoriaus uzpildymas su "<< to_string(S.size())<< " elementais ";
    stopTimer();
    s.clear(); //valome paprasta vektoriu
    S.clear(); //valome mano sukurta vektoriu
    cout<<endl;
    return true;
}

TEST_CASE("Integer surasymo spartos testai") {
    REQUIRE(test1(s,S,1));
    REQUIRE(test1(s,S,10));
    REQUIRE(test1(s,S,100));
    REQUIRE(test1(s,S,1000));
    REQUIRE(test1(s,S,10000));
}
