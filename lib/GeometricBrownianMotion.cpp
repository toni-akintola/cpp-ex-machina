#include "GeometricBrownianMotion.h"
#include <Eigen/Dense>
#include <random>
#include <cmath>
#include <iostream>

GeometricBrownianMotion::GeometricBrownianMotion(double p0, double mu, double sigma, double T, int n)
    : p0(p0), mu(mu), sigma(sigma), T(T), n(n) {
}

Eigen::MatrixXd GeometricBrownianMotion::MonteCarloSimulate(int numSimulations) {
    Eigen::MatrixXd scenarios(numSimulations, n + 1);

    double dt = T / n;
    
    std::random_device rand;
    std::mt19937 gen(rand());
    std::normal_distribution<> d(0.0, std::sqrt(dt)); 

    for (int i = 0; i < numSimulations; ++i) {
        scenarios(i, 0) = p0;
        for (int step = 1; step <= n; ++step) {
            double Wt = d(gen); 
            double St = scenarios(i, 0) * std::exp((mu - 0.5 * sigma * sigma) * dt + sigma * Wt);
            scenarios(i, step) = St;
        }
    }

    return scenarios;
}

