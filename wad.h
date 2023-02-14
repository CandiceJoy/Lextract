//
// Created by Candice Neill on 2/7/23.
//

#include <iostream>
#include "list.h"
#include "util.h"
#include "list.h"
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <regex>

#ifndef LUMPREADER_WAD_H
#define LUMPREADER_WAD_H

using namespace std;

struct Marker
{
	string       name = "NULL";
	unsigned int start = -1;
	unsigned int end = -1;
};

struct Lump
{
	byte         *data = nullptr;
	unsigned int start = 0;
	unsigned int size  = 0;
	string       name;
	Marker       marker;
};

struct Palette
{
	byte red;
	byte green;
	byte blue;
};

class Wad
{
public:
	Wad(string filepathIn);
	void load();
private:
	List<Lump> lumps= *new List<Lump>();
	List<Marker> markers = *new List<Marker>();
	string wadType;
	string filepath;
	List<Palette> palettes;
};

#endif //LUMPREADER_WAD_H
