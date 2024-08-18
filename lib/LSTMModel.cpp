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
    x = linear1->forward(x);

    auto lstm_output = std::get<0>(lstm->forward(x));
    x = dropout->forward(lstm_output);

    x = linear2->forward(x);
    
    return x;
}

std::pair<float, float> run_epoch(
    LSTMModel &model,
    auto &dataloader,
    torch::optim::Optimizer &optimizer,
    torch::nn::Module &criterion,
    torch::optim::LRScheduler &scheduler,
    torch::Device device,
    bool is_training = false)
{
    float epoch_loss = 0.0f;

    if (is_training)
    {
        model.train();
    }
    else
    {
        model.eval();
    }

    for (auto &batch : dataloader)
    {
        auto data = batch.data.to(device);
        auto target = batch.target.to(device);

        if (is_training)
        {
            optimizer.zero_grad();
        }

        int64_t batchsize = data.size(0);

        torch::Tensor output = model.forward(data);
        torch::Tensor loss = criterion(output.contiguous(), target.contiguous());

        if (is_training)
        {
            loss.backward();
            optimizer.step();
        }

        epoch_loss += loss.item<float>() / batchsize;
    }

    float lr = 0;

    return {epoch_loss, lr};
}
