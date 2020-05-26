/*
    tokens.h -- classes responsible for reading input

    Input comes from cin and is handled by a Token_stream, which
    composes Tokens ("elements" of input) from characters. 

    The Token_stream also provides a buffer to putback() Tokens which 
    have been found while "looking ahead". 
    
    To see the utility of the buffer, suppose a variable `x` has 
    been defined and is read as the first Token of a new expression.
    There are two possibilities: either the user wants to use the current 
    value of `x` (e.g. if the input were `x + 2;`) or they want to 
    update the value of `x` (e.g. if the input were `x = 2;`). 
    The calculator has to handle one of these choices, but it cannot know 
    which one until the next Token is read. So it reads the next Token and 
    either uses it or puts it in the buffer for "someone else" to use.
*/

#ifndef TKSTREAM_H
#define TKSTREAM_H

#include <string>
#include <vector>

// A print or quit command, a bracket, an operator, a number, 
// or an identifier.
struct Token
{
    char kind;
    double value;      // for numbers
    std::string name;  // for identifiers

    // Initialises print, quit, bracket, and operator Tokens.
    Token(char type)
        :kind{type}, value{0} { }

    // Initialises a number Token with value x.
    Token(char type, double x)
        :kind{type}, value{x} { }

    // Initialises an identifier Token with name s.
    Token(char type, std::string s)
        :kind{type}, name{s} { }
};

class Token_stream
{
    public:
        Token_stream() { }

        // Reads characters from cin and composes a Token.
        Token get();

        // Puts t at the back of the buffer.
        void putback(Token t);

        // Reads Tokens from the buffer, and then characters
        // from cin, until c (or a Token of kind c) is read.
        void ignore_until(char c);

    private:
        std::vector<Token> buffer;
};

// Called when there is an error in the calculator's main loop.
void clean_up(Token_stream& ts);

#endif