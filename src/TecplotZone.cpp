#include "TecplotZone.h"

TecplotZone::TecplotZone(string name, size_t start_index, string type,
						 size_t i, size_t j, size_t k): name_(name), start_index_(start_index),
						 											type_(type), i_(i), j_(j), k_(k)
{
	size_t add = i;
	if (j > 0)
		add *= j;
	if (k > 0)
		add *= k;
	end_index_ = start_index_+ add;
}

size_t TecplotZone::start()
{
	return start_index_;
}

size_t TecplotZone::end()
{
	return end_index_;
}

size_t TecplotZone::length()
{
	return end_index_ - start_index_;
}

string TecplotZone::name()
{
	return name_;
}

size_t TecplotZone::dim()
{

	if (k_ > 0)
		return 3;
	if (j_ > 0)
		return 2;
	if (i_ > 0)
		return 1;

	return -1;

}

size_t TecplotZone::i()
{
	return i_;
}

size_t TecplotZone::j()
{
	return j_;
}

size_t TecplotZone::k()
{
	return k_;
}