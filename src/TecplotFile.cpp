#include "TecplotFile.h"
#include "TecplotParser.h"
#include  <fstream>

using namespace std;

//====================================================================
TecplotFile::TecplotFile(const string &file_path) : file_path_(file_path), data_("Bad data")
{
}
//====================================================================
bool TecplotFile::open()
{
	if (isBinaryFormat())
	{
		ERROR("Binary format not supported yet");
	}
	else
	{
		parser_ = new TecplotAsciiParser(this->file_path_);
	}

	data_ = parser_->parse();
	delete parser_;
	parser_ = NULL;
	return true;
}

//====================================================================
TecplotData TecplotFile::data()
{
	return data_;
}

//====================================================================
int TecplotFile::openingPersent()
{
	static int i = 0;
	if (parser_)
		return parser_->parsingPercent();
	else
		return 100;
}

//====================================================================
bool TecplotFile::isBinaryFormat()
{
	#warning No file format detection yet!
	return false;
}