#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: it must be ./btc input.txt" << std::endl;
        return 1;
    }
    std::ifstream input(av[1]);
    std::ifstream data("data.csv");
    if (!data || !input)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    Bitcoin btc;
    btc.start(input, data);
    
    return 0;
}