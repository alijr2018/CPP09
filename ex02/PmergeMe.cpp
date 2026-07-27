#include "PmergeMe.hpp"
long comparisons = 0;
std::vector<int> ernst(int n)// this function create the Jacobsthal numbers. sequence
{

    std::vector<int> Jn;
    Jn.push_back(0);
    Jn.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        Jn.push_back((std::pow(2, i) - std::pow(-1, i)) / 3);
        // Jn.push_back((2^n - (-1)^n) / 3);
    }
    // for (std::vector<int>::iterator it = Jn.begin(); it != Jn.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    // for (int i = 0; i < Jn.size(); i++)
    // {
    //     std::cout << Jn[i] << std::endl;
    // }
    return Jn;
    // return 0;
}
std::vector<int> generateInsertionOrder(int size)
{
    std::vector<int> order;

    if (size == 0)
        return order;

    std::vector<int> jacob = ernst(size + 5);

    int previous = 1;

    for (size_t i = 3; i < jacob.size(); i++)
    {
        int current = jacob[i];

        if (current > size)
            break;

        order.push_back(current);

        for (int j = current - 1; j > previous; j--)
        {
            order.push_back(j);
        }

        previous = current;
    }

    // Add missing last elements
    for (int i = previous + 1; i <= size; i++)
    {
        order.push_back(i);
    }

    return order;
}

void sortPairs(std::vector<std::pair<int, int> > &pairs)
{
    if (pairs.size() <= 1)
        return ;
    std::vector<int> larger;

    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        larger.push_back(it->first);
    }
    std::cout << "larger elements:" << std::endl;
    for (std::vector<int>::iterator it = larger.begin(); it != larger.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
void sortByFirst(std::vector<std::pair<int,int> >& pairs)
{
    for (size_t i = 0; i < pairs.size(); i++)
    {
        for (size_t j = i + 1; j < pairs.size(); j++)
        {
            if (pairs[i].first > pairs[j].first)
            {
                std::swap(pairs[i], pairs[j]);
            }
        }
    }
}

void simpleSort(std::vector<int>& numbers)
{
    if (numbers.size() <= 1)
        return;

    std::vector<int> left;
    std::vector<int> right;

    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (i < numbers.size() / 2)
            left.push_back(numbers[i]);
        else
            right.push_back(numbers[i]);
    }

    simpleSort(left);
    simpleSort(right);

    numbers.clear();

    size_t i = 0;
    size_t j = 0;

    while (i < left.size() && j < right.size())
    {
        comparisons++;

        if (left[i] < right[j])
            numbers.push_back(left[i++]);
        else
            numbers.push_back(right[j++]);
    }

    while (i < left.size())
        numbers.push_back(left[i++]);

    while (j < right.size())
        numbers.push_back(right[j++]);
}
void binaryInsert(std::vector<int>& mainChain, int value, int limit)
{
    if (limit > (int)mainChain.size())
        limit = mainChain.size();

    int left = 0;
    int right = limit;

    while (left < right)
    {
        int mid = (left + right) / 2;

        comparisons++;

        if (mainChain[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }

    mainChain.insert(mainChain.begin() + left, value);
}
void fordSortWinners(std::vector<std::pair<int, int> >& pairs)
{
    if (pairs.size() <= 1)
        return;


    // make sure first is the winner
    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin();
         it != pairs.end(); ++it)
    {
        if (it->first < it->second)
            std::swap(it->first, it->second);
    }


    // extract winners
    std::vector<int> winners;

    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin();
         it != pairs.end(); ++it)
    {
        winners.push_back(it->first);
    }


    // sort winners recursively
    simpleSort(winners);


    // rebuild pairs according to sorted winners
    std::vector<std::pair<int,int> > sortedPairs;
    std::vector<bool> used(pairs.size(), false);

    for (std::vector<int>::iterator w = winners.begin();
        w != winners.end(); ++w)
    {
        for (size_t i = 0; i < pairs.size(); i++)
        {
            if (!used[i] && pairs[i].first == *w)
            {
                sortedPairs.push_back(pairs[i]);
                used[i] = true;
                break;
            }
        }
    }

    pairs = sortedPairs;
}
// std::vector<int> fordFunc(std::vector<int> &pair)
// void  fordFunc(std::vector<int> &pair)
// void fordFunc(std::vector<std::pair<int, int> > &pairs)
// void fordFunc(std::vector<std::pair<int, int> > &pairs, int straggler, bool hasStraggler)
std::vector<int> fordFunc(std::vector<std::pair<int, int> > &pairs, int straggler, bool hasStraggler)
{
    if (pairs.size() == 0)
    {
        std::vector<int> result;

        if (hasStraggler)
            result.push_back(straggler);

        return result;
    }

    if (pairs.size() == 1)
    {
        std::vector<int> result;

        result.push_back(pairs[0].second);
        result.push_back(pairs[0].first);

        if (hasStraggler)
            result.push_back(straggler);

        simpleSort(result);

        return result;
    }

    // Step 1: put larger element first
    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        comparisons++;

        if (it->first < it->second)
            std::swap(it->first, it->second);
    }


    // Step 2: extract larger elements
    std::vector<int> larger;

    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin();
         it != pairs.end(); ++it)
    {
        larger.push_back(it->first);
    }


    // Step 3: recursive Ford-Johnson sorting of larger elements

    std::vector<std::pair<int,int> > recursivePairs;

    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        recursivePairs.push_back(*it);
    }

    fordSortWinners(recursivePairs);


    larger.clear();

    for (std::vector<std::pair<int,int> >::iterator it = recursivePairs.begin();
         it != recursivePairs.end(); ++it)
    {
        larger.push_back(it->first);
    }


    // Step 4: rebuild pairs according to sorted winners

    std::vector<std::pair<int,int> > sortedPairs;
    std::vector<bool> used(pairs.size(), false);

    for (std::vector<int>::iterator num = larger.begin();
        num != larger.end(); ++num)
    {
        for (size_t i = 0; i < pairs.size(); i++)
        {
            comparisons++;

            if (!used[i] && pairs[i].first == *num)
            {
                sortedPairs.push_back(pairs[i]);
                used[i] = true;
                break;
            }
        }
    }

    pairs = sortedPairs;

    // std::cout << "After rebuilding pairs:" << std::endl;

    // for (std::vector<std::pair<int,int> >::iterator it = pairs.begin();
    //     it != pairs.end(); ++it)
    // {
    //     std::cout << "(" << it->first << "," << it->second << ") ";
    // }

    std::cout << std::endl;
    // Step 5: create main chain and pend

    std::vector<int> mainChain;
    // std::vector<int> pend;
    std::vector<std::pair<int,int> > pend;

    // for (std::vector<std::pair<int,int> >::iterator it = pairs.begin();
    //      it != pairs.end(); ++it)
    // {
    //     mainChain.push_back(it->first);
    //     pend.push_back(it->second);
    // }

    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        mainChain.push_back(it->first);

        // store b and its partner a
        pend.push_back(std::make_pair(it->second, it->first));
    }
    // std::cout << "Pend:" << std::endl;

    // for (std::vector<std::pair<int,int> >::iterator it = pend.begin();
    //     it != pend.end(); ++it)
    // {
    //     std::cout << "b=" << it->first 
    //             << " partner=" << it->second << std::endl;
    // }
    // Step 6: insert b1

    if (!pend.empty())
    {
        mainChain.insert(mainChain.begin(), pend[0].first);
        pend.erase(pend.begin());
    }


    // Step 7: insert remaining pend
    // (temporary order, Jacobsthal comes next)

    std::vector<int> order = generateInsertionOrder(pend.size() + 1);

    for (std::vector<int>::iterator it = order.begin(); it != order.end(); ++it)
    {
        int index = *it - 2; 

        if (index < 0 || index >= (int)pend.size())
            continue;


        int value = pend[index].first;
        int partner = pend[index].second;


        int limit = 0;

        for (size_t i = 0; i < mainChain.size(); i++)
        {
            if (mainChain[i] == partner)
            {
                limit = i;
                break;
            }
        }


        // binaryInsert(mainChain, value, limit);
        binaryInsert(mainChain, value, limit + 1);
    }


    // Step 8: insert straggler

    if (hasStraggler)
    {
        binaryInsert(mainChain, straggler, mainChain.size());
    }

    // Final output

    return mainChain;
}



int main(int ac, char **av)
{
    // std::vector<std::vector<int> > pairs;
    std::vector<int> pair;

    for (int i = 1; i < ac ;i++)
    {
        std::stringstream ss(av[i]);

        int num;

        while(ss >> num)
            pair.push_back(num);

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