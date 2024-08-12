#include <iostream>
#include <Normalizer.h>
#include <LSTMModel.h>
#include <torch/torch.h>
#include "stock.h"

int main() {
   
    int64_t inputSize = 10;
    int64_t hiddenLayerSize = 20;
    int64_t numLayers = 2;
    int64_t outputSize = 1;
    double dropoutRate = 0.2;

    LSTMModel model(inputSize, hiddenLayerSize, numLayers, outputSize, dropoutRate);

    torch::Tensor input = torch::randn({1, 5, inputSize});

    torch::Tensor output = model.forward(input);

    std::cout << "Model output: " << output << std::endl;

    return 0;
}
