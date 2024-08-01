#include <iostream>
#include <curl/curl.h>
#include <Eigen/Dense>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    Eigen::MatrixXd A(2, 3);
    A << 1, 2, 4,
         4, 5, 6;

    Eigen::MatrixXd B(3, 2);
    B << 7, 8,
         9, 10,
         11, 12;

    Eigen::MatrixXd C = A * B;

    std::cout  << C << std::endl;
    // CURL example
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }
    return 0;
}