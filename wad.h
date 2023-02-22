//
// Created by Candice Neill on 2/7/23.
//

#include <iostream>
#include "list.h"
#include "util.h"
#include "list.h"
#include <iosfwd>
#include <fstream>
#include <regex>
#include <math.h>

#ifndef LUMPREADER_WAD_H
#define LUMPREADER_WAD_H

using namespace std;

struct Marker
{
	string       name = "NULL";
	ulong start = -1;
	ulong end = -1;
};

struct Lump
{
	byte         *data = nullptr;
	ulong start = 0;
	ulong size  = 0;
	string       name;
	Marker       marker;
};

struct Palette
{
	byte red;
	byte green;
	byte blue;
};

struct Animation
{
	byte type;
	string last;
	string first;
	ulong speed;
};

struct Switch
{
	string on;
	string off;
	ulong compat;
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
	List<Animation> animations;
	List<Switch> switches;
	void playpalLump(const Lump& lump);
	void animatedLump(const Lump& lump);
	void switchesLump(const Lump& lump);
};

#endif //LUMPREADER_WAD_H
