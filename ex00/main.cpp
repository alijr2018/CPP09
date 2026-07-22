#include "BitcoinExchange.hpp"


size_t strl(char *sx)
{
    if (!sx)
        return -1;
    int i = 0;
    while (sx[i])
    {
        i++;
    }
    return i;
}
bool check(std::string &h)
{
    return (h.compare(h.size()-4, 4, ".txt") == 0);
}
int main(int ac, char **av)
{
    if (ac != 2)
    {
        // fprintf(stderr, "Error: could not open file.\n");//change it to cpp 
        std::cout << "Error: it must be ./btc input.txt" << std::endl;
        return 1;
    }
    
    try
    {
        std::string arg = av[1];
        std::cout << arg<< std::endl;
        if (!check(arg))
            throw std::runtime_error("the file isn't a .txt file");
            
        Bitcoin btc;
        btc.start(arg);

    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

}