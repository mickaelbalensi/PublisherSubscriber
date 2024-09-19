#ifndef CRYPTO_GENERATOR
#define CRYPTO_GENERATOR

#include "publisher.hpp"        // Publisher
//#include "python_runner.hpp"
#include <vector>               // std::vector
#include <string>               // std::string


class CryptoGenerator
{
public:
    explicit CryptoGenerator();
    ~CryptoGenerator() = default;
    void run();

private:
    std::vector<std::string> fileClassicNames;
    std::vector<std::string> filePremiumNames;

    //PythonRunner m_pythonRunner;
    Publisher m_pub;
};






#endif //   CRYPTO_GENERATOR