#include "BitcoinExchange.hpp"

Bitcoin::Bitcoin(){};
Bitcoin::~Bitcoin(){};

void Bitcoin::start(std::string &j)
{
    std::ifstream input(j.c_str());
    if (!input)
        throw std::runtime_error("file won't open");
}

