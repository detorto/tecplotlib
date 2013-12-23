#ifndef MGLTECPLOTDRAWER_H
#define MGLTECPLOTDRAWER_H
#include <mgl2/wnd.h>
#include "TecplotData.h"
using namespace std;



class MglTecplotDrawer : public mglDraw
{
std::vector<string> colors;

public:
	MglTecplotDrawer(const TecplotData &data);
	int Draw(mglGraph *gr);

	void setMainVar(string var_name);
	void showZone(string zone_name);

	void setMainVar(size_t var_index);
	void showZone(int zone_index);
	void enableVar(int index, bool state);

	void enableContour(bool t);
	void Plot1d(mglGraph *gr);
	void Plot2d(mglGraph *gr);


private:
	TecplotData data_;
	size_t main_var_index_;
	int show_zone_index_;
	std::vector<bool> vars_state_;
	bool contour_;

	size_t sum_zones_i_dim();
	size_t sum_zones_j_dim();
	size_t sum_zones_k_dim();

};

#endif