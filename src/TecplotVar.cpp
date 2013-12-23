#include "TecplotVar.h"
#include "TecplotZone.h"
#include <typeinfo>

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

//====================================================================
double * TecplotVar::data_raw(TecplotZone *z) const
{
	cout<<"Getting raw data"<<endl;
	cout<<"Whole data is:" <<endl;
	for( auto i: data_)
	{

		cout << typeid(i).name()<<" ";
    // Some code here
		cout <<i<<endl;
	}
	return const_cast< double *> (this->data_.data()+z->start());
}

//====================================================================
std::vector<double> * TecplotVar::data()
{
	return &this->data_;
}

//====================================================================
string TecplotVar::name()
{
	return this->name_;
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
	return this->data_.size();
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