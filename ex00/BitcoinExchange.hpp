#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cerrno>

class Bitcoin
{
    public:
        Bitcoin();
        Bitcoin(const Bitcoin &h);
        ~Bitcoin();
        Bitcoin& operator=(const Bitcoin &h);
        void start(std::ifstream &input,std::ifstream &data);

};

#endif
