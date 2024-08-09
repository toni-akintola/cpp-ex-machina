#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <tuple>
#include <torch/torch.h>

std::tuple<std::vector<std::string>, std::vector<float>, int> getStocks();
std::tuple<std::vector<std::vector<float>>, std::vector<float>, std::vector<std::vector<float>>, std::vector<float>> parseData();

class StockDataset : public torch::data::Dataset<StockDataset>
{
private:
    std::vector<std::vector<float>> x_data;
    std::vector<float> y_data;

public:
    StockDataset(const std::vector<std::vector<float>> &x, const std::vector<float> &y);
    torch::data::Example<> get(size_t index) override;
    torch::optional<size_t> size() const override;
};

#endif