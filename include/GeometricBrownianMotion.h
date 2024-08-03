#ifndef GEOMETRICBROWNIANMOTION_H
#define GEOMETRICBROWNIANMOTION_H

#include <Eigen/Dense>

class GeometricBrownianMotion {
private:
    
    double p0;
    // initial price
      
    double mu;  
     // drift coefficient  

    double sigma;
     // volatility  

    double T;    
    // time (years) 

    int n;  
    // number of steps       

public:
    GeometricBrownianMotion(double p0, double mu, double sigma, double T, int n);

    Eigen::MatrixXd MonteCarloSimulate(int numSimulations);
};

#endif 
