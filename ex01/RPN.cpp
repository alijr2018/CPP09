#include "RPN.hpp"

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


long RPN::operation(long a, long b, const std::string &op)
{
    if (op == "+")
    {
        if ((b > 0 && a > LONG_MAX - b) || (b < 0 && a < LONG_MIN - b))
        {
            throw std::runtime_error("Error");
        }
        return a + b;
    }
    if (op == "-")
    {
        if ((b < 0 && a > LONG_MAX + b) || (b > 0 && a < LONG_MIN + b))
        {
            throw std::runtime_error("Error");
        }

        return a - b;
    }
    if (op == "*")
    {

        if (a != 0 && b != 0)
        {
            if (a > 0)
            {
                if (b > 0 && a > LONG_MAX / b)
                {

                    throw std::runtime_error("Error");
                }

                if (b < 0 && b < LONG_MIN / a)
                {

                    throw std::runtime_error("Error");
                }

            }
            else
            {
                if (b > 0 && a < LONG_MIN / b)
                {
                    throw std::runtime_error("Error");
                }

                if (b < 0 && a < LONG_MAX / b)
                {
                    throw std::runtime_error("Error");
                }

            }
        }
        return a * b;
    }
    if (op == "/")
    {

        if (b == 0)
        {
            throw std::runtime_error("Error");
        }

        if (a == LONG_MIN && b == -1)
        {
            throw std::runtime_error("Error");
        }
        return a / b;
    }
    throw std::runtime_error("Error");
}