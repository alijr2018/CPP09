#include "PmergeMe.hpp"

std::vector<int> ernst(int n)// this function create the Jacobsthal numbers. sequence
{
    //Jn = Jn-1 + 2Jn-2;
    // int J0 = 0, J1 = 1;
    std::vector<int> Jn;
    Jn.push_back(0);
    Jn.push_back(1);
    for (int i = 2; i <= 10; i++)
    {
        Jn.push_back((std::pow(2, i) - std::pow(-1, i)) / 3);
        // Jn.push_back((2^n - (-1)^n) / 3);
    }
    // for (std::vector<int>::iterator it = Jn.begin(); it != Jn.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    for (int i = 0; i < Jn.size(); i++)
    {
        std::cout << Jn[i] << std::endl;
    }
    return Jn;
    // return 0;
}

int main()
{

    
    return 0;
}