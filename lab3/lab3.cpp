//
// Created by Cukier on 10/26/2022.
//

#include "lab3.h"


#include <iostream>
#include <vector>
#include <functional>
#include <random>

using namespace std;
using f = function<double(double, double)>;
random_device rd;
mt19937 mt_generator(rd());

auto climb(f function, vector<double> domain, int max_iterations) {
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
    cout << best << endl;
    return dom;
}

auto brute(f function, vector<double> domain, int max_iterations) {
    uniform_real_distribution<double> dist(domain.at(0), domain.at(1));
    auto current_p = dist(mt_generator);
    auto current_p2 = dist(mt_generator);
    auto best_point = function(current_p,current_p2);
    vector<double> dom;

    for(int i=0;i<max_iterations;i++) {
        if (function(current_p,current_p2) < best_point) {
            best_point = function(current_p,current_p2);
            dom = {current_p, current_p2};
        }
        current_p = dist(mt_generator);
        current_p2 = dist(mt_generator);
    }
    cout << best_point << endl;
    return dom;
}

void printer(vector<double> arguments) {
    cout << "x: " << arguments.at(0) << endl;
    cout << "y: " << arguments.at(1) << endl;
}


auto anneal(f function,vector<double> domain, int max_iterations) {
    uniform_real_distribution<double> uk(0, 1);
    uniform_real_distribution<double> dom(domain.at(0),domain.at(1));
    double u = uk(mt_generator);
    double s1 = function(domain.at(0), domain.at(1));
    double s2 = function(domain.at(0),domain.at(1));
    vector<double> myvec;
    vector<double> resultpair;
    myvec.push_back(s1);
    double t1 = dom(mt_generator);
    double t2 = dom(mt_generator);
    for (int i = 0; i < max_iterations; ++i) {
        normal_distribution<double> dom1(t1, 0.1);
        normal_distribution<double> dom2(t2, 0.1);
        t1 = dom1(mt_generator);
        t2 = dom2(mt_generator);
        if (function(t1, t2) < function(s1, s2)) {
            s1 =  function(t1, t2); //sk = tk
            resultpair = {t1, t2};
            myvec.push_back(s1);
        } else {
            if (u < exp(-(fabs(function(t1, t2) - function(s1, s2)) / ((1 / log(i)))))) {
                s1 =  function(t1, t2);
                resultpair = {t1, t2};
                myvec.push_back(s1);
            }
        }
    }
    for(int j=0;myvec.size()>j;j++) {
        if (myvec[j] < s1) {
            s1 = myvec[j];
        }
    }
    cout << s1 << endl;
    return resultpair;
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

    auto cross = [](double x, double y) {
        return -0.0001*(pow((fabs(sin(x)*sin(y)*exp(fabs(100-(sqrt(pow(x,2)+pow(y,2)))/M_PI))+1)),0.1));
    };

    cout << "ANNEAL: " << endl;
    cout << "Matyas best value:" << endl;
    printer(anneal(matyas, {-10.0, 10.0}, 100000));
    cout << "Booth best value:" << endl;
    printer(anneal(booth, {-10.0, 10.0}, 100000));
    cout << "Levi best value:" << endl;
    printer(anneal(levi, {-10.0, 10.0}, 100000));
    cout << "Cross best value:" << endl;
    printer(anneal(cross, {-10.0, 10.0}, 100000));

    cout << " " << endl;
    cout << "CLIMB: " << endl;
    cout << "Matyas best value:" << endl;
    printer(climb(matyas, {-10.0, 10.0}, 100000));
    cout << "Booth best value:" << endl;
    printer(climb(booth, {-10.0, 10.0}, 100000));
    cout << "Levi best value:" << endl;
    printer(climb(levi, {-10.0, 10.0}, 100000));
    cout << "Cross best value:" << endl;
    printer(climb(cross, {-10.0, 10.0}, 100000));
    cout << " " << endl;

    cout << "BRUTE: " << endl;
    cout << "Matyas best value:" << endl;
    printer(brute(matyas, {-10.0, 10.0}, 100000));
    cout << "Booth best value:" << endl;
    printer(brute(booth, {-10.0, 10.0}, 100000));
    cout << "Levi best value:" << endl;
    printer(brute(levi, {-10.0, 10.0}, 100000));
    cout << "Cross best value:" << endl;
    printer(brute(cross, {-10.0, 10.0}, 100000));
    return 0;
}