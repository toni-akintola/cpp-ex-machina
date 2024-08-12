#include <iostream>

#include <torch/torch.h>
#include "stock.h"

int main() {
     torch::Tensor tensor = torch::rand({2, 3});
     std::cout << tensor << std::endl;
     auto [trainingDataset, validationDataset] = parseData();

     return 0;
}