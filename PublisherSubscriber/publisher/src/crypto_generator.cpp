
//g++ -I/usr/include/python3.10 publisher/src/crypto_generator.cpp -lpython3.10
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


    /* json jsonFile;
    std::string classicFolderPath = "/home/mickael/github/PublisherSubscriber/data/classic/";  

    std::cout << fileClassicNames[0].c_str() << endl;
    classicFolderPath.append(fileClassicNames[0]);
    std::cout << classicFolderPath.c_str() << endl;

    std::ifstream file(classicFolderPath.c_str());
    file >> jsonFile;
    std::cout << jsonFile.dump(4) << std::endl;
    std::cout << jsonFile << std::endl;
    std::cout << jsonFile[0] << std::endl;
    std::cout << jsonFile[0]["id"] << std::endl;

    ClassicCrypto classicCrypto(jsonFile); 
    classicCrypto.print();

    ClassicCrypto deserialized;
    deserialized.Deserialize(classicCrypto.Serialize());

    std::cout << "*******DESERIALIZED*******" << std::endl;
    deserialized.print();

    // START PREMIUM
    std::cout << "******************START PREMIUM*****************" << std::endl;
    json jsonFile2;
    std::string premiumFolderPath = "/home/mickael/github/PublisherSubscriber/data/premium/";  

    std::cout << filePremiumNames[0].c_str() << endl;
    premiumFolderPath.append(filePremiumNames[0]);
    std::cout << premiumFolderPath.c_str() << endl;

    std::ifstream file2(premiumFolderPath.c_str());
    file2 >> jsonFile2;
    std::cout << jsonFile2.dump(4) << std::endl;
    std::cout << jsonFile2 << std::endl;
    std::cout << jsonFile2[0] << std::endl;
    std::cout << jsonFile2[0]["id"] << std::endl;

    PremiumCrypto premiumCrypto(jsonFile2); 
    premiumCrypto.print();

    PremiumCrypto premdeserialized;
    premdeserialized.Deserialize(premiumCrypto.Serialize());

    std::cout << "*******DESERIALIZED*******" << std::endl;
    premdeserialized.print();
 */
}

int main()
{
    CryptoGenerator cryptoGenerator;
    cryptoGenerator.run();
    return 0;
}