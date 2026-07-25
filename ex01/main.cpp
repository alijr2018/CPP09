#include "RPN.hpp"

// as the container used it will be used stack 
// 3 3 + => 3 + 3 => 6

bool check(const std::string &h)
{
    if (h.size() != 1)
        return false;
    return true;
}

int main(int ac, char **av)
{
    std::cout << std::string(500, '~') << '\n';
    if (ac != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    
    // std::cout << av[1] << std::endl;

    // std::stack k(atoi(av[1]));
    // std::stack q(av[1]);
    std::stack<int> num;// this will hold numbers
    std::stack<int> op;// this will operation

    std::stringstream ss(av[1]);
    std::string ch;
    while(ss >> ch)
        std::cout << ch << " ";
    std::cout << std::endl;

}