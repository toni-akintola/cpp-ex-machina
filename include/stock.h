#include <string>
#include <tuple>
#ifndef STOCK_H
#define STOCK_H

std::tuple<std::vector<std::string>, std::vector<float>, int> getStocks();
std::tuple<std::vector<std::vector<float>>, std::vector<float>, std::vector<std::vector<float>>, std::vector<float>> parseData();

#endif