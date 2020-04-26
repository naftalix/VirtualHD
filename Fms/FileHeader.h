#pragma once
#include "Sector.h"
#include "Dir.h"
#include "Dat.h"
#pragma pack(push, 1)

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace Fms{

	//! Defined structure for file header.
	struct FileHeader{
		SectorId sectorNr; //!< Sector where this item is located.
		Dir::DirEntry fileDesc; //!< Descritpion of file.
		DatType FAT; //!< Mark which sectors are being used by the file.
		char emptyArea[SIZEOFSECTOR - sizeof(SectorId) - sizeof(Dir::DirEntry) - sizeof(DatType)]; //!< Empty area in order for item to be the same size as sector.

		FMS_API bool operator==(const FileHeader &f) const;
		FMS_API bool operator!=(const FileHeader &f) const;
	};
}

#pragma pack(pop)