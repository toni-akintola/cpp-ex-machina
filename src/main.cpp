#include <iostream>
#include <curl/curl.h>
#include <Eigen/Dense>
#include <stock.h>

int main() {
    Eigen::MatrixXd A(2, 3);
    A << 1, 2, 4,
         4, 5, 6;

    Eigen::MatrixXd B(3, 2);
    B << 7, 8,
         9, 10,
         11, 12;

    Eigen::MatrixXd C = A * B;
    std::vector<Stock> stocks = getStocks();

    for (auto &stock : stocks)
    {
        std::cout << "Ticker: " << stock.get_ticker() << " Price: " << stock.get_price() << std::endl;
    }

    return 0;
}