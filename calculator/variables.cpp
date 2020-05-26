#include <stdexcept>

#include "variables.h"

using namespace std;

double Symbol_table::get(string name)
{
    for (const Variable& var : var_table)
        if (var.name == name) return var.value;

    throw runtime_error("undeclared variable: " + name);
}

void Symbol_table::set(string name, double value)
{
    for (Variable& var : var_table)
    {
        if (var.name == name)
        {
            if (var.is_const)
                throw runtime_error("cannot set() const: " + name);

            var.value = value;
            return;
        }
    }

    throw runtime_error("undeclared variable: " + name);
}

bool Symbol_table::is_declared(string name)
{
    for (const Variable& var : var_table)
        if (var.name == name) return true;

    return false;
}

double Symbol_table::declare(string name, bool is_const, double value)
{
    if (is_declared(name))
        throw runtime_error("variable declared twice: " + name);

    var_table.push_back(Variable{name, is_const, value});

    return value;
}