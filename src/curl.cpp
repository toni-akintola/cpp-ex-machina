#include <iostream>
#include <curl/curl.h>
#include <fmt/core.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
   
    CURL *curl = curl_easy_init();
    std::string readBuffer;
 
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.finazon.io/latest/markets/stocks?page_size=1000");
 
        struct curl_slist *headers = NULL;
        const char *apiKey = std::getenv("FINAZON_API_KEY");
        if (apiKey)
        {
            headers = curl_slist_append(headers, fmt::format("Authorization: apikey {}", apiKey).data());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            CURLcode ret = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            std::cout << readBuffer << std::endl;
        }
        
    }

    return 0;
}