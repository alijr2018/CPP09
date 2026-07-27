#include "RPN.hpp"

// long RPN::operationp(long a, long b)
// {
//     return a + b;
// }

// long RPN::operationm(long a, long b)
// {
//     return a * b;
// }

// long RPN::operations(long a, long b)
// {
//     return a - b;
// }

// long RPN::operationd(long a, long b)
// {
//     // add check for divised by 0
//     return a / b;
// }

// long RPN::operation(long a, long b, const std::string &op)
// {
    // if (op == "+")
        // return a + b;
    // if (op == "-")
        // return a - b;
    // if (op == "*")
        // return a * b;
    // if (op == "/")
    // {
        // if (b == 0)
            // throw " zero";
        // return a / b;
    // }
    // throw "error";
// }

RPN::RPN() {};

RPN::~RPN() {};

RPN::RPN(const RPN &h)
{
    (void)h;
};

RPN& RPN::operator=(const RPN &h)
{
    (void)h;
    return *this;
};
