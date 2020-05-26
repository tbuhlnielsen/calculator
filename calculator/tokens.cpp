#include <iostream>

#include "constants.h"
#include "tokens.h"

using namespace std;

// ---------------------------------------------------------

Token Token_stream::get()
{
    // use a Token from the buffer if there is one
    if (!buffer.empty())
    {
        Token t = buffer.back();
        buffer.pop_back();
        return t;
    }

    char ch;
    cin >> ch;
    switch (ch)
    {
        case print:
        case quit:
        case '(': case ')':
        case '+': case '-': case '*': case '/':
        case '%':
        case '=':
            return Token{ch};

        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            double x;
            cin >> x;
            return Token{numeric, x};
        }

        default:
            if (isalpha(ch))
            {
                string s;
                s += ch;
                while (cin.get(ch) && (isalnum(ch) || ch == '_')) // use get() not to skip whitespace
                    s += ch;
                cin.putback(ch);

                if (s == var_kw)
                    return Token{var_decl};
                if (s == const_kw)
                    return Token{const_decl};

                return Token{identifier, s};
            }
            throw runtime_error("bad token");
    }
}

void Token_stream::putback(Token t)
{
    buffer.push_back(t);
}

void Token_stream::ignore_until(char c)
{
    while (!buffer.empty())
    {
        if (buffer.back().kind == c)
        {
            buffer.pop_back();
            return;
        }
        buffer.pop_back();
    }

    char ch;
    while (cin >> ch)
        if (ch == c) return;
}

void clean_up(Token_stream& ts)
{
    ts.ignore_until(print);
}