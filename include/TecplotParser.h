#ifndef TECPLOTPARSER_H
#define TECPLOTPARSER_H

#include "TecplotVar.h"
#include "TecplotZone.h"
#include "TecplotData.h"
#include "defines.h"

#include <string>

using namespace std;

class TecplotAsciiParser
{
	TecplotAsciiParser(string file);
	TecplotData parse();

private:
	string file;
};

#endif