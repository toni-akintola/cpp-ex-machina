#include <iostream>
#include <Normalizer.h>
#include <LSTMModel.h>
#include <torch/torch.h>
#include "stock.h"

int main() {

    // Device
    auto cuda_available = torch::cuda::is_available();
    torch::Device device(cuda_available ? torch::kCUDA : torch::kCPU);
    std::cout << (cuda_available ? "CUDA available. Training on CPU." : "Training on CPU.") << std::endl;

    // Hyper parameters
    const int64_t inputSize = 10;
    const int64_t hiddenLayerSize = 20;
    const int64_t numLayers = 2;
    const int64_t batch_size = 20;
    const int64_t outputSize = 1;
    double dropoutRate = 0.2;

    LSTMModel model(inputSize, hiddenLayerSize, numLayers, outputSize, dropoutRate);
    model.to(device);

    // Configure datasets & dataloaders
    auto datasets = parseData();
    StockDataset training_dataset = std::get<0>(datasets);
    StockDataset test_dataset = std::get<1>(datasets);

    auto num_training_samples = training_dataset.size().value();
    auto num_test_samples = test_dataset.size().value();

    auto train_loader = torch::data::make_data_loader<torch::data::samplers::RandomSampler>(
        std::move(training_dataset), batch_size);
    auto test_loader = torch::data::make_data_loader<torch::data::samplers::RandomSampler>(std::move(test_dataset), batch_size);

    torch::Tensor input = torch::randn({1, 5, inputSize});

    torch::Tensor output = model.forward(input);

    std::cout << "Model output: " << output << std::endl;

    return 0;
}
