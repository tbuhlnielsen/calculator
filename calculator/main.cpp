/*
    This program implements a calculator which can evaluate 
    arithmetic expressions typed by the user. 
    
    In addition to the four standard operations (addition, subtraction, 
    multiplication, and division), also available is the ability to 
    define variables and constants with the key words "var" and "let", 
    respectively.
*/

#include <iostream>
#include <stdexcept>

#include "calculator.h"

using namespace std;

// ---------------------------------------------------------

int main()
{
    try
    {
        Calculator calc;
        calc.run();
        
        return 0;
    }
    catch (const exception& e)
    {
        cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "unknown error!\n";
        return 2;
    }
}