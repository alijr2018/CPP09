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
bool check(const std::string &h,const char *s)
{
    return (h.compare(h.size()-4, 4, s) == 0);
}

bool chfi(std::ifstream &q, const std::string &u, const char *s)
{
    // std::cout << u << std::endl;
    // std::ifstream input(u.c_str());
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
    
    try
    {
        std::ifstream input;
        std::ifstream data;

        std::string arg = av[1];
        // std::cout << arg<< std::endl;
        chfi(input, arg, ".txt");
        chfi(data, "data.csv", ".csv");
            
        Bitcoin btc;
        btc.start(input, data);

    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

}