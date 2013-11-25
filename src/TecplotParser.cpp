#include "TecplotParser.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "Utils.h"
using namespace std;

TecplotAsciiParser::TecplotAsciiParser(const string &filename):filename_(filename),data_read(0)
{
	title = "Unknown data";
}

TecplotData TecplotAsciiParser::parse()
{
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

	int v_pos = 0;
	for (string v : var_names )
	{
		this->vars[v] = new TecplotVar(v) ;
		this->var_pos[v_pos] = v;

		DEBUG("Created variable " << v);
		v_pos++;
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
	int i=-1,j=-1,k=-1;
	int dim=0;

	if (params.find("T") != params.end())
		title = params["T"];

	if (params.find("F") != params.end())
		type = params["F"];

	if (params.find("I") != params.end())
	{
		i = stoi(params["I"]);
		dim++;
	}

	if (params.find("J") != params.end())
	{
		i = stoi(params["J"]);
		dim++;
	}

	if (params.find("K") != params.end())
	{
		i = stoi(params["K"]);
		dim++;
	}
	this->zones[title] = new TecplotZone(title, this->data_read, type, dim, i,  j,  k);
	DEBUG("Created zone [" << title << " "<< this->data_read << " " <<type << " " << dim << " " << i << " " << j << " " << k << "]");

	return true;
}

bool TecplotAsciiParser::getData(const string &line)
{

	strings vars;
	split(line,vars);
	if(vars.size() != this->var_pos.size())
	{
		DEBUG("Line is not datatype");
		return true;
	}
	for (int i =0; i< vars.size(); i++)
		this->vars[var_pos[i]]->data()->push_back(stod(vars[i]));

	this->data_read++;
	DEBUG(data_read<<": Readed data "<< line);
	return true;
}



