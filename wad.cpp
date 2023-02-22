//
// Created by Candice Neill on 2/7/23.
//

#include "wad.h"

#include <utility>

Wad::Wad (string filepathIn)
{
	filepath = std::move(filepathIn);
}

void Wad::load()
{
	auto   file     = new ifstream();
	file->open(filepath,std::ifstream::ate | std::ifstream::binary);
	file->seekg(0,std::ios::end);
	long length = file->tellg();
	file->seekg(0,std::ios::beg);
	byte *list = new byte[length];
	printf("Length: %ld\n",length);

	for (int x = 0; x < length; x++)
	{
		int i = file->get();

		if (i < 0)
		{
			break;
		}

		byte b = static_cast<byte>(i);
		list[x] = b;
	}

	wadType   = util::asUppercaseString(list,0);
	ulong numLumps  = util::asUInt(list, 4);
	ulong directory = util::asUInt(list, 8);
	printf("Wad Type: %s\n",wadType.c_str());
	printf("Num Lumps: %lu\n",numLumps);
	printf("Directory Location: %lu\n",directory);

	printf("------------------------\n");

	for (ulong x = 0; x < numLumps; x++)
	{
		ulong    start     = directory + (x * 16);
		ulong    lumpStart = util::asUInt(list, start);
		ulong    lumpSize  = util::asUInt(list, start + 4);
		string lumpName  = util::asUppercaseString(list,start + 8,8);

		if (lumpSize == 0)
		{
			regex  markerRegex(R"(([\w\d][\w\d]?)_(START|END)?)",std::regex_constants::icase | std::regex_constants::ECMAScript);
			smatch matches;
			regex_search(lumpName,matches,markerRegex);

			if( lumpStart == 0 )
			{
				lumpStart = (int)lumps[lumps.size()-1].start + (int)lumps[lumps.size()-1].size;
			}

			string name = matches[1].str();

			if( name.length() == 1 )
			{
				name += name;
			}

			string loc  = matches[2].str();
			printf("%s - %s\n",name.c_str(),loc.c_str());

			auto marker = new Marker();

			if( lumpName.substr(0,3) == "MAP" )
			{
				marker->name = lumpName;
			}
			else
			{
				marker->name = name;
			}

			printf("Marker Start: %lu\n",lumpStart);
			printf("Marker Name: %s\n",lumpName.c_str());

			if (loc != "END")
			{
				marker->start = lumpStart;
				markers += *marker;
			}
		}
		else
		{
			auto lump = new Lump();
			lump->start = lumpStart;
			lump->size  = lumpSize;
			lump->name = lumpName;
			byte* bytes = util::asBytes(list,lumpStart,lumpSize);
			lump->data = bytes;
			printf("----------------------------");
			printf("Lump Start: %lu\n",lumpStart);
			printf("Lump Size: %lu\n",lumpSize);
			printf("Lump Name: %s\n",lumpName.c_str());
			lumps += *lump;
		}
	}

	// Sort namespaces
	for(long x=0; x<markers.size();x++ )
	{
		for(long y=0; y<markers.size();y++)
		{
			if(markers[y].start>markers[x].start)
			{
				Marker temp = markers[y];
				markers[y] = markers[x];
				markers[x] = temp;
			}
		}
	}

	int index = 0;
	Marker* currentMarker = &markers[index];

	// Find namespace for each lump
	for (long x = 0; x < lumps.size(); x++)
	{
		Lump* lump = &lumps[x];

		//printf("Lump [%s - %d]; currentMarker %d\n", lump->name.c_str(),lump->start,currentMarker->start);

		if(lump->start > currentMarker->start && index<markers.size())
		{
			currentMarker = &markers[index++];
			//if(currentMarker != nullptr )printf("NEXT! %s - %d\n",currentMarker->name.c_str(),currentMarker->start);
		}

		if(currentMarker == nullptr )
		{
			throw runtime_error("Could not find marker for lump "+lump->name);
		}

		lump->marker = *currentMarker;
	}

	// Process Lumps
	for( int x = 0; x < lumps.size(); x++ )
	{
		Lump lump = lumps[x];
		printf("Lump Name: %s\n",lump.name.c_str());
		printf("\tLump Start: %lu\n",lump.start);
		printf("\tLump Size: %lu\n",lump.size);
		printf("\tLump Namespace: %s\n",lump.marker.name.c_str());

		if(lump.name=="PLAYPAL") playpalLump(lump);
		if(lump.name=="ANIMATED") animatedLump(lump);
		if(lump.name=="SWITCHES") switchesLump(lump);
	}

	printf("Size: %u\n",lumps.size());

	delete file;
}

void Wad::playpalLump(const Lump& lump)
{
	if(lump.size%(256*3)!=0) throw std::runtime_error("Invalid PLAYPAL format");
	unsigned int numPal = lump.size / (256 * 3);

	for(int palNum = 0; palNum < numPal; palNum++)
	{
		int     recStart = palNum * 3;
		byte    red      = lump.data[recStart];
		byte    green    = lump.data[recStart + 1];
		byte    blue     = lump.data[recStart + 2];
		Palette palette  = {red,green,blue};
		palettes += palette;
		//printf("Palette %d = %hhu, %hhu, %hhu\n",pal,palettes[pal].red,palettes[pal].green,palettes[pal].blue);
	}
}

void Wad::animatedLump(const Lump& lump)
{
	for(ulong recStart = 0; recStart < lump.size; recStart += 23)
	{
		byte type = lump.data[recStart];
		if(type==(byte)255) break;
		string tex1 = util::asString(lump.data,recStart+1,9);
		string tex2 = util::asString(lump.data,recStart+10,9);
		ulong speed = util::asUInt(lump.data, recStart + 19, 4);

		Animation animation = {type,tex1,tex2,speed};
		animations += animation;
		printf("[%hhu] %s -> %s (%lu)\n",type,tex1.c_str(),tex2.c_str(),speed);
	}
}

void Wad::switchesLump(const Lump& lump)
{
	for(ulong recStart = 0; recStart < lump.size; recStart += 20)
	{
		string tex1 = util::asString(lump.data,recStart,9);
		string tex2 = util::asString(lump.data,recStart+9,9);
		ulong compat = util::asUInt(lump.data, recStart + 18, 2);
		if(compat==0)break;
		Switch s = {tex1,tex2,compat};
		switches += s;
		printf("%s -> %s (%lu)\n", tex1.c_str(), tex2.c_str(), compat);
	}
}