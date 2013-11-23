#ifndef TECPLOTZONE_H
#define TECPLOTZONE_H

#include "TecplotVar.h"
#include "defines.h"

#include <string>

using namespace std;

class TecplotZone
{
	TecplotZone(string name, size_t start_index, string type, size_t dim, size_t i, size_t j, size_t k);

private:
	string name;
	string type;
	size_t start_index;

	size_t dim;
	size_t i;
	size_t j;
	size_t k;

	size_t end_index;

	TecplotVars vars;
};
#endif