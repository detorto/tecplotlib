#ifndef TECPLOTFILE_H
#define TECPLOTFILE_H

#include "TecplotVar.h"
#include "TecplotZone.h"
#include "defines.h"

#include <string>

using namespace std;

class TecplotData
{
	TecplotData(string title);

	TecplotVars vars() const;
	TecplotZones zones() const;

	void addVar(const TecplotVar & var);
	void addZone(const TecplotZones & zone);

private:
	TecplotVars vars;
	TecplotZones zones;
};

#endif