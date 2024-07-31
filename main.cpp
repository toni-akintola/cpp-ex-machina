#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"
int main() {
    Eigen::MatrixXd A(2, 3);
    A << 1, 2, 4,
         4, 5, 6;

    Eigen::MatrixXd B(3, 2);
    B << 7, 8,
         9, 10,
         11, 12;

    Eigen::MatrixXd C = A * B;

    std::cout  << C << std::endl;

    return 0;
}
