#include "stock.h"
#include <iostream>
#include <curl/curl.h>
#include <fmt/core.h>
#include <nlohmann/json.hpp>

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

void parseData()
{

    std::tuple<std::vector<std::string>, std::vector<float>, int> data = getStocks();
    std::vector<float> prices = std::get<1>(data);
    std::vector<std::vector<float>> x{};
    std::vector<float> y{};
    size_t right = 19;
    size_t fast = 20;

    for (size_t right = 20; right < prices.size(); right++)
    {
        std::vector<float> x_vector{};

        for (size_t left = right - 20; left < right; left++)
        {
            x_vector.push_back(prices[left]);
        }
        x.push_back(x_vector);
        y.push_back(prices[right]);
    }
    std::cout << "X length: " << x.size() << std::endl
              << "Y length: " << y.size() << std::endl;
}