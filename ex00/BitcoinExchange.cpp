#include "BitcoinExchange.hpp"

Bitcoin::Bitcoin(){};
Bitcoin::~Bitcoin(){};

void Bitcoin::start(std::ifstream &input,std::ifstream &data)
{
    // (void)j;
    std::map<std::string, int> bitin;
    std::map<std::string, float> bitout;

    std::string in, da;
    std::getline(input, in);
    if (!getline(input, in) || in != "date | value")
        return;

    if (!getline(data, in) || in != "date,exchange_rate")
        return;

    while(std::getline(data, da))
    {
        std::stringstream parse(da);
        std::string date;
        std::string value;

        std::getline(parse, date, ',');
        std::getline(parse, value);
        
        bitout[date] = std::atof(value.c_str());
    }

    while(std::getline(input, da))
    {
        std::stringstream parse(da);
        std::string date;
        std::string value;

        std::getline(parse, date, '|');
        std::getline(parse, value);
        
        date.erase(date.find_last_not_of(" \t") + 1);//it could be failure
        value.erase(0, value.find_first_not_of(" \t"));//it could be failure

        float amount = std::atof(value.c_str());
        // std::map<std::string, float>::iterator it = bitout.lower_bound(date);

        // if (it == bitout.end())
        //     --it;
        // else if (it->first != date)
        // {
        //     if (it == bitout.begin())
        //     {
        //         std::cout << "Error: no earlier date." << std::endl;
        //         continue;
        //     }
        //     --it;
        // }

        // std::cout << date << " => "
        //           << amount << " = "
        //           << amount * it->second << std::endl;
    }
        // use std::map::lower_bound() It returns an iterator to the first element whose key is greater than or equal to the key you provide.
    }
        // std::cout << in << std::endl;
    // std::cout << in << std::endl;

    // std::cout << "input ^|" << std::endl;

    // while(getline(data, da))
    //     // std::cout << da << std::endl;
    
    //     std::cout << da << std::endl;
    
    // std::cout << "input ^|^" << std::endl;


