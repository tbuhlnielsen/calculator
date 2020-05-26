#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Token::kind
const char numeric = '8';
const char var_decl = 'v';
const char const_decl = 'c';
const char identifier = 'a';
const char print = ';';
const char quit = 'q';

// Key words
const std::string var_kw = "var";
const std::string const_kw = "let";

// UI
const std::string prompt = "> ";
const std::string result = "= ";

#endif