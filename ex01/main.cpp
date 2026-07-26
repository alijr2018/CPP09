#include "RPN.hpp"

// as the container used it will be used stack 
// 3 3 + => 3 + 3 => 6

bool check(const std::string &h)
{
    if (h.size() != 1)
        return false;
    return true;
}
long operation(long a, long b, const std::string &op)
{
    if (op == "+")
        return a + b;
    if (op == "-")
        return a - b;
    if (op == "*")
        return a * b;
    if (op == "/")
    {
        if (b == 0)
            throw " zero";
        return a / b;
    }
    throw "error";
}

bool isnum(const std::string &arg)
{
    return arg.size() == 1&& std::isdigit(arg[0]);
}
int main(int ac, char **av)
{
    std::cout << std::string(500, '~') << '\n';
    if (ac != 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    // std::cout << av[1] << std::endl;

    // std::stack k(atoi(av[1]));
    // std::stack q(av[1]);
    // char a = {"+", "-", "/"};
    std::stack<int> num;// this will hold numbers
    // std::stack<int> op;// this will operation

    std::stringstream ss(av[1]);
    std::string ch;
    std::string result;
    while(ss >> ch)
    {
        std::cout << ch << " ";
        if (isnum(ch))
            num.push(ch[0] - '0');
        else
        {
            if (num.size() < 2)
                throw "wd";
            long b = num.top();
            num.pop();

            long a = num.top();
            num.pop();

            num.push(operation(a , b, ch));
        }
    }
    // std::cout << num << std::endl;
    std::cout << num.top() << '\n';
}