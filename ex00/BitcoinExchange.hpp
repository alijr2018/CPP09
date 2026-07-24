#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <ostream>
#include <algorithm>
#include <map>
#include <sstream>
// #include <stdio.h>

class Bitcoin
{
    public:
        // std::string date;
        // float       value;
        Bitcoin();
        Bitcoin(const Bitcoin &h);
        ~Bitcoin();
        Bitcoin& operator=(const Bitcoin &h);

        // void start(std::string &j);
        // void start(std::ifstream &input,std::ifstream &data);
        void start(std::ifstream &input,std::ifstream &data);



};

#endif