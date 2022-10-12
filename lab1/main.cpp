#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using mojafunkcja = function<double(vector<double>)>;

void wypisz(vector<double> liczby, mojafunkcja fun) {
    cout << fun(liczby) << endl;
}

int main(int argc, char **argv) {
    map<string, mojafunkcja> opcje;
    opcje["add"] = [](vector<double> liczby) { return liczby.front() + liczby.back(); };
    opcje["mod"] = [](vector<double> liczby) { return (int)liczby.front() % (int)liczby.back(); };
    opcje["sin"] = [](vector<double> liczby) { return sin(liczby.front()); };
        try {
            vector<string> argumenty(argv, argc + argv);
            auto selected_f = argumenty.at(1);
            vector<double> numbers = {{stod(argumenty.at(2)), stod(argumenty.back())}};
            wypisz(numbers, opcje.at(selected_f));
            } catch (out_of_range aor) {
                    cout << "Wybierz opcje, dostepne to: " << endl;
                    for (auto [k, v] : opcje) cout << " " << k;
                    cout << endl;
            return 1;
            }
    return 0;
}