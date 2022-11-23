//
// Created by Cukier on 11/1/2022.
//

#include "lab4.h"

#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <map>
#include <chrono>
#include <math.h>


using namespace std;
random_device rd;
mt19937 mt_generator(rd());
using f = function<double(pair<double, double>)>;
using chromosome_t = vector<int>;
using population_t = vector<chromosome_t>;

population_t populate(int popSize, int chromSize){
    srand(time(nullptr));
    population_t population;
    for(int i=0;i<popSize;i++){
        chromosome_t chromosome;
        for(int j=0;j<chromSize;j++){
            chromosome.push_back(rand()%2);
        }
        population.push_back(chromosome);
    }
    return population;
}

pair<double, double> geno_feno(chromosome_t chromosome){
    pair<double, double> result={0,0};
    bool minusX = false;
    if(chromosome.at(0)==1)minusX=true;
    bool minusY = false;
    if(chromosome.at(1)==1)minusY=true;
    int splitter = chromosome.size() / 2;
    for(int i=splitter; i > 1; i--){
        result.first += (chromosome.at(i) * pow(2,i));
    }
    for (int i = chromosome.size()-1; i > splitter; i--) {
        result.second += (chromosome.at(i) * pow(i,2));
    }
    if(minusX){ result.first*=-1;}
    if(minusY){ result.second*=-1;}
    result.first = result.first/100000000000000;
    result.second = result.second/10000;

//    cout << "x: "<< result.first << endl;
//    cout << "y: "<< result.second << endl;
    return result;
}


auto genetic_algorithm = [](
        auto initial_population, auto fitness, auto term_condition,
        auto selection, double p_crossover,
        auto crossover, double p_mutation,  auto mutation, f function,
        vector<double> domain, double goal) {
    using namespace std;
    uniform_real_distribution<double> uniform(0.0,1.0);
    auto population = initial_population;
    vector<double> population_fit = fitness(population, function, domain, goal);
    while (!term_condition(population,population_fit)) {
        auto parents_indexes = selection(population_fit);
        decltype(population) new_population;
        for (int i = 0 ; i < parents_indexes.size(); i+=2) {
            decltype(initial_population) offspring = {population[i],population[i+1]};
            if (uniform(mt_generator) < p_crossover) {
                offspring = crossover(offspring);
            }
            for (auto chromosome : offspring) new_population.push_back(chromosome);
        }
        for (auto & chromosome : new_population) {
            chromosome = mutation(chromosome,p_mutation);
        }
        population = new_population;
        population_fit = fitness(population, function, domain, goal);
    }
    return population;
};

vector<double> fitness_function(population_t pop, f function, vector<double> domain, double goal){
    vector<double> result;
    pair <double, double> currPair;
    for (int i = 0; i < pop.size(); i++){
        currPair = geno_feno(pop.at(i));
        if (currPair.first > domain.at(0) && currPair.first < domain.at(1) && currPair.second > domain.at(0) && currPair.second < domain.at(1)){
            result.push_back(666666 - function(currPair));
        }
        else {
            result.push_back(10 + function(currPair));
        }
    }
    int goodBoys = 0;
    for (double p: result) {
        if(p>20){
            goodBoys++;
            cout << p << endl;
        }
    }
    cout << "Good count:" << goodBoys;
    return result;
}


using chromosome_t = vector<int>;
using population_t = vector<chromosome_t>;

vector<int> selection(std::vector<double> fitnesses) {
    uniform_real_distribution<> randomNumb(0.0,1.0);
    double R = randomNumb(mt_generator);
    double S = 0;
    double P = 0;
    double lastP = 0;
    for (double elem : fitnesses){
        S += elem;
    }
    double p = 0;
    std::vector<int> resVector;
    for (int i = 0; i < fitnesses.size(); i++) {
        p = fitnesses.at(i) / S;
        P = lastP + p;
        if(lastP <= R && lastP <= P){
            resVector.push_back(i);
        }
        lastP = P;
    }
    return resVector;
}
vector<chromosome_t > crossover(std::vector<chromosome_t > parents) {
    uniform_real_distribution<double> randomPoint(0,parents.at(0).size());
    int swapPoint = randomPoint(mt_generator);
    for (int i = swapPoint; i < parents.at(0).size(); i++) {
        int temp = parents.at(0).at(i);
        parents.at(0).at(i) = parents.at(1).at(i);
        parents.at(1).at(i) = temp;
    }
    return parents;
}
chromosome_t mutation(chromosome_t parent, double p_mutation) {
    uniform_real_distribution<> randomNumb(0.0,1.0);
        for (int i = 0; i < parent.size(); i++) {
            if ( randomNumb(mt_generator) > p_mutation) {
                if (parent.at(i) == 0){
                    parent.at(i) = 1;
                } else{
                    parent.at(i) = 0;
                }
            }

        }
    return parent;
}
int main() {


    auto cross = [](pair<double, double> xy) {
        return -0.0001*(pow((fabs(sin(xy.first)*sin(xy.second)*exp(fabs(100-(sqrt(pow(xy.first,2)+pow(xy.second,2)))/M_PI))+1)),0.1));
    };

    population_t population = populate(10000, 100+(22202%10)*2);

    population = genetic_algorithm(population,
                                   fitness_function,
                                   [](auto a, auto b) {
                                       for (auto elem: b) {
                                           if (elem >= 666665.999) {
                                               cout << endl << 666666 - elem;
                                               return true;
                                           }
                                       };
                                       return false;
                                   },
                                   selection, 1.0,
                                   crossover,
                                   0.05, mutation, cross, {-10, 10}, -2.06261);
//    for (chromosome_t chromosome: result) {
//        cout << "[";
//        for (int p: chromosome) {
//            cout << p;
//        }
////        cout << "] ";
//    }
    cout << endl;
    return 0;


}