#include "arithmetic.h"// ���������� ������� � ������� ��� ���������� �������������� ���������

std::map<string, std::function<double(double)>> function = {
    {"~", [](double a) {return (-1 * a); }},
    {"sin", [](double a) {return sin(a); }},
    {"cos", [](double a) {return cos(a); }},
    {"sqrt",[](double a) {return sqrt(a); }},
    {"log", [](double a) {return log(a); }},
    {"lg", [](double a) {return log10(a); }},
    {"ln", [](double a) {return log(a); }},
};
std::map<string, std::function<double(double, double)>> inf_op = {
    {"+",[](double a,double b) {return a + b; }},
    {"-",[](double a,double b) {return a - b; }},
    {"*",[](double a,double b) {return a * b; }},
    {"/",[](double a,double b) {return a / b; }},
    {"^",[](double a,double b) {return pow(a,b); }}
};

std::map <string, double> variables;

/*������� ������������ �������� ��������.���� ������� ���������������� ������ (1),
* �� �������� �������� ������ �� ����� �����. ���� �� ���� ������� �����, �� 
* ������������� �������� ��������������� ����������(2). ���� ����� ���, �
* �������� ������������� � ������������(3)
*/
void TPostfix::operands::Set(string input)
{
    if (isdigit(input.at(0)) || input.at(0) == '.')        /*1*/
    {
        value = string_to_double(input);
    }
    if (isalpha(input.at(0))) {
        if (variables.count(input) != 0)                   /*2*/
        {
            value = variables.find(input)->second;
        }
        else                                               /*3*/
        {
            string var_value;
            std::cout << "Enter value of " << input << std::endl;
            getline(std::cin, var_value);
            value = string_to_double(var_value);
            variables.emplace(input, value);
        }
    }
}

/*������� ������������ ���������� ��������. ��������� ������ ������ ����� �
* ������� � ��������� ��������. ��� ��������������� �������� ��������� � � 
* ����� �������. �������� � ����� ������� ��� ���������� ���������� �������
* �� �����
*/
void TPostfix::operators::Set(const string input)
{
    switch (input.at(0))
    {
    case '(':
        priority = brack;
        break;
    case ')':
        priority = brack;
        break;
    case '*':
        priority = mult_div;
        break;
    case '/':
        priority = mult_div;
        break;
    case '^':
        priority = power;
        break;
    case '+':
        priority = add_sub;
        break;
    case '-':
        priority = add_sub;
        break;
    default:
        if (function.count(input) == 1) { priority = foo; } /*1*/
        else { throw MyException("undefined operation on:",left,right); }
        break;
    }
}

double string_to_double( const string s)
{
    const char* input = s.c_str() ;
    double a = 0.0;
    int e = 0;
    size_t c = 0;
    for (; isdigit(*input) && *input != '\0';*(input++)) 
    {
        c = static_cast<size_t>(*input - '0'); //shift *input to number
        a = 10 * a + c;
    }
    if (*input == '.')
    {
        *(input++);
        for (; isdigit(*input) && *input != '\0'; *(input++))
        {
            c = static_cast<size_t>(*input - '0');
            a = 10 * a + c;
            e--;
        }
    }
    if (*input == 'e' || *input == 'E')
    {
        *(input++);
        int sign = 1;
        size_t i = 0;
        if (*input == '+') *(input++);
        if (*input == '-') { *(input++); sign = -1; }
        for (; isdigit(*input) && *input != '\0'; *(input++))
        {
            size_t c = static_cast<size_t>(*input - '0');
            i = i * 10 + c;
        }
        e += sign * i;
    }
    for (; e > 0; e--)
    {
        a = 10 * a;
    }
    for (; e < 0; e++)
    {
        a = 0.1 * a;
    }
    if (*input != '\0') throw std::invalid_argument("extra sign at" + s);
    return a;
}

/*����������� ����������� �����. �� ���� ������� ������ ��������� � ���������
* �����. ����� - ������ ���� TPostfix � �������� ������, ��������������
* ��������� � ����������� �����
* 
* ��������� ����, � ������� ��� ��������� ������������, ���� �� ������ ��
* ����� ������. ��������� head ��������� �� ������ ������� �������, cur - �� 
* ������, ����������� � ������ ������.
*
* (1) ���� ������� ������ ����� ��� �����, ������ �� ����� ����� � ���������� �
* ������ �������(2).���� ������� �������, ����� � � ����.� ��������� ������ 
* ����� � ����� ����� ��� ����������.
*
* (3) ���� ������� ������ - ��������� �������� ����� ������, ����������� ��
* ����� � ����� ��� �������� � ������� ��� ����� �������� ������������ �
* �������� � � ����.
*
* (4) ���� ������� ������ - �����, ��������� �������. ������� ����� �����
* � ����, ��� ��������� ��������� �������� ��������� ����������.
* 
* (5) ����������� ������ ����� � ����.
* 
* (6) ���� ������� ������ - ����������� ������, ����������� � ����� ��� ��������
* �� ����������� ������. ���� ���� ������� ������, �� ������������� ������������
* ������
* 
* ����� ��� ������� ���������, ����������� ��� ��������� �� ����� � �����(7).
* ���� ������� ����������� ������, ������ ������������� �����������.
*/
TPostfix::TPostfix(const string input)
{ 
    const size_t len = input.length();
    Tstack<operators*> op; //���� ��� ��� �� �������� � �������� ������ ���������� 
    for (size_t head = 0, cur = 0; cur < len ; head = cur)
    {
        char tmp = input.at(head);
        if (isdigit(tmp) || tmp == '.' || isalpha(tmp))              /*1*/
        {
            do {
                tmp = input.at(cur);
                cur++;
                if (tmp == 'e' || tmp == 'E') cur++;
            } while (cur < len && (isdigit(tmp) || isalpha(tmp) || tmp == '.'));
            if (!(isdigit(tmp) || isalpha(tmp) || tmp == '.')) { cur--; };
            string other(input, head, cur - head);

            if (function.count(other) == 1)                          /*2*/
            {
                op.push(new operators(other, head, cur));
                continue;
            }

            out.push_back(new operands(other, head, cur ));
            continue;
        }

        if (   tmp == '+'                                            /*3*/
            || tmp == '*'
            || tmp == '/'
            || tmp == '^'
            )
         {
            cur++;
            string other(input, head, cur - head);
            operators op_tmp(other, head, cur);
            while (!op.isEmpty() &&op.peek()->priority <= op_tmp.priority)
            {
                out.push_back(op.pop());
            }
            op.push(new operators(other, head, cur));
            continue;
         }

        if (tmp == '-'){                                             /*4*/
            cur++;
            if(head == 0  || (head != 0 && (input.at(head - 1) == '('
                                        || input.at(head - 1) == '+'
                                        || input.at(head - 1) == '-'
                                        || input.at(head - 1) == '*'
                                        || input.at(head - 1) == '/'
                                        || input.at(head - 1) == '^'
            )))
            {
                string other("~", 1);
                operators op_tmp(other, head, cur);
                while (!op.isEmpty() && op.peek()->priority <= op_tmp.priority)
                {
                    out.push_back(op.pop());
                }
                op.push(new operators(other, head, cur));
                continue;
            }
            else {
                string other(input, head, cur - head);
                operators op_tmp(other, head, cur);
                while (!op.isEmpty() && op.peek()->priority <= op_tmp.priority)
                {
                    out.push_back(op.pop());
                }
                op.push(new operators(other, head, cur));
                continue;
            }
        }

        if (tmp == '(')                                              /*5*/
        {
            cur++;
            string other(input, head, cur - head);
            op.push(new operators(other, head, cur));
            continue;
        }  

        if (tmp == ')')                                              /*6*/
        {
            cur++;
            while (!op.isEmpty() && op.peek()->priority != brack)
            {
                out.push_back(op.pop());
            }
            if (op.isEmpty()) throw MyException("expected open bracket at:",op.peek()->left, op.peek()->right);
            op.pop();
            if (!op.isEmpty() && op.peek()->priority == foo)
            {
                out.push_back(op.pop());
            }
            continue;
        }
        throw MyException("undefined operation", head, cur);
    }

    while (!op.isEmpty())                                            /*7*/
    {
        if (op.peek()->priority == brack) throw MyException("expected close bracket", op.peek()->left, op.peek()->right);
        out.push_back(op.pop());
    }
}

/*����� ���������� ��������� �� ����������� ������
* 
* �� ���� ������� ������ ���� TPostfix, ��� ������ ������ - ��������� � 
* ����������� �����. �� ������ - �������� ��������� ������� double.
* 
* ���� �� ���������� ��� ������� ��������� ������ ����������.
* 
* (4)���� ���� ����, �� �� ���� ��������� ������ ��������� 
* 
* (1) ���� ������� - �������, ����� � � ����.
* 
* (2,3) ���� ������� - ��������� �������� ��� �������, ������ �� ����� ������ 
* ���������� ��������� � ��������� ��� ���� ��������� ��������.
*
* ����� ���������� ��� �������, ������������ ��������� � ����� ������� 
* ��������� ���������. (5) ���� ����� ����� ���� �� ����, ������ ��� �������� 
* �������� ��� ������ ��� ���������� ���������.
*/
double solve(const TPostfix& obj)
{
    Tstack <TPostfix::operands*> op_st; // ���� �������������� ���������
    for (auto& lex : obj.out)
    {
        if (variables.count(lex->data) != 0                          /*1*/
         || isdigit(lex->data.at(0)) 
         || lex->data.at(0) == '_')
        {
            op_st.push(dynamic_cast<TPostfix::operands*>(lex));
            continue;
        }

        if (inf_op.count(lex->data) != 0)                            /*2*/
        {
            if (op_st.isEmpty()) {
                string exception = "Missing right operands in operation:" + lex->data + " on positnion:";
                throw MyException(exception.c_str(), lex->left, lex->right);
            }
            TPostfix::operands* right = (TPostfix::operands*)(op_st.pop());
            if (op_st.isEmpty()) {
                string exception = "Missing left operand in operation:" + lex->data + " on positnion:";
                throw MyException(exception.c_str(), lex->left, right->right);
            }
            TPostfix::operands* left = (TPostfix::operands*)(op_st.pop());
            op_st.push(new TPostfix::operands(inf_op[lex->data](left->value, right->value), left->left, right->right));
            continue;
        }

        if (function.count(lex->data) != 0)                          /*3*/
        {
            if (op_st.isEmpty()) {
                string exception = "Missing operand in function:" + lex->data + " on positnion:";
                throw MyException(exception.c_str(), lex->left, lex->right);
            }
            TPostfix::operands* op = (TPostfix::operands*)(op_st.pop());
            op_st.push(new TPostfix::operands(function[lex->data](op->value), lex->left, op->right));
            continue;
        }
    }
    if (op_st.isEmpty())                                             /*4*/
    {
        throw std::invalid_argument("Expression not entered");
    }
    
    const double res = op_st.pop()->value;
    
    if (!op_st.isEmpty())                                            /*5*/
    {
        size_t min = 0, max = INT_MAX;
        while (!op_st.isEmpty())
        {
            TPostfix::Lexem* tmp = op_st.pop();
            min = std::max(min, tmp->left);
            max = std::min(max, tmp->right);
        }
        throw MyException("Missing operator after:", min, max);
    }
    return res;
}

//����� � ����� ���������� ���������� ��������� � ����������� �����
std::ostream& operator<<(std::ostream& os, const TPostfix& obj)
{
    os << solve(obj);;
    return os;
}