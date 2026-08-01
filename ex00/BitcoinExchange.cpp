#include "BitcoinExchange.hpp"

Bitcoin::Bitcoin() {};
Bitcoin::~Bitcoin() {};

Bitcoin::Bitcoin(const Bitcoin &h)
{
    (void)h;
};

Bitcoin &Bitcoin::operator=(const Bitcoin &h)
{
    (void)h;
    return *this;
};

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
    if (day < 1 || day > days[month - 1])
        return false;
        
    return true;
}

bool change(const std::string &num, double &value)
{
    char *e;
    errno = 0;
    
    value = strtod(num.c_str(), &e);

    if (e == num.c_str())
        return false;
        
    if (*e != '\0' || errno == ERANGE)
        return (false);
    return (true);
}

bool validValue(const std::string &value)
{
    double n;
    if (!change(value, n))
        return false;

    if (n < 0 || n > 1000)
        return false;

    return true;
}

void trim(std::string& s)
{
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos)
    {
        s.clear();
        return;
    }
    size_t end = s.find_last_not_of(" \t");
    s = s.substr(start, end - start + 1);
}

void Bitcoin::start(std::ifstream &input,std::ifstream &data)
{
    std::map<std::string, double> bitout;

    std::string line;

    if (!getline(input, line))
    {
        std::cout << "Error: empty input file." << std::endl;
        return ;
    }
    trim(line);
    if (line != "date | value")
    {
        std::cout << "Error: invalid input header." << std::endl; 
        return;
    }
    if (!getline(data, line))
    {
        std::cout << "Error: empty input file." << std::endl;
        return ;
    }
    trim(line);
    if (line != "date,exchange_rate")
    {
        std::cout << "Error: invalid data header." << std::endl;
        return ;
    }

    while(std::getline(data, line))
    {
        if (line.empty())
            continue;
        size_t pos = line.find(',');

        if (pos == std::string::npos)
            continue;

        std::string date = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        
        trim(date);
        trim(value);

        if (!validDate(date))
            continue;
        double amount;

        if (!change(value, amount))
            continue;
        
        bitout[date] = amount;
    }

    while(std::getline(input, line))
    {
        if (line.empty())
            continue;

        size_t pos =line.find('|');

        if (pos == std::string::npos || line.find('|', pos + 1) != std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
 
        std::string dates = line.substr(0, pos);
        std::string values = line.substr(pos + 1);
        
        trim(dates);
        trim(values);

        if (!validDate(dates))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        double amount;
        if (!change(values, amount))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (amount > 1000)
        {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }
        if (amount < 0) 
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        std::map<std::string, double>::iterator it = bitout.lower_bound(dates);

        if (it == bitout.end() || it->first != dates)
        {
            if (it == bitout.begin())
            {
                std::cout << "Error: bad input => " << dates << std::endl;
                continue;
            }
            --it;
        }

        std::cout << dates << " => " << values << " = "  << std::fixed << std::setprecision(2) << amount * it->second << std::endl;
    }
}

