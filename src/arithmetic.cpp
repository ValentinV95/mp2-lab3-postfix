#include "..\include\arithmetic.h"// реализация функций и классов для вычисления арифметических выражений
void operands::Set(string input)
{
    if (isdigit(input.at(0)) || input.at(0) == '.')
    {
        value = string_to_double(input);
    }
    if (isalpha(input.at(0)) && variables.count(input) == 0)
    {
        string var_value;
        std::cout << "Введите значение переменной " << input << std::endl;
        getline(std::cin, var_value);
        value = string_to_double(var_value);
        variables.emplace(input, value);
    }
}

void operators::Set(const string input)
{
    switch (input.at(0))
    {
    case '(':
        priority = brack;
        break;
    case ')':
        priority = brack;
        break;
    case '~':
        priority = foo;
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
        if (input.length() > 1 && function.count(input) == 1) { priority = foo; }
        else { throw std::invalid_argument("undefined operation"); }
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
    if (*input != '\0') throw std::invalid_argument("extra sign");
    return a;
}

operands* make_inf_op(operands* l, operators* op, operands* r)
{
    switch (op->data.at(0))
    {
    case '+':
        return  &operands(l->value + r->value, l->left, r->right);
        break;
    case '-':
        return  &operands(l->value - r->value, l->left, r->right);
        break;
    case '*':
        return &operands(l->value * r->value, l->left, r->right);
        break;
    case '/':
        return &operands(l->value / r->value, l->left, r->right);
        break;
    case '^':
        return &operands(pow(l->value,r->value), l->left, r->right);
        break;
    default:
        throw std::invalid_argument("weird");
        break;
    }
}


void TPostfix::check_input()
{
}


TPostfix::TPostfix(const string input)
{ 
    const size_t len = input.length();
    Tstack<operators*> op;
    for (size_t head = 0, cur = 0; cur < len ; head = cur)
    {
        char tmp = input.at(head);
        if (isdigit(tmp) || tmp == '.' || isalpha(tmp))
        {
            do {
                tmp = input.at(cur);
                cur++;
            } while (cur < len && (isdigit(tmp) || tmp == '.' || tmp == 'e' || tmp == 'E'));
            if (cur < len) { cur--; };
            string other(input, head, cur - head);
            if (function.count(other) == 1)
            {
                op.push(new operators(other, head, cur));
                continue;
            }

            out.push_back(new operands(string_to_double(other), head, cur ));
            continue;
        }
        if (   tmp == '+'
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
            op.push(/*&op_tmp);/*/new operators(other, head, cur));
            continue;
         }
        if (cur == 0 && tmp == '-'||
            cur != 0 && (input.at(cur - 1) == '('
                     || input.at(cur - 1) == '+'
                     || input.at(cur - 1) == '-'
                     || input.at(cur - 1) == '*'
                     || input.at(cur - 1) == '/'
                     || input.at(cur - 1) == '^'
            ))
        {
            string other('~', 1);
            operators op_tmp(other, head, cur);
            while (!op.isEmpty() && op.peek()->priority <= op_tmp.priority)
            {
                out.push_back(op.pop());
            }
            op.push(new operators(other, head, cur));
            continue;
        }
        if (tmp == '(')
        {
            string other(input, head, cur - head + 1);
            op.push(new operators(other, head, cur));
            continue;
    }   
        if (tmp == ')')
        {
            while (!op.isEmpty() && op.peek()->priority != brack)
            {
                out.push_back(op.pop());
            }
            if (!op.isEmpty()) throw std::invalid_argument("expected open bracket");
            op.pop();
            if (!op.isEmpty() && op.peek()->priority == foo)
            {
                out.push_back(op.pop());
            }
        }
    }
    while (!op.isEmpty())
    {
        if (op.peek()->priority == brack) throw std::invalid_argument("expected close bracket");
        out.push_back(op.pop());
    }
}

std::ostream& operator<<(std::ostream& os, const TPostfix obj)
{
    string inf_op = { '+','-','*','/','^' };
    Tstack <operands*> op_st;
    for (auto& lex : obj.out)
    {
        if (lex->data=="_")
        {
            op_st.push(dynamic_cast<operands*>(lex));
        }
        if (inf_op.find(lex->data) != string::npos)
        {
            operators* op = dynamic_cast<operators*>(lex);
            op_st.push(make_inf_op(dynamic_cast<operands*>(op_st.pop()),op,dynamic_cast<operands*>(op_st.pop())));
        }
        if (function.count(lex->data) != 0)
        {
            operands* op = dynamic_cast<operands*>(op_st.pop());
            op_st.push(new operands(function[lex->data](op->value),lex->left,op->right));
        }
    }
    os << op_st.pop()->value;
    return os;
}