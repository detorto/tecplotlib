#ifndef TECPLOTPARCER_H
#define TECPLOTPARCER_H

#include "TecplotPaser.h"

#include "defines.h"
#include <string>

class TecplotFile
{
	TecplotFile(string file);
	TecplotData data(string file_path);
};

#endif