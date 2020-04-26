#pragma once
#include<cstdint>
#include<array>
#include "Functions.h"
#pragma pack(push, 1)
#pragma warning(disable: 4996)

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace Fms{

	//! Type for Sector ID.
	typedef uint32_t SectorId;

	//! Bytes that can be stored in a single sector.
	const SectorId SIZEOFSECTOR = 1024;

	/*! \brief Represent a Sector on the HDD.
	* 
	* Sector is the most basic unit that can be used to store data.
	*/
	struct Sector{
		//! Default constructor.
		FMS_API Sector();

		SectorId sectorNr; //!< Sector where this item is located.
		char rawData[SIZEOFSECTOR - sizeof(SectorId)]; //!< Data in various format.

		/*! \brief Operator ==.
		* 
		* \param s Sector
		* \return this == sector
		*/
		FMS_API bool operator==(const Sector&) const;

		/*! \brief Operator !=.
		* 
		* \param s Sector
		* \return this != sector
		*/
		FMS_API bool operator!=(const Sector&) const;


		/*! \brief Pipe sector object to ostream.
		*
		* \param out Stream object
		* \param sector The sector to print
		* \return The stream object
		*/
		FMS_API friend std::ostream& operator<< (std::ostream&, const Sector&);

	};


	//! Amount of sectors in cluster.
	const SectorId CLUSTERSIZE = 2;

	//! Type for Cluster ID
	typedef uint32_t ClusterId;

	//! Type of cluster (array of sectors)
	typedef std::array<Sector, CLUSTERSIZE> Cluster;

	//! Type for Record ID
	typedef uint32_t RecordId;
}

#pragma pack(pop)