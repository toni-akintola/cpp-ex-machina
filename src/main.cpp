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


    return 0;
}