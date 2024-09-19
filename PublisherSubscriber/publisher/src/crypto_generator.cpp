
// g++ -I/usr/include/python3.10  -I publisher/include/  -I utils/include/ 
// utils/src/crypto.cpp utils/src/client.cpp publisher/src/publisher.cpp 
// publisher/src/crypto_generator.cpp -lpython3.10 -g -o pub.out

#include "crypto_generator.hpp"
#include <thread>       //  this_thread::sleep_for
#include <filesystem>
#include <fstream>  // ifstream 
#include "crypto.hpp"
#include "json.hpp" // JSON library
using json = nlohmann::json;

/* 
const std::string PYTHON_MODULE_PATH = "/home/mickael/github/PublisherSubscriber/publisher/src";
const std::string PYTHON_MODULE_NAME = "fetch_api_script";
*/

namespace fs = std::filesystem;

void fillFileNames(std::vector<std::string>& fileNames, const std::string& folderPath)
{
    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {  
                fileNames.push_back(entry.path().filename().string());  
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


CryptoGenerator::CryptoGenerator()//: m_pythonRunner(PYTHON_MODULE_PATH, PYTHON_MODULE_NAME)
{
    std::string classicFolderPath = "/home/mickael/github/PublisherSubscriber/data/classic/";  
    std::string PremiumFolderPath = "/home/mickael/github/PublisherSubscriber/data/premium/"; 

    fillFileNames(fileClassicNames, classicFolderPath);
    fillFileNames(filePremiumNames, PremiumFolderPath);
}

void CryptoGenerator::run()
{
    for (int i = 0; i < filePremiumNames.size(); i++) {
        std::this_thread::sleep_for(1s);
        json jsonCrypto;
        std::cout << filePremiumNames[i].c_str() << endl;
        std::string classicFolderPath = "/home/mickael/github/PublisherSubscriber/data/premium/";  

        classicFolderPath.append(filePremiumNames[i]);

        std::ifstream file(classicFolderPath.c_str());
        file >> jsonCrypto;
        file.close();
        m_pub.Publish(make_shared<PremiumCrypto>(jsonCrypto));
    }
}

int main()
{
    CryptoGenerator cryptoGenerator;
    cryptoGenerator.run();
    return 0;
}