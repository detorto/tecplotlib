#ifndef TECPLOTPARCER_H
#define TECPLOTPARCER_H

#include "TecplotParser.h"

#include "defines.h"
#include <string>

using namespace std;

class TecplotFile
{
public:
	TecplotFile(const string &file_path);
	TecplotData data();

private:
	bool isBinaryFormat();
	string file_path_;
};

#endif