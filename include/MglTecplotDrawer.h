#ifndef MGLTECPLOTDRAWER_H
#define MGLTECPLOTDRAWER_H
#include <mgl2/wnd.h>
#include "TecplotData.h"
using namespace std;

class MglTecplotDrawer : public mglDraw
{
public:
	MglTecplotDrawer(const TecplotData &data);
	int Draw(mglGraph *gr);
private:
	TecplotData data_;
};

#endif