#include <iostream>
#include "MglTecplotDrawer.h"
#include <map>

MglTecplotDrawer::MglTecplotDrawer(const TecplotData &data):data_(data),main_var_index_(0),show_zone_index_(-1)
{
	colors = {"k","r","R","g","G", "b", "B", "c","C", "m",
							 "M","y","Y","h", "H" ,"w","W", "l", "L", "e",
							 "E", "n", "N", "u", "U", "p", "P", "q", "Q"};

	for (int i =0; i< data_.var_count(); i++)
		this->vars_state_.push_back(true);

}

size_t MglTecplotDrawer::sum_zones_i_dim()
{
	size_t i_dim = 0;
	for (auto zone: data_.zones())
	{
		i_dim += zone->i();
	}
	return i_dim;
}

size_t MglTecplotDrawer::sum_zones_j_dim()
{
	size_t j_dim = 0;
	for (auto zone: data_.zones())
	{
		j_dim += zone->j();
	}
	return j_dim;
}

size_t MglTecplotDrawer::sum_zones_k_dim()
{
	size_t k_dim = 0;
	for (auto zone: data_.zones())
	{
		k_dim += zone->k();
	}
	return k_dim;
}

void MglTecplotDrawer::setMainVar(string var_name)
{
	//find index fot var_name
	//this->main_var_name_ = var_name;
}

void MglTecplotDrawer::showZone(string zone_name)
{
	//find index fot zone name
	//this->show_zone_name_ = zone_name;
}

void MglTecplotDrawer::setMainVar(size_t var_index)
{
	main_var_index_ = var_index;
}

void MglTecplotDrawer::showZone(int zone_index)
{
	show_zone_index_ = zone_index;
}

void MglTecplotDrawer::enableContour(bool t)
{
	contour_ = t;
}

void MglTecplotDrawer::enableVar(int index, bool state)
{
	vars_state_[index] = state;
}

void MglTecplotDrawer::Plot1d(mglGraph *gr)
{

}

void MglTecplotDrawer::Plot2d(mglGraph *gr)
{

}


int MglTecplotDrawer::Draw(mglGraph *gr)
{
	//make mgldatas;
	std::vector<mglData> datas(data_.var_count());
	TecplotZone *show_zone = NULL;

	if (show_zone_index_ >= 0 )
		show_zone = data_.zones()[show_zone_index_];

	for (int i = 0; i< data_.var_count(); i++)
	{
		if (show_zone)
			datas[i].Link(data_.vars()[i]->data_raw(show_zone), show_zone->length());
		else
			datas[i].Link(data_.vars()[i]->data_raw(), data_.vars()[i]->size());
	}

	gr->Title(data_.title().c_str());

	strings vars = data_.var_names();
	strings zones = data_.zone_names();

	int dim = data_.zones()[0]->dim();
	DEBUG("DIM is "<<dim);

	//1d point plotting
	if (dim == 1)
	{
		DEBUG("Main var is " << vars[main_var_index_]);
		gr->Label('x',vars[main_var_index_].c_str(),0);
		gr->SetRange('x',datas[main_var_index_]);

		gr->SetRange('y',datas[1]);
		gr->Axis();

		for (int i =0; i< data_.var_count(); i++)
		{
			if (i != main_var_index_ && vars_state_[i])
			{
				gr->Plot(datas[main_var_index_], datas[i],"");
			}
		}
			//DEBUG("DO LEGEND!");
			//for (int  i =0; i < vars.size(); i++)
			//{
			//	gr->AddLegend(vars[i].c_str(), colors[i % colors.size()].c_str());
			//}
			//gr->Legend();
			//gr->Label('x',vars[1].c_str(),0);
			//gr->SetRange('x',datas[vars[1]]);
			//gr->Axis();

			//do legend
			//1) find minimum and maximum for axis range
			//2) make legend for all data

	}

	//2d point plotting
	if (dim == 2)
	{
		gr->SetOrigin(-1,-1,-1);
		gr->Light(true);
		gr->Rotate(50,60);
		gr->Grid();


		gr->Label('x',vars[0].c_str(), 0);
		gr->Label('y',vars[1].c_str(), 0);
		gr->Label('z',vars[2].c_str(), 0);

		gr->SetRange('x', datas[0]);
		gr->SetRange('y', datas[1]);
		gr->SetRange('z', datas[2]);

		gr->Axis();

		//get size by first zone dimesions

		TecplotZone *first_zone;
		if (show_zone)
			first_zone = show_zone;
		else
			first_zone = data_.zones()[0];

		size_t	x_size = sum_zones_i_dim();
		size_t	y_size = sum_zones_j_dim();

		mglData g(first_zone->i(),first_zone->j());

		gr->DataGrid(g,datas[0],datas[1],datas[2]);
		gr->Surf(g);

		if (contour_)
		{
			gr->Cont(g,"y");
			gr->Cont(g,"_");

		}
	}

	if (dim == 3)
	{
		gr->SetOrigin(-1,-1,-1);
		gr->Light(true);
		gr->Rotate(50,60);
		gr->Grid();


		gr->Label('x',vars[0].c_str(), 0);
		gr->Label('y',vars[1].c_str(), 0);
		gr->Label('z',vars[2].c_str(), 0);

		gr->SetRange('x', datas[0]);
		gr->SetRange('y', datas[1]);
		gr->SetRange('z', datas[2]);

		gr->Axis();

		//get size by first zone dimesions

		TecplotZone *first_zone;
		if (show_zone)
			first_zone = show_zone;
		else
			first_zone = data_.zones()[0];

		size_t	x_size = sum_zones_i_dim();
		size_t	y_size = sum_zones_j_dim();

		mglData g(first_zone->i(),first_zone->j());
		mglData first;
		mglData second;
		mglData third;
		gr->DataGrid(g,datas[0],datas[1],datas[2]);
		gr->Surf(g);

		if (contour_)
		{
			gr->Cont(g,"y");
			gr->Cont(g,"_");

		}
	}
	return 0;
}
