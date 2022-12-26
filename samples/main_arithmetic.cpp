// реализация пользовательского приложения

#include "arithmetic.h"

int main() 
{
    std::string str = "";
    std::cout << "List of operation:\n'+' - addition\n'-' - subtraction\n'*' - multiplication\n'/' - division\n'~' - unary minus" << std::endl;
    std::cout << "Enter an arithmetic expression." << std::endl;
    getline(std::cin, str);
    std::map<char, double> m;
    Postfix p;
    std::string str1;
    try 
    {
        str1 = p.ToPostfix(str);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    std::cout << std::endl << "Postfix form : " << str1 << std::endl;

    double res;

    try 
    {
        res = p.calculate(str1, m);
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
    
    std::cout << "Result : " << res << std::endl;
    return 0;
}
