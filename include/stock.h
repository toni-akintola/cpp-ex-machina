#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <tuple>
#include <torch/torch.h>

class StockDataset : public torch::data::Dataset<StockDataset>
{
private:
    std::vector<std::vector<float>> x_data;
    std::vector<float> y_data;

public:
    // Constructor
    StockDataset(const std::vector<std::vector<float>> &x, const std::vector<float> &y) : x_data(x), y_data(y) {};

    // Override get() function
    torch::data::Example<> get(size_t index) override
    {
        std::vector<float> &x_item = x_data[index];
        float y_item = y_data[index];

        // Convert std::vector<float> to torch::Tensor
        torch::Tensor x_tensor = torch::from_blob(x_item.data(), {static_cast<long>(x_item.size())}, torch::kFloat32).clone();
        torch::Tensor y_tensor = torch::tensor(y_item);

        return {x_tensor, y_tensor};
    }

    // Override size() function
    torch::optional<size_t> size() const override
    {
        return x_data.size();
    }
};

std::tuple<std::vector<std::string>, std::vector<float>, int> getStocks();
std::tuple<StockDataset, StockDataset> parseData();
#endif