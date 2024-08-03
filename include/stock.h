#include <string>
#ifndef STOCK_H
#define STOCK_H

class Stock
{
private:
    std::string ticker;
    double price;

public:
    Stock(double p, std::string ticker);
    double get_price();
    std::string get_ticker();
};

std::vector<Stock> getStocks();

#endif