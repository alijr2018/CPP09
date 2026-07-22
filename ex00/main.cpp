#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2 || !fopen(av[1], "r"))
    {
        fprintf(stderr, "Error: could not open file.\n");//change it to cpp 
        return 1;
    }
    try
    {
        std::string arg = av[1];

    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

}