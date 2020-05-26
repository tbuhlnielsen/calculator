/*
    variables.h -- classes for giving the user the ability 
                   to define and use variables.
*/

#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include <vector>

struct Variable
{
    std::string name;
    bool is_const;
    double value;
};

class Symbol_table
{
    public:
        Symbol_table() { }

        // Returns the value of a variable/constant called name
        // if there is one, else throws an error.
        double get(std::string name);

        // Sets the value of a variable called name to value
        // if there is one, else throws an error.
        void set(std::string name, double value);

        // True if a variable called name has been declared.
        bool is_declared(std::string name);

        // Declare a variable called name with value.
        double declare(std::string name, bool is_const, double value);

    private:
        std::vector<Variable> var_table;
};

#endif