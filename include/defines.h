#ifndef TECPLOTDEFINES_H
#define TECPLOTDEFINES_H

#define BUILD_DEBUG


#include <string>
#include <map>
#include <vector>
#include <iostream>

class TecplotZone;
class TecplotVar;

typedef std::map <std::string, TecplotZone *> TecplotZones;
typedef std::map <std::string, TecplotVar *>  TecplotVars;

typedef std::vector <std::string> strings;
typedef std::map< std::string, std::string> params;

#define ERROR(X) std::cout << X;

#ifdef BUILD_DEBUG
	#define DEBUG(X) std::cout << X << std::endl;


#else
	#define DEBUG(X) {};

#endif
#endif