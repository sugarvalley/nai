#include <iostream>
#include <vector>
#include <functional>
#include <random>

using namespace std;
using f = function<double(double, double)>;
random_device rd;
mt19937 mt_generator(rd());

double opti(f function, vector<double> domain, int max_iterations) {
    uniform_real_distribution<double> dist(domain.at(0), domain.at(1));
    double best = function(domain.at(0), domain.at(1));
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        double r1 = dist(mt_generator);
        double r2 = dist(mt_generator);
        double temp = function(r1, r2);
        if (temp < best) {
            best = temp;
        }
    }
    return best;
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

    cout<<"Matyas function best min:    "<< opti(matyas, {-10.0, 10.0},10000)<<endl;
    cout<<"Booth function best min:     "<< opti(booth, {-10.0, 10.0},10000)<<endl;
    cout<<"Levi function N.13 best min: "<< opti(levi, {-10.0, 10.0},10000)<<endl;
    return 0;
}