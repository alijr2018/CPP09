#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe alpha;
    std::vector<int> original;

    for (int i = 1; i < ac ;i++)
    {
        std::string token(av[i]);
        if (!alpha.isStrictPositiveInt(token))
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        original.push_back(std::atoi(token.c_str()));
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < original.size(); i++)
        std::cout << original[i] << " ";
    std::cout << std::endl;


    std::vector<int> vec = original;
    clock_t start = clock();
    std::vector<int> sorted = alpha.mergeIns(vec);
    clock_t end = clock();
    double timeUs = double(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "After: ";
    for (size_t i = 0; i < sorted.size(); i++)
        std::cout << sorted[i] << " ";
    std::cout << std::endl;
    
    std::cout << "Time to process a range of " << original.size() << " elements with std::vector : " << timeUs << " us" << std::endl;
    
    std::deque<int> deq(original.begin(), original.end());
    clock_t start1 = clock();
    std::deque<int> sorted1 = alpha.mergeInsd(deq);
    clock_t end1 = clock();
    double timeUs1 = double(end1 - start1) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << original.size() << " elements with std::deque : " << timeUs1 << " us" << std::endl;
    
    return 0;
}
