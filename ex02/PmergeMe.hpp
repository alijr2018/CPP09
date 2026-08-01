#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <deque>
#include <ctime>

class PmergeMe
{
    public:
        PmergeMe();
        ~PmergeMe();
        bool isStrictPositiveInt(const std::string &token);
        std::vector<int> mergeIns(const std::vector<int> &input);
        std::deque<int> mergeIns(const std::deque<int> &input);
        long comparisons;
        void resetCom();


};

#endif