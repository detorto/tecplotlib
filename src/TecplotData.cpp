#include "TecplotData.h"

TecplotData::TecplotData(string title):title_(title)
{

}

void TecplotData::addVar(const TecplotVar & var)
{

}

TecplotVars TecplotData::vars() const
{
	return vars_;
}

TecplotZones TecplotData::zones() const
{
	return zones_;
}

TecplotZone *TecplotData::zone(string x)
{
	return 0;
}

strings TecplotData::zone_names()
{
	strings ret;

	for (auto v: this->zones_)
	{
		ret.push_back(v->name());
	}
	return ret;
}

size_t TecplotData::zone_count()
{
	return zones_.size();
}

string TecplotData::title()
{
	return title_;
}

void TecplotData::assignVars(const TecplotVars & vars)
{
	this->vars_ = vars;
}


void TecplotData::addZone(const TecplotZone & zone)
{

}

void TecplotData::assignZones(const TecplotZones & zones)
{
	this->zones_ = zones;
}

TecplotVar *TecplotData::var(string x)
{
	for (auto var : vars_)
		if (var->name() == x)
			return var;
	return 0;
}

strings TecplotData::var_names()
{
	strings ret;

	for (auto v: this->vars_)
	{
		ret.push_back(v->name());
	}
	return ret;
}


size_t TecplotData::var_count()
{
	return this->vars_.size();
}

size_t TecplotData::var_size(string name)
{
	return 0;
	//return this->vars_[name]->size();
}
