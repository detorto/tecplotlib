#ifndef TECPLOTUTILS_H
#define TECPLOTUTILS_H

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <vector>
#include "defines.h"

// trim from start
std::string &ltrim(std::string &s);

// trim from end
std::string &rtrim(std::string &s);

// trim from both ends
std::string &trim(std::string &s);

strings &split(const std::string &s, strings &elems,  char delim = ' ');

params &get_params(std::string line, params &p, bool only_one_param = false);
double my_stod(const std::string &valueAsString);
#endif