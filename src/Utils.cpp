#include "Utils.h"
#include <sstream>
// trim string from start
std::string &ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim string from end
std::string &rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim string from both ends
std::string &trim(std::string &s)
{
	return ltrim(rtrim(s));
}

std::vector<std::string> &split(const std::string &s, std::vector<std::string> &elems, char delim)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

params &get_params(std::string line, params &p, bool only_one_param)
{
	int pos;
	std::string p_name;
	std::string p_value;

	bool in_string = false;
	bool eq_found = false;

	bool need_to_appemd_comma = false;

	for (char c: line)
	{
		if (!in_string && ( c == ' ' || c == '\t' ))
		{
			continue;
		}

		if (c == '\"' )
		{
			in_string = !in_string;
			continue;
		}

		if (c == ',')
		{
			if(!only_one_param )
			{
					eq_found = false;
					p[p_name] = p_value;
					p_name.clear();
					p_value.clear();
			}
			else
			{
				p_value.push_back(',');
			}
			continue;
		}

		if (c == '=' )
		{
			eq_found = true;
			continue;
		}

		if(!eq_found)
		{
			p_name.push_back(c);
		}
		else
		if (eq_found)
		{
			p_value.push_back(c);
		}
	}

	if (eq_found)
	{
		p[p_name] = p_value;
	}

	return p;
}