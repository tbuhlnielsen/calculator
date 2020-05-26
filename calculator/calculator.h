/*
    calculator.h -- responsible for main program functionality.

    The grammar for parsing input is shown below

        Calculation:
            Print
            Quit
            Statement
            Calculation Statement

        Statement:
            Declaration
            Assignment
            Expression

        Declaration:
            "var" Name '=' Expression
            "let" Name '=' Expression

        Assignment:
            Name '=' Expression

        Name:
            Sequence of digits/letters/underscores, starting with a letter

        Expression:
            Term
            Expression '+' Term
            Expression '-' Term

        Term:
            Primary
            Term '*' Primary
            Term '/' Primary
            Term '%' Primary

        Primary:
            Number
            '-' Primary
            '+' Primary

        Number:
            Floating-point literal

    Note: the rule for Primary allows for repeated unary minus and plus.
    For example, `--2;` will evaluate to 2, and `+++3;` will evaluate to 3.
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "tokens.h"
#include "variables.h"

class Calculator
{
    public:
        Calculator();

        // The main loop: get input, evaluate, output results
        void run();

        // Handles declarations and assignments or calls expression()
        double statement();

        double declaration(bool is_const);
        double assignment(std::string name);

        // Handles '+' and '-'
        double expression();

        // Handles '*' and '/'
        double term();

        // Handles numbers and parentheses
        double primary();

    private:
        Token_stream ts;
        Symbol_table sym_table;
};

#endif