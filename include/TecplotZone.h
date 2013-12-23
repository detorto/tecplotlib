#ifndef TECPLOTZONE_H
#define TECPLOTZONE_H

#include "defines.h"

#include <string>

using namespace std;

class TecplotZone
{
public:
	TecplotZone(string name, size_t start_index, string type, size_t i, size_t j=0, size_t k=0);
	~TecplotZone()
	{
		DEBUG("Destroing Zone "<<name_);
	}

	string name();
	size_t dim();
	size_t i();
	size_t j();
	size_t k();
	size_t start();
	size_t end();
	size_t length();
private:
	string name_;
	string type_;
	size_t start_index_;
	size_t end_index_;

	size_t dim_;
	size_t i_;
	size_t j_;
	size_t k_;
};
#endif