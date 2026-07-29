#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>
#include <climits>
#include <exception>


// template <typename T = long>
class RPN
{
    public:
        // long operationp(long a, long b);
        // long operationd(long a, long b);
        // long operationm(long a, long b);
        // long operation(long a, long b, const std::string &op);
        RPN();
        ~RPN();
        RPN(const RPN &h);
        RPN& operator=(const RPN &h);
        long operation(long a, long b, const std::string &op);

};
#endif