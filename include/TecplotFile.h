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
	~TecplotFile() {DEBUG("Destroing file "<<file_path_);}
	TecplotData data();
	bool open();
	int openingPersent();

private:
	bool isBinaryFormat();
	string file_path_;
	TecplotParser *parser_;
	TecplotData data_;

};

#endif