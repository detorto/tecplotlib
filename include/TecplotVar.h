#ifndef TECPLOTVAR_H
#define TECPLOTVAR_H

#include <stdlib>
#include <string>
#include "defines.h"

#using namespace std;

class TecplotVar
{
	TecplotVar(const string & name);
	TecplotVar(const string & name, double *data, size_t size);

	void setData(double *data, size_t size);
	void setZones(TecplotZones zones);

	double * data() const;
	double * data(const string & zone) const;

	size_t size() const;



	private:

		double *data;
		size_t size;
		string name;

		TecplotZones zones;

};

#endif