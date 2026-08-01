#include "PmergeMe.hpp"



int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    // std::vector<std::vector<int> > pairs;
    std::vector<int> pair;

    for (int i = 1; i < ac ;i++)
    {
        std::string token(av[i]);
        if (!isStrictPositiveInt(token))
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        pair.push_back(std::atoi(token.c_str()));
    }
    std::vector<std::pair<int, int> > pairs;

    bool hasStraggler = (pair.size() % 2 != 0);
    int straggler = 0;

    if (hasStraggler)
        straggler = pair.back();
    for (size_t i = 0; i + 1 < pair.size(); i += 2)
    {
        pairs.push_back(std::make_pair(pair[i], pair[i + 1]));
    }
    // std::vector<int> sorted = fordFunc(pair);
    // fordFunc(pairs);
    // fordFunc(pairs, straggler, hasStraggler);
    // std::vector<int> sorted = fordFunc(pairs, straggler, hasStraggler);

    // std::cout << "Sorted: ";

    // for (std::vector<int>::iterator it = sorted.begin();
    //     it != sorted.end(); ++it)
    // {
    //     std::cout << *it << " ";
    // }


// std::cout << std::endl;

        std::cout << "Before: ";
    
    for (std::vector<int>::iterator it = pair.begin();
         it != pair.end(); ++it)
    {
        std::cout << *it << " ";
    }
    
    std::cout << std::endl;
    
    
    clock_t start = clock();

    std::vector<int> sorted = fordFunc(pairs, straggler, hasStraggler);

    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
    
    
    std::cout << "After: ";
    
    for (std::vector<int>::iterator it = sorted.begin();
         it != sorted.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Time: " << time << " us" << std::endl;
    std::cout << "Comparisons: " << comparisons << std::endl;
    std::cout << std::endl;
    return 0;
}

// int main()
// {
//     std::vector<int> order = ernst(5);

//     std::cout << "Insertion order: ";

//     for (std::vector<int>::iterator it = order.begin();
//          it != order.end(); ++it)
//     {
//         std::cout << *it << " ";
//     }

//     std::cout << std::endl;

//     std::vector<int> order1 = generateInsertionOrder(5);
    
//     std::cout << "Insertion order1: ";
    
//     for (std::vector<int>::iterator it = order1.begin(); it != order1.end(); ++it)
//     {
//         std::cout << *it << " ";
//     }
            
//     std::cout << std::endl;
//     return 0;

// }