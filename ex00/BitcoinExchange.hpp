#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <ostream>
#include <algorithm>
// #include <stdio.h>

class Bitcoin
{
    public:
        Bitcoin();
        Bitcoin(const Bitcoin &h);
        ~Bitcoin();
        Bitcoin& operator=(const Bitcoin &h);

        void start(std::string &j);

};

#endif