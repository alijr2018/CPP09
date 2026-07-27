#include "BitcoinExchange.hpp"

bool check(const std::string &h, const char *s)
{
    if (h.size() < 4)
        return false;
    return (h.compare(h.size()-4, 4, s) == 0);
}

bool chfi(std::ifstream &q, const std::string &u, const char *s)
{
    q.open(u.c_str());
    if (!q)
        throw std::runtime_error(std::string("file ") + u + " won't open");

    if (!check(u, s))
        throw std::runtime_error(std::string("the file isn't a ") + s + " file");
    return true;
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: it must be ./btc input.txt" << std::endl;
        return 1;
    }
    std::ifstream input(av[1]);
    std::ifstream data("data.csv");
    // if (!input)
    // {
    //     std::cout << "Error: could not open file." << std::endl;
    //     return 1;
    // }
    if (!data || !input)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    // std::string arg = av[1];
    // chfi(input, arg, ".txt");
    // chfi(data, "data.csv", ".csv");
    Bitcoin btc;
    btc.start(input, data);
    
    // try//remove try and catch
    // {
        //     std::ifstream input;
        //     std::ifstream data;
        
        //     std::string arg = av[1];
    //     // std::cout << arg<< std::endl;
    //     chfi(input, arg, ".txt");
    //     chfi(data, "data.csv", ".csv");
            
    //     Bitcoin btc;
    //     btc.start(input, data);

    // }
    // catch(const std::exception &e)
    // {
    //     std::cout << e.what() << std::endl;
    //     return 1;
    // }
    return 0;

}