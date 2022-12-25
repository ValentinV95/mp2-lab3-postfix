#include <iostream>
#include "string"
#include "stack.h"
#include <map>
#include <vector>
#include <functional>
#include <cmath>
// объявление функций и классов для вычисления арифметических выражений
using  std::string;

/*Собственный класс исключений, который возвращает промежуток, где была
*допущена ошибка
*/
class MyException : public std::invalid_argument
{
private:
    size_t left;
    size_t right;
public:
    MyException(std::string s,size_t left,size_t right) : std::invalid_argument(s.c_str()), left(left), right(right){}
    ~MyException() = default;
    const char* what() const override
    {
        size_t i = 0;
        size_t l = left;
        size_t r = right;
        Tstack<char> digit;
        char * tmp = new char[1024];
        strcpy(tmp, this->invalid_argument::what());
        while (tmp[i] != '\0') { i++; }
        do
        {
            char c = static_cast<char>(l % 10) + '0';
            l = l /10;
            digit.push(c);
        } while (l > 0);
        while (!digit.isEmpty())
        {
            tmp[i++] = digit.pop();
        }
        tmp[i++] = '-';
        while (r > 0)
        {
            char c = static_cast<char>(r % 10) + '0';
            r = r / 10;
            digit.push(c);
        }
        while (!digit.isEmpty())
        {
            tmp[i++] = digit.pop();
        }
        tmp[i] = '\0';
        return tmp; 
    };
};

//Перечисляемый тип, хранящий приоритет операций
  enum Priority{ foo,power, mult_div,add_sub, brack};

//Карта переменных. На начало выполнения пустая  
  std::map <string, double> variables;

/*Карта для функций и операций.Ставит во взаимное соответствие строковое
*представление операции и лябда функцию, вычисляющюю значение
*/
  std::map<string, std::function<double(double)>> function ={ 
      {"~",[](double a)          {return (-1 * a); }},
      {"sin",[](double a)        {return sin(a); }},
      {"cos",[](double a)        {return cos(a); }},
      {"sqrt",[](double a)       {return sqrt(a); }},
      {"log",[](double a)        {return log(a); }},
      {"lg",[](double a)         {return log10(a); }},
      {"ln",[](double a)         {return log(a); }},
  };
  std::map<string, std::function<double(double, double)>> inf_op = {
      {"+",[](double a,double b) {return a + b; }},
      {"-",[](double a,double b) {return a - b; }}, 
      {"*",[](double a,double b) {return a * b; }},
      {"/",[](double a,double b) {return a / b; }},
      {"^",[](double a,double b) {return pow(a,b); }}
  };
  
//Класс, реализующий вычисления выражений.
  class TPostfix {
  private:
/*Вспомогательный класс, представляющий отдельную лексему выражения. Содержит
*строковое представление лексемы, позицию начала и позицию конца
*/
  class Lexem {
  public:
      string data;
      size_t left;
      size_t right;
      Lexem(string s = "_", size_t l = 0, size_t r = 0) :data(s), left(l), right(r) {};

      virtual void Set(const string input) = 0;
      virtual ~Lexem() = default;
  };
/*Класс-наследник лексемы. Содержит лексему операнда и её значение
*/
  class operands : public Lexem{
  public:
      double value;

      operands(string input, size_t left, size_t right) :Lexem(input, left, right) { Set(input); };
      operands(double input, size_t left, size_t right) :Lexem("_", left, right), value(input) {};
      void Set(const string input) override;
  };
/*Класс-наследник лексемы. Содержит лексему оператора и её приоритет
*/
  class operators : public Lexem {
  public:
      Priority priority;

      operators(string input, size_t left, size_t right) :Lexem(input, left, right) { Set(input); };
      void Set(const string input) override;
  };

    std::vector <Lexem *> out; //постфиксная форма выражения, разбитая на лексемы
public:
    TPostfix(const string input);
    ~TPostfix() = default;
    friend double solve(const TPostfix & obj);
    friend std::ostream& operator <<(std::ostream& os, const TPostfix& obj) ;
};
    
  double string_to_double(string input); 