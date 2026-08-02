#include "RPN.hpp"


bool isnum(const std::string &arg)
{
    return arg.size() == 1 && std::isdigit(static_cast<unsigned char>(arg[0]));
}

bool isOperator(const std::string &arg)
{
    return arg.size() == 1 && (arg[0] == '+' || arg[0] == '-' || arg[0] == '*' || arg[0] == '/');
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: usage: ./RPN \"7 7 *\"" << std::endl;
        return 1;
    }

    std::stack<long> num;
    RPN l;
    std::stringstream ss(av[1]);
    std::string ch;
    long res = 0;
    try
    {
        while(ss >> ch)
        {
            if (isnum(ch))
                num.push(ch[0] - '0');

            else if (isOperator(ch))
            {
                if (num.size() < 2)
                {
                    throw std::runtime_error("Error");
                }

                long b = num.top();
                num.pop();

                long a = num.top();
                num.pop();

                res = l.operation(a , b, ch);
                num.push(res);
            }
            else
            {
                throw std::runtime_error("Error");
            }
        }
        if (num.size() != 1)
        {
            throw std::runtime_error("Error");
        }
        std::cout << num.top() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}