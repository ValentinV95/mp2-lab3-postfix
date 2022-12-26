#include <iostream>
#include "string"
#include "stack.h"
#include <map>
#include <vector>
#include <functional>
#include <cmath>

#pragma once

// ���������� ������� � ������� ��� ���������� �������������� ���������
using  std::string;

/*����������� ����� ����������, ������� ���������� ����������, ��� ����
*�������� ������
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

/*����� ��� ������� � ��������.������ �� �������� ������������ ���������
*������������� �������� � ����� �������, ����������� ��������
*/
   extern std::map<string, std::function<double(double)>> function;
   extern std::map<string, std::function<double(double, double)>> inf_op;
//����� ����������. ���������� ������
   extern std::map<string, double> variables;

//������������� ���, �������� ��������� ��������
enum Priority { foo, power, mult_div, add_sub, brack };

//�����, ����������� ���������� ���������.
  class TPostfix {
  private:
/*��������������� �����, �������������� ��������� ������� ���������. ��������
*��������� ������������� �������, ������� ������ � ������� �����
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
/*�����-��������� �������. �������� ������� �������� � � ��������
*/
  class operands : public Lexem{
  public:
      double value;

      operands(string input, size_t left, size_t right) :Lexem(input, left, right) { Set(input); };
      operands(double input, size_t left, size_t right) :Lexem("_", left, right), value(input) {};
      void Set(const string input) override;
  };
/*�����-��������� �������. �������� ������� ��������� � � ���������
*/
  class operators : public Lexem {
  public:
      Priority priority;

      operators(string input, size_t left, size_t right) :Lexem(input, left, right) { Set(input); };
      void Set(const string input) override;
  };

   std::vector <Lexem *> out; //����������� ����� ���������, �������� �� �������
public:
    TPostfix(const string input);
    ~TPostfix() = default;
    friend double solve(const TPostfix & obj);
    friend std::ostream& operator <<(std::ostream& os, const TPostfix& obj) ;
};
    
  double string_to_double(string input); 