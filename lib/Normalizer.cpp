#include "Normalizer.h"
#include <numeric>
#include <cmath>

Normalizer::Normalizer() : mu(0), sd(0) {}

std::vector<double> Normalizer::fit_transform(const std::vector<double>& x) {
    mu = mean(x);
    sd = standard_deviation(x, mu);
    std::vector<double> normalized;
    for (double value : x) {
        normalized.push_back((value - mu) / sd);
    }
    return normalized;
}

std::vector<double> Normalizer::inverse_transform(const std::vector<double>& x) const {
    std::vector<double> original_x;
    for (double value : x) {
        original_x.push_back((value * sd) + mu);
    }
    return original_x;
}

double Normalizer::mean(const std::vector<double>& x) const {
    return std::accumulate(x.begin(), x.end(), 0.0) / x.size();
}

double Normalizer::standard_deviation(const std::vector<double>& x, double mean) const {
    double variance = 0;
    for (double value : x) {
        variance += (value - mean) * (value - mean);
    }
    variance /= x.size();
    return std::sqrt(variance);
}
