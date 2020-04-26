#pragma once
#include "Sector.h"
#pragma pack(push, 1)

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace Fms{

	/*! \brief Defined structure for Volume Header.
	* 
	* The volume header should use a single sector to store its data. This data contains information about the disk.
	*/
	struct VolumeHeader{
		//! Constrcutor for VolumeHeader.
		FMS_API VolumeHeader();

		SectorId sectorNr; //!< Sector where this item is located.
		char diskName[12]; //!< Name of disk.
		char diskOwner[12]; //!< Name of disk owner.
		char prodDate[10]; //!< When was the HDD manufactured
		ClusterId clusQty; //!< Amount of clusters in disk.
		ClusterId dataClusQty; //!< Amount of clusters to be used by data in disk.
		SectorId addrDat; //!< Sector number where DAT is stored.
		ClusterId addrRootDir; //!< Address of the root directory in clusters (as per assignment).
		SectorId addrDatCpy; //!< Sector where a copy of the dat is located.
		ClusterId addrRootDirCpy; //!< Address of root directory copy in clusters (as per assignment).
		ClusterId addrDataStart; //!< First cluster which should be used for data.
		char formatDate[10]; //!< Date of when the disk was last formatted.
		bool isFormated; //!< Is the disk formatted?

		//! Empty area in order for item to be the same size as sector.
		char emptyArea[SIZEOFSECTOR - sizeof(SectorId) - sizeof(char[12]) - sizeof(char[12]) - sizeof(char[10]) - sizeof(ClusterId) -
			sizeof(ClusterId) - sizeof(SectorId) - sizeof(ClusterId) - sizeof(SectorId) - sizeof(ClusterId) -
			sizeof(ClusterId) - sizeof(char[10]) - sizeof(bool)];
	};

}
#pragma pack(pop)