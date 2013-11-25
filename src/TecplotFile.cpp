#include "TecplotFile.h"
#include "TecplotParser.h"
#include  <fstream>

using namespace std;

//====================================================================
TecplotFile::TecplotFile(const string &file_path) : file_path_(file_path)
{
}

//====================================================================
TecplotData TecplotFile::data()
{
	TecplotParser *parser;
	if (isBinaryFormat())
	{
		ERROR("Binary format not supported yet");
	}
	else
	{
		parser = new TecplotAsciiParser(this->file_path_);
	}

	TecplotData data = parser->parse();
	delete parser;

	return data;
}

//====================================================================
bool TecplotFile::isBinaryFormat()
{
	#warning No file format detection yet!
	return false;
}