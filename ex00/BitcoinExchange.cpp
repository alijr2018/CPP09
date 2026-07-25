#include "BitcoinExchange.hpp"

Bitcoin::Bitcoin(){};
Bitcoin::~Bitcoin(){};

bool validDate(const std::string &date)
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.size(); i++)
    {
        if ((i != 4 && i != 7) && !isdigit(date[i]))
            return false;
    }
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12)
        return false;

    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap= ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    if (leap)
        days[1] = 29;
    if (day < 1 || day > days[month - 1]) // check month that has 28 day check leap year
        return false;
        
    return true;
}

bool validValue(const std::string &value)
{
    bool dot = false;
    bool digit = false;

    for (size_t i = 0; i < value.size(); i++)
    {
        if (value[i] == '.')
        {
            if (dot)
                return false;
            dot = true;
        }
        else if (isdigit(value[i]))
        {
            digit = true;
        }
        else
        {
            return false;
        }
    }

    if (!digit)
        return false;

    float n = std::atof(value.c_str());

    if (n <= 0 || n > 1000)
        return false;

    return true;
}
void Bitcoin::start(std::ifstream &input,std::ifstream &data)
{
    // (void)j;

    //std::map<std::string, float> bitin;
    std::map<std::string, float> bitout;

    std::string line;
    // std::getline(input, line);
    if (!getline(input, line) || line != "date | value")
    {
        // throw std::runtime_error("Error: invalid input header.");
        std::cout << "Error: invalid input header." << std::endl; 
       // return;
    }

    if (!getline(data, line) || line != "date,exchange_rate")
    {
        // throw std::runtime_error("Error: invalid data header.");
        std::cout << "Error: invalid data header." << std::endl; 

       // return;
    }

    while(std::getline(data, line))// data parse
    {
        std::stringstream parse(line);
        std::string date, value;

        std::getline(parse, date, ',');
        std::getline(parse, value);
        
        bitout[date] = std::atof(value.c_str());
    }

    while(std::getline(input, line))// input parse
    {
        std::stringstream parse(line);
        std::string dates, values;

        std::getline(parse, dates, '|');
        std::getline(parse, values);
        
        //check this trim later
        size_t pos = dates.find_last_not_of(" \t");
        if (pos != std::string::npos)
            dates.erase(pos + 1);
        else
            dates.clear();

        pos = values.find_first_not_of(" \t");
        if (pos != std::string::npos)
            values.erase(0, pos);
        else
            values.clear();

        //add validate date and value

        if (!validDate(dates))
        {
            std::cout << "Error: Bad input => " << line << std::endl;
            continue;
        }

        if (!validValue(values))
        {
            float n = atof(values.c_str());
            if (n > 1000)
                std::cout << "Error: too large a number." << std::endl;
            else 
                std::cout << "Error: not a positive number." << std::endl;

            continue;
        }


        float amount = std::atof(values.c_str());
        std::map<std::string, float>::iterator it = bitout.lower_bound(dates);


        if (it == bitout.end() || it->first != dates)
        {
            if (it == bitout.begin())
            {
                std::cout << "Error: bad input => " << dates << std::endl;
                continue;
            }
            --it;
        }

        std::cout << std::fixed << std::setprecision(2);
        std::cout << dates << " => " << amount << " = " << amount * it->second << std::endl;
    

    }
    // for (std::map<std::string, float>::iterator it = bitin.begin(); it != bitin.end(); it++)
    // {
        // std::cout << "date " << it->first << " value " << it->second <<std::endl;
    // }
    // for (std::map<std::string, float>::iterator it = bitout.begin(); it != bitout.end(); it++)
    // {
        // std::cout << "date " << it->first << " value " << it->second <<std::endl;
    // }

}


