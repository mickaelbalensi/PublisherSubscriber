#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include "json.hpp" // JSON library

using json = nlohmann::json;

// Function to write the response data to a string buffer
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
    size_t totalSize = size * nmemb;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        // Set the URL for the API request
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.coingecko.com/api/v3/coins/usd-coin");

        // Set the callback function to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Parse the response to a JSON object
            json jsonResponse = json::parse(readBuffer);

            // Pretty-print the JSON object
            std::cout << jsonResponse.dump(4) << std::endl;

            // Save the JSON response to a file
            std::ofstream outputFile("coingecko_response.json");
            outputFile << jsonResponse.dump(4);  // 4 spaces for indentation (pretty-print)
            outputFile.close();

        }

        // Cleanup CURL
        curl_easy_cleanup(curl);
    }

    return 0;
}
