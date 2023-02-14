//
// Created by Candice Neill on 2/7/23.
//

#include "wad.h"

Wad::Wad (string filepathIn)
{
	filepath = filepathIn;
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

	string       wadType   = util::asUppercaseString(list,0);
	unsigned int numLumps  = util::asInt(list,4);
	unsigned int directory = util::asInt(list,8);
	printf("Wad Type: %s\n",wadType.c_str());
	printf("Num Lumps: %d\n",numLumps);
	printf("Directory Location: %d\n",directory);

	printf("------------------------\n");

	for (int x = 0; x < numLumps; x++)
	{
		int    start     = (int)directory + (x * 16);
		int    lumpStart = util::asInt(list,start);
		int    lumpSize  = util::asInt(list,start + 4);
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

			printf("Marker Start: %d\n",lumpStart);
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
			byte bytes = util::asBytes(list,lumpStart,lumpSize);
			lump->data = &bytes;
			//printf("----------------------------");
			//printf("Lump Start: %d\n",lumpStart);
			//printf("Lump Size: %d\n",lumpSize);
			//printf("Lump Name: %s\n",lumpName.c_str());
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

		if(lump->start > currentMarker->start)
		{
			index++;

			if(index<markers.size())
			{
				index++;
				currentMarker = &markers[index];
				//if(currentMarker != nullptr )printf("NEXT! %s - %d\n",currentMarker->name.c_str(),currentMarker->start);
			}
		}

		if(currentMarker == nullptr )
		{
			throw runtime_error("Could not find marker for lump "+lump->name);
		}

		lump->marker = *currentMarker;
	}

	// Output
	for( int x = 0; x < lumps.size(); x++ )
	{
		Lump lump = lumps[x];
		printf("Lump Name: %s\n",lump.name.c_str());
		printf("\tLump Start: %d\n",lump.start);
		printf("\tLump Size: %d\n",lump.size);
		printf("\tLump Namespace: %s\n",lump.marker.name.c_str());

		if(lump.name=="PLAYPAL")
		{
			if(lump.size%(256*3)!=0) throw std::runtime_error("Invalid PLAYPAL format");
			unsigned int numPal = lump.size / (256 * 3);

			for(int pal = 0; pal < numPal; pal++)
			{
				byte red = lump.data[pal*3];
				byte green = lump.data[pal*3+1];
				byte blue = lump.data[pal*3+1];
				Palette palette = {red,green,blue};
				palettes += palette;
				//printf("Palette %d = %hhu, %hhu, %hhu\n",pal,palettes[pal].red,palettes[pal].green,palettes[pal].blue);
			}
		}
	}

	printf("Size: %u\n",lumps.size());

	delete file;
}