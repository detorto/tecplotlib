#include "TecplotVar.h"

//====================================================================
TecplotVar::TecplotVar(const string & name):name_(name)
{

}

//====================================================================
TecplotVar::TecplotVar(const string & name, double *data, size_t size):name_(name)
{
	setData(data,size);
}

//====================================================================
void TecplotVar::setData(double *data, size_t size)
{
	//this->data_ = data;
	//this->size_ = size;
}

//====================================================================
void TecplotVar::setZones(TecplotZones zones)
{
	this->zones_ = zones;
}

//====================================================================
double * TecplotVar::data_raw() const
{
	return const_cast< double *> (this->data_.data());
}

std::vector<double> * TecplotVar::data()
{
	return &this->data_;
}
//====================================================================
/*double * TecplotVar::data(const string & zone) const
{
	//todo
	return NULL;
}

//====================================================================
double * TecplotVar::data(const TecplotZone & zone) const
{
	//todo
	return NULL;
}
*/
//====================================================================
size_t TecplotVar::size() const
{
	return this->size_;
}

//====================================================================
size_t TecplotVar::size(const string & zone) const
{
	//todo
	return 0;
}

//====================================================================
size_t TecplotVar::size(const TecplotZone & zone) const
{
	//todo
	return 0;
}