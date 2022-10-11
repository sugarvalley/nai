#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using mojafunkcja = function<float(int x, int y)>;

void wypisz(const mojafunkcja& fun, int x, int y=0) {
    cout << fun(x, y) << endl;
}

int main(int argc, char **argv) {
    vector<string> argumenty(argv, argc + argv);
    map<string, mojafunkcja> opcje;
    opcje["add"] = [](int x, int y) { return x + y; };
    opcje["mod"] = [](int x, int y) { return x % y; };
    opcje["sin"] = [](int x, int y=0) { return sin(x); };
        try {
            wypisz(opcje[argumenty.at(1)], stoi(argumenty.at(2)), stoi(argumenty.at(3)));
            } catch (out_of_range aor) {
                if(argc == 3){
                    wypisz(opcje[argumenty.at(1)], stoi(argumenty.at(2)));
                } else {
                    cout << "Wybierz opcje, dostepne to: " << endl;
                    for (auto [k, v] : opcje) cout << " " << k;
                    cout << endl;
                }
            }
    return 0;
}