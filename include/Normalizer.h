#ifndef NORMALIZER_H
#define NORMALIZER_H

#include <vector>

class Normalizer {
public:
    Normalizer();
    std::vector<double> fit_transform(const std::vector<double>& x);
    std::vector<double> inverse_transform(const std::vector<double>& x) const;

private:
    double mu;
    double sd;

    double mean(const std::vector<double>& x) const;
    double standard_deviation(const std::vector<double>& x, double mean) const;
};

#endif 
