#include "Sector.h"
#include<cstring>

namespace Fms{

	Sector::Sector(){
		sectorNr = 0;
		memset(rawData, '\0', sizeof(rawData));
	}

	bool Sector::operator==(const Sector &s) const{
		if (memcmp(this, &s, sizeof(Sector)) == 0){
			return true;
		}
		return false;
	}

	bool Sector::operator!=(const Sector &s) const{
		return !(operator==(s));
	}

	std::ostream& operator<< (std::ostream& out, const Sector &sector){
		// Create a temp copy of rawData with null character in it's end to prevent overflow.
		char toPrint[(sizeof(sector.rawData) + 1)];
		std::strncpy(toPrint, sector.rawData, sizeof(sector.rawData));
		toPrint[sizeof(sector.rawData)] = '\0';
		out << "\nSector number: " << sector.sectorNr << std::endl
			<< "Data of sector: " << toPrint << std::endl;
		return out;
	}
}