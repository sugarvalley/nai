#include <iostream>
#include <vector>
#include <functional>
#include <random>

using namespace std;
using f = function<double(double, double)>;
random_device rd;
mt19937 mt_generator(rd());

auto opti(f function, vector<double> domain, int max_iterations) {
    uniform_real_distribution<double> dist(domain.at(0), domain.at(1));
    double best = function(domain.at(0), domain.at(1));
    vector<double> dom;
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        double r1 = dist(mt_generator);
        double r2 = dist(mt_generator);
        double temp = function(r1, r2);
        if (temp < best) {
            best = temp;
            dom = {r1, r2};
        }
    }
    return dom;
}
void printer(vector<double> arguments) {
    cout << "x: " << arguments.at(0) << endl;
    cout << "y: " << arguments.at(1) << endl;
}

int main() {

    auto matyas = [](double x, double y) {
        return ((0.26*(pow(x, 2) + pow(y, 2))) - (0.48 * x * y));
    };

    auto booth = [](double x, double y) {
        return ((pow((x + 2*y - 7), 2)) + (pow((2*x + y - 5), 2)));
    };

    auto levi = [](double x, double y) {
        return (pow((sin((3*M_PI*x))),2) + (pow((x - 1), 2) *
                (1 + pow((sin((3*M_PI*y))),2))) +
                (pow((y - 1), 2)*(1 + pow((sin((2*M_PI*y))),2))));
    };

    cout << "Matyas best value:" << endl;
    printer(opti(matyas, {-10.0, 10.0},10000));
    cout << "Booth best value:" << endl;
    printer(opti(booth, {-10.0, 10.0},10000));
    cout << "Levi best value:" << endl;
    printer(opti(levi, {-10.0, 10.0},10000));
    return 0;
}