#include <iostream>

#include <torch/torch.h>
#include "stock.h"

int main() {
     torch::Tensor tensor = torch::rand({2, 3});
     std::cout << tensor << std::endl;
     parseData();

     return 0;
}