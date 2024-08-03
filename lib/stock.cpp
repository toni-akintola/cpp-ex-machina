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

Stock::Stock(double p, std::string underlyingTicker)
{
    price = p;
    ticker = underlyingTicker;
}

double Stock::get_price()
{
    return price;
}

std::string Stock::get_ticker()
{
    return ticker;
}

std::vector<Stock> getStocks()
{

    CURL *curl = curl_easy_init();
    std::vector<Stock> stocks = {};
    std::vector<std::string> tickers = {"O:SPY251219C00650000", "O:NVDA240809C00075000", "O:CRWD240809C00215000", "O:AMC240809C00003500"};

    if (curl)
    {
        for (auto &ticker : tickers)
        {
            std::string readBuffer;
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
            curl_easy_setopt(curl, CURLOPT_URL, fmt::format("https://api.polygon.io/v3/reference/options/contracts/{}", ticker).data());

            struct curl_slist *headers = NULL;
            const char *apiKey = std::getenv("POLYGON_API_KEY");
            if (apiKey)
            {
                headers = curl_slist_append(headers, fmt::format("Authorization: Bearer {}", apiKey).data());
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

                CURLcode ret = curl_easy_perform(curl);

                if (ret == 0)
                {
                    nlohmann::json data = nlohmann::json::parse(readBuffer);
                    double p = data["results"]["strike_price"];
                    std::string ticker = data["results"]["underlying_ticker"];
                    stocks.push_back(Stock(p, ticker));
                }
            }
        }
        curl_easy_cleanup(curl);
    }

    return stocks;
}