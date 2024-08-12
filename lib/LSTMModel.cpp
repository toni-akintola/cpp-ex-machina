#include "LSTMModel.h"

LSTMModel::LSTMModel(int64_t inputSize, int64_t hiddenLayerSize, int64_t numLayers, int64_t outputSize, double dropout)
    :
      linear1(register_module("linear1", torch::nn::Linear(inputSize, hiddenLayerSize))),
      lstm(register_module("lstm", torch::nn::LSTM(torch::nn::LSTMOptions(hiddenLayerSize, hiddenLayerSize).num_layers(numLayers).batch_first(true)))),
      dropout(register_module("dropout", torch::nn::Dropout(dropout))),
      linear2(register_module("linear2", torch::nn::Linear(hiddenLayerSize, outputSize)))
{
    std::cout << "initializing weights"  << std::endl;
    for (auto& param : lstm->named_parameters()) {
        if (param.key().find("bias") != std::string::npos) {
            torch::nn::init::constant_(param.value(), 0.0);
        } else if (param.key().find("weight_ih") != std::string::npos) {
            torch::nn::init::kaiming_normal_(param.value());
        } else if (param.key().find("weight_hh") != std::string::npos) {
            torch::nn::init::orthogonal_(param.value());
        }
    }
    std::cout << "weights initialized"  << std::endl;
}

torch::Tensor LSTMModel::forward(torch::Tensor x) {
    return x;
}

