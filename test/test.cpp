#include <iostream>
#include <cmath>
#include <limits>

int main(){
    float inf {INFINITY};
    std::cout << "Infity cmath: " << inf << '\n';
    double inf2 {std::numeric_limits<double>::infinity()};
    std::cout << "Infinity limits: " << inf2 << '\n';
}
