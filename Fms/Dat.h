#pragma once
#include<bitset>
#include "Sector.h"
#pragma pack(push, 1)

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace Fms{

	//! Amount of clusters in the disk.
	const ClusterId CLUSTERSINDISK = 1600;

	//! DAT / FAT bitset for marking which clusters are free / taken.
	typedef std::bitset<CLUSTERSINDISK> DatType;

	/*! \brief Defined structure for Disk DAT.

	The DAT should use a single sector to store its data. This data contains information about the disk.
	*/
	struct Dat{
		SectorId sectorNr; //!< Sector where this item is located.
		DatType dat; //!< Mark which clusters are free / taken.
		char emptyArea[SIZEOFSECTOR - sizeof(DatType) - sizeof(ClusterId)]; //!< Empty area in order for item to be the same size as sector.

		//! Default constructor.
		FMS_API Dat();

		/*! \brief Pipe Dat object to ostream.
		*
		* \param out Stream object
		* \param dat The Dat to print
		* \return The stream object
		*/
		FMS_API friend std::ostream& operator<< (std::ostream&, const Dat&);
	};
}

#pragma pack(pop)