#ifndef LSTMMODEL_H
#define LSTMMODEL_H

#include <torch/torch.h>

class LSTMModel : public torch::nn::Module {  

    public:
        LSTMModel(int64_t inputSize = 1, int64_t hiddenLayerSize = 32, int64_t numLayers = 2, int64_t outputSize = 1, double dropout = 0.2);

        torch::Tensor forward(torch::Tensor x);

private:

    torch::nn::Linear linear1{nullptr};
    torch::nn::ReLU relu;
    torch::nn::LSTM lstm{nullptr};
    torch::nn::Dropout dropout{nullptr};
    torch::nn::Linear linear2{nullptr};
};

#endif 
