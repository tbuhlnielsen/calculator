#include <cmath>
#include <iostream>
#include <stdexcept>

#include "calculator.h"
#include "constants.h"

using namespace std;

Calculator::Calculator()
{
    sym_table.declare("pi", true, 3.14159265);
}

void Calculator::run()
{
    while (cin)
    {
        try
        {
            cout << prompt;

            Token t = ts.get();

            while (t.kind == print)
                t = ts.get();

            if (t.kind == quit)
                return;

            ts.putback(t);

            cout << result << statement() << '\n';
        }
        catch (const exception &e)
        {
            cout << e.what() << '\n';
            clean_up(ts);
        }
    }
}

double Calculator::statement()
{
    Token t = ts.get();

    switch (t.kind)
    {
        case var_decl: 
            return declaration(false);

        case const_decl:
            return declaration(true);

        case identifier:
        {
            Token t2 = ts.get();
            if (t2.kind == '=')
                return assignment(t.name);

            ts.putback(t2);
            ts.putback(t);
            return expression();
        }

        default:
            ts.putback(t);
            return expression();
    }
}

double Calculator::declaration(bool is_const)
{
    Token t = ts.get();
    if (t.kind != identifier)
        throw runtime_error("name expected in declaration");
    string name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
        throw runtime_error("missing '=' in declaration of " + name);

    double value = expression();

    sym_table.declare(name, is_const, value);

    return value;
}

double Calculator::assignment(string name)
{
    double value = expression();

    sym_table.set(name, value);

    return value;
}

double Calculator::expression()
{
    double left = term();

    Token t = ts.get();
    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;

        case '-':
            left -= term();
            t = ts.get();
            break;

        default:
            ts.putback(t);
            return left;
        }
    }
}

double Calculator::term()
{
    double left = primary();

    Token t = ts.get();
    while (true)
    {
        switch (t.kind)
        {
            case '*':
                left *= primary();
                t = ts.get();
                break;

            case '/':
            {
                double d = primary();
                if (d == 0)
                    throw runtime_error("division by 0");
                left /= d;
                t = ts.get();
                break;
            }

            case '%':
            {
                double d = primary();
                if (d == 0)
                    throw runtime_error("division by 0");
                left = fmod(left, d);
                t = ts.get();
                break;
            }

            default:
                ts.putback(t);
                return left;
        }
    }
}

double Calculator::primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
        case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')')
                throw runtime_error("expected ')'");
            return d;
        }

        case '-':
            return -primary();

        case '+':
            return primary();

        case numeric:
            return t.value;

        case identifier:
            return sym_table.get(t.name);

        default:
            throw runtime_error("primary expected");
    }
}