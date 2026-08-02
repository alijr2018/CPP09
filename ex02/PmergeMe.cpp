#include "PmergeMe.hpp"


PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}


bool PmergeMe::isStrictPositiveInt(const std::string &token)
{
    if (token.empty())
        return false;

    char *end = NULL;
    errno = 0;
    long value = std::strtol(token.c_str(), &end, 10);

    if (*end != '\0' || errno == ERANGE)
        return false;
    if (value < 0 || value > INT_MAX)
        return false;
    return true;
}

std::vector<int> ernst(int n)
{

    std::vector<int> Jn;
    Jn.push_back(0);
    Jn.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        Jn.push_back((std::pow(2, i) - std::pow(-1, i)) / 3);
    }
    return Jn;
}

std::deque<int> ernstDe(int n)
{

    std::deque<int> Jn;
    Jn.push_back(0);
    Jn.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        Jn.push_back((std::pow(2, i) - std::pow(-1, i)) / 3);
    }
    return Jn;
}

std::vector<int> generateInsertionOrder(int size)
{
    std::vector<int> order;

    if (size <= 0)
        return order;


    std::vector<int> jacob = ernst(size + 10);

    int last = 1;

    for (size_t i = 3; i < jacob.size(); i++)
    {
        int j = jacob[i];

        if (j > size)
            break;

        for (int k = j; k > last; k--)
            order.push_back(k - 1);

        last = j;
    }


    for (int i = last; i < size; i++)
        order.push_back(i);


    return order;
}

std::deque<int> generateInsertionOrderDe(int size)
{
    std::deque<int> order;

    if (size <= 0)
        return order;

    std::deque<int> jacob;
    jacob.push_back(0);
    jacob.push_back(1);

    while (jacob.back() < size)
    {
        int n = jacob.size();
        jacob.push_back(jacob[n - 1] + 2 * jacob[n - 2]);
    }

    int previous = 1;

    for (size_t i = 3; i < jacob.size(); i++)
    {
        int current = jacob[i];

        if (current > size)
            current = size;

        for (int j = current; j > previous; j--)
            order.push_back(j - 1);

        previous = current;

        if (current == size)
            break;
    }

    return order;
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


void simpleSort(std::deque<int>& numbers)
{
    if (numbers.size() <= 1)
        return;

    std::deque<int> left;
    std::deque<int> right;

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


        if (mainChain[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }

    mainChain.insert(mainChain.begin() + left, value);
}

void binaryInsert(std::deque<int>& mainChain, int value, int limit)
{
    if (limit > (int)mainChain.size())
        limit = mainChain.size();

    int left = 0;
    int right = limit;

    while (left < right)
    {
        int mid = (left + right) / 2;


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

    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin();
         it != pairs.end(); ++it)
    {
        if (it->first < it->second)
            std::swap(it->first, it->second);
    }

    std::vector<int> winners;

    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin();
         it != pairs.end(); ++it)
    {
        winners.push_back(it->first);
    }


    simpleSort(winners);

    std::vector<std::pair<int,int> > sortedPairs;
    std::vector<bool> used(pairs.size(), false);

    for (std::vector<int>::iterator w = winners.begin(); w != winners.end(); ++w)
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

void fordSortWinners(std::deque<std::pair<int, int> >& pairs)
{
    if (pairs.size() <= 1)
        return;


    // make sure first is the winner
    for (std::deque<std::pair<int,int> >::iterator it = pairs.begin();
         it != pairs.end(); ++it)
    {
        if (it->first < it->second)
            std::swap(it->first, it->second);
    }

    std::deque<int> winners;

    for (std::deque<std::pair<int,int> >::iterator it = pairs.begin();
         it != pairs.end(); ++it)
    {
        winners.push_back(it->first);
    }

    simpleSort(winners);

    std::deque<std::pair<int,int> > sortedPairs;
    std::deque<bool> used(pairs.size(), false);

    for (std::deque<int>::iterator w = winners.begin();
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

std::deque<std::pair<int,int> > PmergeMe::sortPairs(std::deque<std::pair<int,int> > pairs)
{
    if (pairs.size() <= 1)
        return pairs;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first < pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }

    std::deque<int> winners;

    for (size_t i = 0; i < pairs.size(); i++)
        winners.push_back(pairs[i].first);

    winners = mergeInsd(winners);

    std::deque<std::pair<int,int> > result;
    std::vector<bool> used(pairs.size(), false);

    for (size_t i = 0; i < winners.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].first == winners[i])
            {
                result.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    return result;
}

std::vector<int> PmergeMe::fordFunc(std::vector<std::pair<int, int> > &pairs, int straggler, bool hasStraggler)
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
            binaryInsert(result, straggler, result.size());

        return result;
    }

    // Step 1: put larger element first
    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {

        if (it->first < it->second)
            std::swap(it->first, it->second);
    }


    pairs = sortPairs(pairs);

    std::vector<int> mainChain;
    std::vector<std::pair<int,int> > pend;


    for (std::vector<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        mainChain.push_back(it->first);
        pend.push_back(std::make_pair(it->second, it->first));
    }


    // insert first pending element immediately
    if (!pend.empty())
    {
        mainChain.insert(mainChain.begin(), pend[0].first);
        pend.erase(pend.begin());
    }

    std::vector<int> order = generateInsertionOrder(pend.size() + 1);

    for (std::vector<int>::iterator it = order.begin(); it != order.end(); ++it)
    {
        int index = *it - 1;

        if (index < 0 || index >= (int)pend.size())
            continue;

        int value = pend[index].first;
        int partner = pend[index].second;

        int limit = 0;

        for (size_t j = 0; j < mainChain.size(); j++)
        {
            if (mainChain[j] == partner)
            {
                limit = j;
                break;
            }
        }

        binaryInsert(mainChain, value, limit + 1);
    }
    if (hasStraggler)
    {
        binaryInsert(mainChain, straggler, mainChain.size());
    }

    return mainChain;
}

std::vector<std::pair<int,int> > PmergeMe::sortPairs(std::vector<std::pair<int,int> > pairs)
{
    if (pairs.size() <= 1)
        return pairs;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first < pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }

    std::vector<int> winners;

    for (size_t i = 0; i < pairs.size(); i++)
        winners.push_back(pairs[i].first);

    winners = mergeIns(winners);
    std::vector<std::pair<int,int> > result;
    std::vector<bool> used(pairs.size(), false);

    for (size_t i = 0; i < winners.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].first == winners[i])
            {
                result.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    return result;
}


// std::deque<int> fordFunc(std::deque<std::pair<int, int> > &pairs, int straggler, bool hasStraggler)
std::deque<int> PmergeMe::fordFunc(std::deque<std::pair<int, int> > &pairs, int straggler, bool hasStraggler)
{
    if (pairs.size() == 0)
    {
        std::deque<int> result;

        if (hasStraggler)
            result.push_back(straggler);

        return result;
    }

    if (pairs.size() == 1)
    {
        std::deque<int> result;

        result.push_back(pairs[0].second);
        result.push_back(pairs[0].first);

        if (hasStraggler)
            binaryInsert(result, straggler, result.size());


        return result;
    }

    // Step 1: put larger element first
    for (std::deque<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {

        if (it->first < it->second)
            std::swap(it->first, it->second);
    }

    pairs = sortPairs(pairs);

    std::deque<int> mainChain;
    std::deque<std::pair<int,int> > pend;


    for (std::deque<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        mainChain.push_back(it->first);

        // store b and its partner a
        pend.push_back(std::make_pair(it->second, it->first));
    }

    if (!pend.empty())
    {
        mainChain.insert(mainChain.begin(), pend[0].first);
        pend.erase(pend.begin());
    }

    std::deque<int> order = generateInsertionOrderDe(pend.size() + 1);

    for (std::deque<int>::iterator it = order.begin(); it != order.end(); ++it)
    {
        int index = *it - 1;

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

        binaryInsert(mainChain, value, limit + 1);
    }


    if (hasStraggler)
    {
        binaryInsert(mainChain, straggler, mainChain.size());
    }

    return mainChain;
}


std::deque<int> PmergeMe::mergeInsd(const std::deque<int> &input)
{
    if (input.size() <= 1)
        return input;
    
    std::deque<std::pair<int, int> > pairs;
        
    bool hasStraggler = (input.size() % 2 != 0);
    int straggler = 0;

    if (hasStraggler)
        straggler = input.back();
    for (size_t i = 0; i + 1 < input.size(); i += 2)
    {
        int f = input[i];
        int s = input[i + 1];

        if (f < s)
            std::swap(f, s);
        pairs.push_back(std::make_pair(f, s));
    }

    return fordFunc(pairs, straggler, hasStraggler);
}
std::vector<int> PmergeMe::mergeIns(const std::vector<int> &input)
{
    if (input.size() <= 1)
        return input;
    
    if (input.size() == 2)
    {
        std::vector<int> res = input;

        if (res[0] > res[1])
            std::swap(res[0], res[1]);
        return res;
    }
        
    std::vector<std::pair<int, int> > pairs;

        
    bool hasStraggler = (input.size() % 2 != 0);
    int straggler = 0;

    if (hasStraggler)
        straggler = input.back();
    for (size_t i = 0; i + 1 < input.size(); i += 2)
    {
        int f = input[i];
        int s = input[i + 1];

        if (f < s)
            std::swap(f, s);
        pairs.push_back(std::make_pair(f, s));
    }

    return (fordFunc(pairs, straggler, hasStraggler));
}