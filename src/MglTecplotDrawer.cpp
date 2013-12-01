#include <iostream>
#include "MglTecplotDrawer.h"
#include <map>

MglTecplotDrawer::MglTecplotDrawer(const TecplotData &data):data_(data)
{
}

int MglTecplotDrawer::Draw(mglGraph *gr)
{
	//make mgldatas;

	std::map <string, mglData> datas;
	for (string name : data_.var_names())
	{
		datas[name].Link(data_.var(name)->data_raw(), data_.var_size(name));
	}


	gr->Title(data_.title().c_str());


	//1d point plotting
	#warning This is not true, 1d or 2d or 3d plot type must be got from TecplotZone, not from count of variables
	if (data_.var_count() == 2)
	{
		gr->Grid();

		std::vector<string> names = data_.var_names();
		gr->Label('y',names[0].c_str(),0);
		gr->Label('x',names[1].c_str(),0);

		gr->SetRange('x',datas[names[1]]);
		gr->SetRange('y',datas[names[0]]);
		gr->Axis();

		gr->Plot(datas[names[1]], datas[names[0]],"*");

	}

		//2d point plotting
	if (data_.var_count() == 3)
	{
		cout<<"Plotting 2d type"<<endl;
		gr->SetOrigin(-1,-1,-1);
		gr->Light(true);
		gr->Rotate(50,60);
		gr->Grid();

		std::vector<string> names = data_.var_names();

		gr->Label('x',names[2].c_str(), 0);
		gr->Label('y',names[1].c_str(), 0);
		gr->Label('z',names[0].c_str(), 0);

		gr->SetRange('x', datas[names[2]]);
		gr->SetRange('y', datas[names[1]]);
		gr->SetRange('z', datas[names[0]]);

		gr->Axis();


		mglData g(10,15);

		gr->DataGrid(g,datas[names[2]],datas[names[1]],datas[names[0]]);
		gr->Surf(g);

/*
		  gr->SubPlot(2,2,3); gr->Title("parametric form");
  mglData x(50,40),y(50,40),z(50,40);
  gr->Fill(x,"0.8*sin(pi*x)*sin(pi*(y+1)/2)");
  gr->Fill(y,"0.8*cos(pi*x)*sin(pi*(y+1)/2)");
  gr->Fill(z,"0.8*cos(pi*(y+1)/2)");
  gr->Rotate(50,60);  gr->Box();  gr->Surf(x,y,z,"BbwrR");
*/

		//gr->Plot(datas[names[2]], datas[names[1]], datas[names[0]],"BbwrR");
		//gr->Surf();

		//gr->Rotate(60);

	}
	return 0;
}
