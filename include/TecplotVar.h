#ifndef TECPLOTVAR_H
#define TECPLOTVAR_H

#include <stdlib.h>
#include <string>
#include "defines.h"

using namespace std;
#include <vector>
class TecplotVar
{
public:
	TecplotVar(const string & name);
	TecplotVar(const string & name, double *data, size_t size);

	void setData(double *data, size_t size);
	void setZones(TecplotZones zones);

	double * data_raw() const;
	//double * data(const string & zone) const;
	//double * data(const TecplotZone & zone) const;

	std::vector<double> * data() ;
	size_t size() const;
	size_t size(const string & zone) const;
	size_t size(const TecplotZone & zone) const;

	private:

		std::vector <double> data_;
		size_t size_;
		string name_;

		TecplotZones zones_;

};

#endif