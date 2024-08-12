#include "stock.h"
#include <iostream>
#include <curl/curl.h>
#include <fmt/core.h>
#include <tuple>
#include <nlohmann/json.hpp>
#include <cmath>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t totalSize = size * nmemb;
    output->append((char *)contents, totalSize);
    return totalSize;
}

std::tuple<std::vector<std::string>, std::vector<float>, int> getStocks()
{

    CURL *curl = curl_easy_init();
    std::vector<std::string> dates;
    std::vector<float> closePrices;

    if (curl)
    {
        // Set ticker and define http request endpoint
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        const char *apiKey = std::getenv("ALPHA_VANTAGE_API_KEY");
        const char *ticker = "ABNB";

        curl_easy_setopt(curl, CURLOPT_URL, fmt::format("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol={}&outputsize=full&apikey={}", ticker, apiKey).data());

        struct curl_slist *headers = NULL;
        if (apiKey)
        {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            CURLcode ret = curl_easy_perform(curl);

            if (ret == 0)
            {
                // Parse the json response -> {dates, closePrices, datapoints}
                nlohmann::json data = nlohmann::json::parse(readBuffer);
                nlohmann::json timeseriesData = data["Time Series (Daily)"];

                for (auto it = timeseriesData.begin(); it != timeseriesData.end(); ++it)
                {
                    dates.push_back(it.key());
                    std::string conversionString = it.value()["4. close"];
                    float closePrice = atof(conversionString.data());
                    closePrices.push_back(closePrice);
                }
            }
        }
        curl_easy_cleanup(curl);
    }
    int datapoints = dates.size();

    return std::make_tuple(dates, closePrices, datapoints);
}

std::tuple<StockDataset, StockDataset> parseData()
{

    std::tuple<std::vector<std::string>, std::vector<float>, int> data = getStocks();
    std::vector<float> prices = std::get<1>(data);
    std::vector<std::vector<float>> x{};
    int window_size = 20;
    std::vector<float> y{};
    size_t right = window_size - 1;
    size_t fast = window_size;

    for (size_t right = window_size; right < prices.size(); right++)
    {
        std::vector<float> xVector{};

        for (size_t left = right - window_size; left < right; left++)
        {
            xVector.push_back(prices[left]);
        }
        x.push_back(xVector);
        y.push_back(prices[right]);
    }
    // Compute index
    int split_index = std::floor(y.size() * 0.80);
    std::cout << split_index << std::endl;

    std::vector<std::vector<float>> xTrainingData = std::vector<std::vector<float>>(x.begin(), x.begin() + split_index);
    std::vector<float> yTrainingData = std::vector<float>(y.begin(), y.begin() + split_index);
    std::vector<std::vector<float>> xValidationData = std::vector<std::vector<float>>(x.begin() + split_index, x.end());
    std::vector<float> yValidationData = std::vector<float>(y.begin() + split_index, y.end());

    std::cout << "X Training length: " << xTrainingData.size() << std::endl
              << "Y Training length: " << yTrainingData.size() << std::endl
              << "X Validation length: " << xValidationData.size() << std::endl
              << "Y Validation length: " << yValidationData.size() << std::endl;

    StockDataset trainingDataset(xTrainingData, yTrainingData);
    StockDataset validationDataset(xValidationData, yValidationData);

    return std::make_tuple(trainingDataset, validationDataset);
}
