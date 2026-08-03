#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <deque>
#include <cerrno>

class PmergeMe
{
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &h);
        PmergeMe &operator=(const PmergeMe &h);
        bool isStrictPositiveInt(const std::string &token);
        std::vector<int> mergeIns(const std::vector<int> &input);
        std::deque<int> mergeInsd(const std::deque<int> &input);
        std::vector<int> fordFunc(std::vector<std::pair<int, int> > &pairs, int straggler, bool hasStraggler);
        std::deque<int> fordFunc(std::deque<std::pair<int, int> > &pairs, int straggler, bool hasStraggler);
        std::vector<std::pair<int,int> > sortPairs(std::vector<std::pair<int,int> > pairs);
        std::deque<std::pair<int,int> > sortPairs(std::deque<std::pair<int,int> > pairs);
};

#endif