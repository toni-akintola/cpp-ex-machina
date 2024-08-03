#include <iostream>
#include "GeometricBrownianMotion.h"
#include <curl/curl.h>
#include <Eigen/Dense>


int main() {
    double p0 = 100.0;  
    double mu = 0.05;  
    double sigma = 0.2; 
    double T = 1.0;   
    int n = 10;         

    GeometricBrownianMotion gbm(p0, mu, sigma, T, n);


    Eigen::MatrixXd sim = gbm.MonteCarloSimulate(10);
    
    std::cout << "New value: " << sim << std::endl;

    return 0;
}