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
	~TecplotData()
	{DEBUG("Destroing data "<<title_);}

	TecplotVars vars() const ;
	TecplotVar *var(string x);

	strings var_names();
	size_t var_count();

	size_t var_size(string name);

	TecplotZones zones() const;
	TecplotZone *zone(string x);

	strings zone_names();
	size_t zone_count();

	string title() ;

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