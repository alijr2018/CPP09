#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>
#include <climits>
#include <exception>
#include <cctype>


class RPN
{
    public:
        RPN();
        ~RPN();
        RPN(const RPN &h);
        RPN& operator=(const RPN &h);
        long operation(long a, long b, const std::string &op);

};
#endif