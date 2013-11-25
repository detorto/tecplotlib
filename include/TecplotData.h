#ifndef TECPLOTFILE_H
#define TECPLOTFILE_H

#include "TecplotVar.h"
#include "TecplotZone.h"
#include "defines.h"

#include <string>

using namespace std;

class TecplotData
{
public:

	TecplotData(string title);

	TecplotVars vars() const {return vars_; }
	TecplotZones zones() const {return zones_; }
	string title() {return title_; }

	void addVar(const TecplotVar & var);
	void assignVars(const TecplotVars & vars);

	void addZone(const TecplotZone & zone);
	void assignZones(const TecplotZones & zones);



private:
	TecplotVars vars_;
	TecplotZones zones_;
	string title_;
};

#endif