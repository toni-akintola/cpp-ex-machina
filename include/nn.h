#ifndef NN_H
#define NN_H
#include <torch/torch.h>

class LSTMModel : public torch::nn::Module
{
public:
    LSTMModel(int64_t input_size, int64_t hidden_size, int64_t output_size)
    {
        // Define layers
        fc1 = register_module("fc1", torch::nn::Linear(input_size, hidden_size));
        fc2 = register_module("fc2", torch::nn::Linear(hidden_size, hidden_size));
        fc3 = register_module("fc3", torch::nn::Linear(hidden_size, output_size));
    };

    torch::Tensor forward(torch::Tensor x)
    {
        // Define forward pass
        x = torch::relu(fc1->forward(x));
        x = torch::relu(fc2->forward(x));
        x = fc3->forward(x);

        return x;
    }
    ~LSTMModel();

private:
    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
};

LSTMModel::LSTMModel(/* args */)
{
}

LSTMModel::~LSTMModel()
{
}

#endif