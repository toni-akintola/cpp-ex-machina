#include <iostream>
#include "GeometricBrownianMotion.h"

int main() {
    double p0 = 100.0;  
    double mu = 0.05;  
    double sigma = 0.2; 
    double T = 1.0;   
    int n = 10;         

    GeometricBrownianMotion gbm(p0, mu, sigma, T, n);

    Eigen::MatrixXd sim = gbm.MonteCarloSimulate(100);
    
    std::cout << "New value: " << sim << std::endl;

    return 0;
}