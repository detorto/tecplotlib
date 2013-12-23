#include "TecplotParser.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "Utils.h"
#include "gzstream.h"

using namespace std;

TecplotAsciiParser::TecplotAsciiParser(const string &filename):filename_(filename),data_read(0),parsing_percent_(0)
{
	title = "Unknown data";
}

int TecplotAsciiParser::parsingPercent()
{
	return parsing_percent_;
}

bool TecplotAsciiParser::isFileGziped()
{
	ifstream inFile;
	ifstream::pos_type size;

	inFile.open( filename_, ios::in|ios::binary|ios::ate );
	char data[2];
	inFile.seekg(0, ios::beg);

	inFile.read( data, 2 );
	inFile.close();

	DEBUG("GZIPPED: "<<hex<<(unsigned char)data[0] <<hex<<(unsigned int)data[1] );
	if (data[0] == 0x1f && (unsigned int) data[1] ==  0xffffff8b )
	{
		return true;
	}
	return false;
}

TecplotData TecplotAsciiParser::parse()
{
	if (isFileGziped())
		return parseGZIP();
	else
		return parseASCII();
}

TecplotData TecplotAsciiParser::parseGZIP()
{
	igzstream file;

	igzstream files(filename_.c_str());
	streampos fsize = 0;
	fsize = files.tellg();
	files.seekg( 0, std::ios::end );
	fsize = files.tellg() - fsize;
	files.close();


	file.open (filename_.c_str());
	int line_index = 0;
	while (!file.eof())
	{
		parsing_percent_ = (file.tellg()/(fsize/100.0));
		DEBUG("\nFile size: "<<fsize);
		DEBUG("\nTellg: "<<file.tellg());
		DEBUG("Percens: "<<parsing_percent_);

		DEBUG("Reading " << line_index);

		string line;
		getline(file, line);

		if (line.size() == 0)
		{
			DEBUG("Line is empty, skipping");
			continue;
		}

		trim(line);

		if (line[0] == '#') // commants are allowed (additional info in them)
		{
			if ( processComment(line) )
			{
				DEBUG("Comment found in line: "<<line_index);
			}
		}
		else
		{

			if ( !processTecplot(line) )
			{
				ERROR("Error in line: " << line_index);
			}
		}
		line_index++;
	}


	//do assambling tecplot data
	TecplotData td = TecplotData(this->title);
	td.assignVars(this->vars);
	td.assignZones(this->zones);

	return td;
}

TecplotData TecplotAsciiParser::parseASCII()
{
	//file size getting
	ifstream files(filename_.c_str());
	streampos fsize = 0;
	fsize = files.tellg();
	files.seekg( 0, std::ios::end );
	fsize = files.tellg() - fsize;
	files.close();

	ifstream file(filename_.c_str());

	if ( !file.is_open() )
	{
		ERROR("File not opened!\n");
		return TecplotData("Bad data");
	}
	int line_index = 0;

	DEBUG("Starting reading...");
	while (!file.eof())
	{
		parsing_percent_ = (file.tellg()/(fsize/100.0));
		DEBUG("Reading " << line_index);

		string line;
		getline(file, line);

		if (line.size() == 0)
		{
			DEBUG("Line is empty, skipping");
			continue;
		}

		trim(line);

		if (line[0] == '#') // commants are allowed (additional info in them)
		{
			if ( processComment(line) )
			{
				DEBUG("Comment found in line: "<<line_index);
			}
		}
		else
		{

			if ( !processTecplot(line) )
			{
				ERROR("Error in line: " << line_index);
			}
		}
		line_index++;
	}

	//do assambling tecplot data
	TecplotData td = TecplotData(this->title);
	td.assignVars(this->vars);
	td.assignZones(this->zones);

	return td;
}

bool TecplotAsciiParser::processComment(const string &comment)
{
	return true;
}

bool TecplotAsciiParser::processTecplot(const string &line)
{
	if ( !getTitle(line) && !getVars(line) && !getZone(line) && !getData(line))
		return false;
	return true;
}


bool TecplotAsciiParser::getTitle(const string &line)
{
	params p;
	get_params(line, p);

	if (p.find("TITLE") != p.end())
	{
		this->title = p["TITLE"];
		DEBUG("Title is "<<this->title);
		return true;
	}
	else
	{
		return false;
	}
}

bool TecplotAsciiParser::getVars(const string &line)
{
	params p;
	get_params(line, p, true);
	if (p.find("VARIABLES") == p.end())
		return false;

	string right = p["VARIABLES"];
	DEBUG("Var found: "<<right);
	strings var_names;
	split(right, var_names, ',');

	if(var_names.size() == 0)
		ERROR("No varibles found!");

	for (int i =0; i < var_names.size(); i++ )
	{
		this->vars.push_back( new TecplotVar(var_names[i])) ;
		DEBUG("Created variable " << var_names[i]);
	}

	return true;
}

bool TecplotAsciiParser::getZone(const string &line)
{
	strings splits;

	split(line, splits);
	if (splits[0] != "ZONE")
		return false;

	map <string,string> params;
	get_params(line.substr(5,line.size()), params);

	string type = "POINT";
	string title = std::to_string(this->zones.size());
	int i=0,j=0,k=0;

	if (params.find("T") != params.end())
		title = params["T"];

	if (params.find("F") != params.end())
		type = params["F"];

	if (params.find("I") != params.end())
	{
		i = stoi(params["I"]);
	}

	if (params.find("J") != params.end())
	{
		j = stoi(params["J"]);
	}

	if (params.find("K") != params.end())
	{
		k = stoi(params["K"]);
	}
	this->zones.push_back( new TecplotZone(title, this->data_read, type, i,  j,  k));
	DEBUG("Created zone [" << title << " "<< this->data_read << " " << type  << " " << i << " " << j << " " << k << "]");

	return true;
}

bool TecplotAsciiParser::getData(const string &line)
{

	strings lvars;
	DEBUG("Line is " << line);
	split(line, lvars);
	if(lvars.size() != this->vars.size())
	{
		DEBUG("Var size: " << lvars.size() << " vars: " << vars.size());
		DEBUG("Line is not datatype");
		return true;
	}
	for (int i =0; i< lvars.size(); i++)
	{
		double v =my_stod(lvars[i]);
		this->vars[i]->data()->push_back(v);
	}

	this->data_read++;
	DEBUG(data_read<<": Readed data "<< line);
	return true;
}



