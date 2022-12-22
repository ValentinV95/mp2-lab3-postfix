#include <iostream>
#include "string"
#include "stack.h"
#include <map>
#include <vector>
#include<functional>
#include<cmath>
// объ€вление функций и классов дл€ вычислени€ арифметических выражений
using  std::string;

  enum Priority{ brack, foo,power, mult_div,add_sub}; // „ем меньше приоритет, тем раньше нужно выполнить операцию
  std::map <string, double> variables;
  std::map<string, std::function<double(double)>> function = { {"~",[](double a) {return (-1 * a);} },
															 {"sin",[](double a) {return sin(a); }},
															 {"cos",[](double a) {return cos(a); }},
															 {"sqrt",[](double a) {return sqrt(a); }},
															 {"log",[](double a) {return log(a); }},
	                                                         {"lg",[](double a) {return log10(a); }},
															 {"ln",[](double a) {return log(a); }},
															 };
  

  class Lexem {
  public:
	  string data;
	  size_t left;
	  size_t right;
	  Lexem(string s = "_", size_t l = 0, size_t r = 0) :data(s), left(l), right(r) {};

	  virtual void Set(const string input) = 0;
	  virtual const bool is_operand() = 0;
	  virtual ~Lexem() = default;
  };

  class operands : public Lexem{
  public:
	  double value;
	  operands(string input, size_t left, size_t right) :Lexem(input, left, right) { Set(input); };
	  operands(double input, size_t left, size_t right) :Lexem("_", left, right), value(input) {};
	  const bool is_operand() override { return true; };
 	  void Set(const string input) override;

  };

  class operators : public Lexem {
  public:
	  Priority priority;
	  const bool is_operand() override { return false; };
	  operators(string input, size_t left, size_t right) :Lexem(input, left, right) { Set(input); };
	void Set(const string input) override;
  };

class TPostfix {
private:

	void check_input();
  std::vector <Lexem *> out;
public:
	TPostfix(const string input);
	~TPostfix() = default;
	friend std::ostream& operator <<(std::ostream& os, const TPostfix obj) ;
};
operands* make_inf_op(operands* l, operators* op, operands* r);
operands* make_func_op(operators* op, operands* arg);
double string_to_double(string input);