#include "TecplotData.h"

TecplotData::TecplotData(string title):title_(title)
{

}

void TecplotData::addVar(const TecplotVar & var)
{

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