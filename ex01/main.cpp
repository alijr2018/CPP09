#include "RPN.hpp"

// as the container used it will be used stack 
// 3 3 + => 3 + 3 => 6

bool check(const std::string &h)
{
    if (h.size() != 1)
        return false;
    return true;
}
long RPN::operation(long a, long b, const std::string &op)
{
    if (op == "+")
    {
        if ((b > 0 && a > LONG_MAX - b) || (b < 0 && a < LONG_MIN - b))
        {
            // std::cerr << "Error" << std::endl;
            throw std::runtime_error("Error");
            // exit(1);
            // throw std::runtime_error("Error");

        }
        return a + b;
    }
    if (op == "-")
    {
        if ((b < 0 && a > LONG_MAX + b) || (b > 0 && a < LONG_MIN + b))
        {
            // std::cerr << "Error" << std::endl;
            // exit(1);
            throw std::runtime_error("Error");

        }

        return a - b;
    }
    if (op == "*")
    {
        // if (a > LONG_MAX / b || a < LONG_MAX / b)
        // {
            // std::cerr << "Error" << std::endl;
            // exit(1);
        // }
        if (a != 0 && b != 0)
        {
            if (a > 0)
            {
                if (b > 0 && a > LONG_MAX / b)
                {
                    // std::cerr << "Error" << std::endl;
                    // exit(1);
                    throw std::runtime_error("Error");

                }

                if (b < 0 && b < LONG_MIN / a)
                {
                    // std::cerr << "Error" << std::endl;
                    // exit(1);
                    throw std::runtime_error("Error");

                }

            }
            else
            {
                if (b > 0 && a < LONG_MIN / b)
                {
                    // std::cerr << "Error" << std::endl;
                    // exit(1);
                    throw std::runtime_error("Error");

                }

                if (b < 0 && a < LONG_MAX / b)
                {
                    // std::cerr << "Error" << std::endl;
                    // exit(1);
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
            // std::cout << "Error: division by zero" << std::endl;
            // exit(1);
            throw std::runtime_error("Error: division by zero");

        }

        if (a == LONG_MIN && b == -1)
        {
            throw std::runtime_error("Error: overflow");

            // std::cout << "Error: overflow" << std::endl;
            // exit(1);
        }
        return a / b;
    }
    throw std::runtime_error("Error operator not found");

    // std::cout << "Error operator not found" << std::endl;
    // return -1;
}

bool isnum(const std::string &arg)
{
    return arg.size() == 1 && std::isdigit(static_cast<unsigned char>(arg[0]));
}
int main(int ac, char **av)
{
    // std::cout << std::string(500, '~') << '\n';
    // if (ac != 2)
    // {
    //     std::cerr << "Error , it must be like ./RPN" << " \" 7 7 * 7 - \" " << std::endl;
    //     return 1;
    // }
    
    // std::cout << av[1] << std::endl;

    // std::stack k(atoi(av[1]));
    // std::stack q(av[1]);
    // char a = {"+", "-", "/"};
    std::stack<long> num;// this will hold numbers
    // std::stack<int> op;// this will operation
    RPN l;
    std::stringstream ss(av[1]);
    std::string ch;
    long res = 0;
    try
    {
         if (ac != 2)
        {
            throw std::runtime_error("Error , it must be like ./RPN \" 7 7 * 7 - \" " );
            // std::cerr << "Error , it must be like ./RPN" << " \" 7 7 * 7 - \" " << std::endl;
            // return 1;
        }
        while(ss >> ch)
        {
            // std::cout << ch << " ";
            if (isnum(ch))
                num.push(ch[0] - '0');

            else
            {
                if (num.size() < 2)
                {
                    // std::cout << "Error it sould be a number between 0-9" << std::endl;
                    // std::cout << "Error" << std::endl;
                    throw std::runtime_error("Error it sould be a number between 0-9");

                    // return 1;
                }

                long b = num.top();
                num.pop();

                long a = num.top();
                num.pop();

                res = l.operation(a , b, ch);
                num.push(res);
            }
        }
        if (num.size() != 1)
        {
            throw std::runtime_error("Error");
            // return 1;
        }
        // std::cout << num << std::endl;
        std::cout << num.top() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    
 
    return 0;
}