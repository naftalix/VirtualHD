#pragma once
#include "Sector.h"
#include "Dat.h"
#include "Dir.h"
#include "VolumeHeader.h"
#include "FileHeader.h"
#include <fstream>
#include <memory>
#include <vector>
#include <set>
#pragma pack(push, 1)

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace Fms{
	//! Amount of clusters used for HDD structure
	const ClusterId CLUSTERSRESERVED=4;

	class Fcb;

	/*! \brief Represent a disk in memory.
	*
	* This could be used to mount a virtual disk from the HDD in the correct format, and do various tasks on it.
	*/
	class Disk{
	private:

		VolumeHeader vhd; //!< General information about virtual disk.
		Dat dat; //!< Marks which clusters are currently used in the virtual disk.
		Dir rootDir; //!< Root directory of virtual disk.
		bool mounted; //!< Mark whenever the virual disk is mounted or not.
		std::fstream dskfl; //!< Used for interacting with the real HDD.
		SectorId currDiskSectorNr; //!< Current sector. I.E. which sector is going to be affected by the next read / write task.
		std::string fileName; //!< Disk file name.

		/*! \brief Disable copy constructor
		*
		* This is because we have fstream object which isn't copyable. It doesn't make much sense to have multiple instances of the same disk.
		*/
		Disk(const Disk&);

		/*! \brief Disable opeartor=
		*
		* This is because we have fstream object which isn't copyable. It doesn't make much sense to have multiple instances of the same disk.
		*/
		Disk& operator=(const Disk&);

		/*! \brief Move the reading head to target sector.
		* 
		* \sa moveWritingHead()
		*/
		void moveReadingHead();

		/*! \brief Move the writing head to target sector.
		* 
		* \sa moveReadingHead()
		*/
		void moveWritingHead();

		/*! \brief Read a batch of sectors.
		*
		* After reading, the needle will move to the sector after the last read sector.
		* \param count Amount of sectors to be read
		* \return Vector of sectors with read sectors
		* \sa readSector(Sector*), readSector(SectorId, Sector*), readSectors(SectorId, SectorId)
		*/
		std::vector<Sector> readSectors(SectorId);

		/*! \brief Read a batch of sectors.
		*
		* After reading, the needle will move to the sector after the last read sector.
		* \param count Amount of sectors to be read
		* \param location Sector number to reading from
		* \return Vector of sectors with read sectors
		* \sa readSector(Sector*), readSector(SectorId, Sector*), readSectors(SectorId)
		*/
		std::vector<Sector> readSectors(SectorId, SectorId);

		/*! \brief Write a batch of sectors.
		*
		* After writing, the needle will move to the sector after the last read sector.
		* \param vector Vector of sectors to write
		* \sa writeSector(Sector*), writeSector(SectorId, Sector*), writeSectors(std::vector<Sector>, SectorId)
		*/
		void writeSectors(std::vector<Sector>);

		/*! \brief Write a batch of sectors.
		*
		* After writing, the needle will move to the sector after the last read sector.
		* \param vector Vector of sectors to write
		* \param location Sector number to reading from
		* \sa writeSector(Sector*), writeSector(SectorId, Sector*), writeSectors(std::vector<Sector>)
		*/
		void writeSectors(std::vector<Sector>, SectorId);

		/*! \brief Write a cluster to a specified location.
		* 
		* \param location Cluster number where the cluster should be read from
		* \return Read cluster
		* \sa writeCluster(Cluster, ClusterId)
		*/
		Cluster readCluster(ClusterId);

		/*! \brief Write a cluster to a specified location.
		* 
		* \param cluster Cluster to be written
		* \param location Cluster number where the cluster should be written
		* \sa readCluster(ClusterId)
		*/
		void writeCluster(Cluster, ClusterId);

		/*! \brief Initialize the object.
		*
		* \sa Disk(), Disk(std::string &, std::string &, char)
		*/
		void init();

		/*! \brief Assert that a file exist.
		*
		* If the file exist, nothing happens. If it doesn't, an exception is thrown.
		*/
		void verifyFile(std::string);

		/* \brief Find location of writing amount of clusters to disk using First Fit.
		*
		* This works by finding the first batch of free clusters that is big enough.
		* \param numClusters Amount of free clusters
		* \return Suggested FAT for file
		* \sa bestFit(ClusterId) worstFit(ClusterId) fillFit(ClusterId)
		*/
		DatType firstFit(ClusterId) const;

		/* \brief Find location of writing amount of clusters to disk using Best Fit.
		*
		* This works by finding the smallest batch of free clusters that is big enough.
		* \param numClusters Amount of free clusters
		* \return Suggested FAT for file
		* \sa firstFit(ClusterId) worstFit(ClusterId) fillFit(ClusterId)
		*/
		DatType bestFit(ClusterId) const;

		/* \brief Find location of writing amount of clusters to disk using worst Fit.
		*
		* This works by finding the biggest batch of free clusters.
		* \param numClusters Amount of free clusters
		* \return Suggested FAT for file
		* \sa bestFit(ClusterId) firstFit(ClusterId) fillFit(ClusterId)
		*/
		DatType worstFit(ClusterId) const;

		/* \brief Find enough free spots that sum to the requested amount of clusters.
		*
		* This is an NP complete problem and thus ineffective in terms of calculation.
		* \param numClusters Amount of free clusters
		* \return Suggested FAT for file
		* \sa bestFit(ClusterId) worstFit(ClusterId) firstFit(ClusterId)
		*/
		DatType fillFit(ClusterId) const;

		/* \brief Move the file on disk to fit it's new FAT.
		*
		* When a file FAT changes, it should be noted that the file might end up corrupted as the file might gain additional free space in the middle of it.
		* This function moves the saved sectors of the file as to preserve the order, so that all new space would be in it's end.
		* \param oldFat Old FAT of file
		* \param newFat New FAT of file
		* \param start Number of first cluster in the file
		*/
		void updateFileToFat(DatType, DatType, ClusterId);

		/*! \brief Swap to clusters on the disk.
		* 
		* \param loc1 The first location
		* \param loc2 The second location
		*/
		void swapClusters(ClusterId, ClusterId);

		/*! \brief Move a file from an old fat to a new one.
		* 
		* This changes the first cluster to be the result of findFirstClusterOfFile on the new FAT.
		* \param oldFat The old FAT of the file
		* \param newFat The new FAT of the file
		* \param startOfOld The cluster number for the first cluster in the old file.
		* \sa findFirstClusterOfFile(DatType)
		*/
		void moveFile(DatType, DatType, ClusterId);

		/*! \brief Suggest a sequential FAT for the file.
		* 
		* \param fat The current FAT of file.
		* \return A sequential FAT for the file.
		*/
		DatType defragFitFirst(DatType) const;

		/*! \brief Suggest how to put the file in the end of the disk.
		* 
		* This tries to squeeze the file to the end of the disk. The file could end up really fragmented.
		* \param fat Current FAT of file
		* \return Suggested FAT for pushing the file to the end of the disk.
		*/
		DatType defragFitEnd(DatType) const;

		/*! \brief Try to force all files to be sequential at the start of the disk.
		* 
		* \param dir Directory to process
		* \param skip DirEntry to skip
		*/
		void defragAlignStart(Dir& dir, Dir::DirEntry &skip = Dir::DirEntry());

		/*! \brief Check if a FAT is sequential.
		* 
		* This checks whenever all the bits set on the DatType are next to each other (one long line).
		* \param fat
		* \return Whenever the fat is sequential.
		*/
		bool fatIsSequential(DatType) const;

		/*! \brief Defrag the disk
		* 
		* Try to defrag a directory. This is a risky operation by definition, take caution before using it and always backup your data.
		* \param dir Directory to defrag
		* \param rounds Maximum amount of rounds to try and defrag, 0 for unlimited.
		*/
		void defrag(Dir&, size_t rounds=0);

	public:

		/*! \brief Helper class for reading FAT Table
		*
		* This is used for moving through FAT Table without having to worry about the bits.
		*/
		class FatReader{
		private:
			const DatType &fat; //!< Fat to read
			ClusterId phyStart; //!< First physical cluster
			ClusterId phyLoc; //!< Physical location of the current cluster
			ClusterId logicLoc; //!< Logical location of the current cluster
		public:
			/* \brief Constructor
			*
			* \param fat The FAT to read
			* \param phyStart Cluster number where the file starts.
			*/
			FatReader(const DatType&, ClusterId);

			/* \brief Get current physical cluster.
			*
			* \return Current physical cluster pointed by the reader
			*/
			ClusterId operator*();

			/* \brief Move the physical operator to the next marked bit.
			*
			* \return The physical number after moving the needle.
			* \sa operator++(int)
			*/
			ClusterId operator++();

			/* \brief Move the physical operator to the next marked bit.
			*
			* \return The physical number before moving the needle.
			* \sa operator++()
			*/
			ClusterId operator++(int);

			/* \brief Move the physical operator to the previous marked bit.
			*
			* \return The physical number after moving the needle.
			* \sa operator--(int)
			*/
			ClusterId operator--();

			/* \brief Move the physical operator to the previous marked bit.
			*
			* \return The physical number before moving the needle.
			* \sa operator--()
			*/
			ClusterId operator--(int);

			/*! \brief Returns all the locations the file has allocated.
			*
			* \return std::vector<std::pair<Location,Amount>>
			*/
			std::vector<std::pair<ClusterId, SectorId> > getLocationsVector() const;
		};

		/*! \brief Default constructor.
		*
		\sa Disk(std::string &, std::string &, char)
		*/
		FMS_API Disk();

		/*! \brief Construct using disk name.
		* 
		* \param diskName Disk name (file name)
		* \param ownerName Owner of disk
		* \param code 'c' - Create, 'm' - Mount
		*
		* \warning An exception may be thrown when the flag in incorrect / request to create a file for an existing file / request to mount non existing file.
		* \sa Disk()
		*/
		FMS_API Disk(std::string &, std::string &, char);

		//! \brief Destrcutor. Enforces safe unmount.
		FMS_API ~Disk();

		/*! \brief Create a new unformatted disk.
		* 
		* \param diskName Name of disk
		* \param diskOwner Name of disk owner
		*/
		FMS_API void createDisk(std::string &diskName, std::string &diskOwner);

		/*! \brief Mount a disk.
		* 
		* \param diskName Name of the disk
		*/
		FMS_API void mountDisk(std::string &diskName);

		/*! \brief Unmount mounted disk.
		*/
		FMS_API void unmountDisk();

		/*! \brief Recreates the disk.
		*
		* Can only be used after a disk has been chosen (via createDisk or mountDisk).
		* \param diskOwner Name of disk owner
		*/
		FMS_API void recreateDisk(std::string &diskOwner);

		/*! \brief Get the pointer to the opened disk.
		*
		* \return A pointer (fstream) to the disk file.
		*/
		std::fstream *getDskfl();

		//! Move the sector needle to the requested sector.
		FMS_API void seekToSector(SectorId);

		/*! \brief Write data to a free specified sector.
		*
		* Data can only be written to a sector marked as free.
		* After writing, the needle will move to the next sector.
		* \param target Id of sector to be written
		* \param sector data to be written
		* \sa writeSector(Sector*) writeSector(SectorId, Sector*)
		*/
		FMS_API void writeFreeSector(SectorId, Sector*);

		/*! \brief Write data to specified sector.
		*
		* After writing, the needle will move to the next sector.
		* \param target Id of sector to be written
		* \param sector data to be written
		* \sa writeSector(Sector*) writeFreeSector(SectorId, Sector*);
		*/
		FMS_API void writeSector(SectorId, Sector*);

		/*! \brief Write data to sector.
		* 
		* After writing, the needle will move to the next sector.
		* \param sector Data to be written.
		* \sa writeSector(SectorId, Sector*) writeFreeSector(SectorId, Sector*);
		*/
		FMS_API void writeSector(Sector*);

		/*! \brief Read data from sector.
		*
		* After reading, the needle will move to the next sector.
		* \param target Id of sector to be read
		* \param sector Sector pointer to receive the data
		* \sa readSector(Sector*)
		*/
		FMS_API void readSector(SectorId, Sector*);

		/*! \brief Read data from sector.
		*
		* After reading, the needle will move to the next sector.
		* \param sector Pointer to receive the data
		* \sa readSector(SectorId, Sector*)
		*/
		FMS_API void readSector(Sector*);

		/*! \brief Formats the disk.
		*
		* \param ownerName The name of the disk owner
		*/
		FMS_API void format(std::string);

		/*! \brief Returns the amount of free clusters in the disk.
		*
		* \return Amount of free clusters
		*/
		FMS_API ClusterId howMuchEmpty() const;

		/*! \brief Mark the sectors in given FAT as free.
		*
		* This works by marking the DAT as (DAT | FAT). Afterwards, the given FAT would be filled with 0's.
		* \param fat FAT to free.
		* \sa alloc(DatType &, SectorId, uint32_t) allocExtend(DatType &, SectorId, uint32_t)
		*/
		void dealloc(DatType &);

		/*! \brief Allocate sectors to file.
		*
		* \param fat FAT which will receieve the sectors.
		* \param numSectors Amount of sectors to be allocated.
		* \param mode Allocation method. 0 - First fit. 1 - Best fit. 2 - Worst fit.
		* \sa dealloc(DatType &) allocExtend(DatType &, SectorId, uint32_t)
		*/
		void alloc(DatType &, SectorId, uint32_t);

		/*! \brief Allocate more sectors to file.
		*
		* \param fat FAT which will receieve the sectors.
		* \param numSectors Amount of sectors to be allocated in addition to what the FAT already has.
		* \param mode Allocation method. 0 - First fit. 1 - Best fit. 2 - Worst fit.
		* \sa alloc(DatType &, SectorId, uint32_t) dealloc(DatType &)
		*/
		void allocExtend(DatType &, SectorId, uint32_t);

		/*! \brief Pipe disk object to ostream.
		*
		* \param out Stream object
		* \param disk The disk to print
		* \return The stream object
		*/
		FMS_API friend std::ostream& operator<< (std::ostream&, const Disk&);

		/*! \brief Return the disk dat.
		*
		* \return Current dat of disk
		*/
		FMS_API const Dat& getDat() const;

		/*! \brief Return current visible directory in disk.
		*
		* In reality it's going to be the rootDir, as only that is supported (i.e. no subfolders avilable, though it can be extended to).
		* \return Current dir in disk
		*/
		FMS_API const Dir& getDir() const;

		/*! \brief Return the VolumeHeader of the mounted disk.
		*
		* \return Current Vhd
		*/
		FMS_API const VolumeHeader& getVolumeHeader() const;

		/*! \brief Create a new file.
		* 
		* The file is in the root directory. No other folder is available as per the spec.
		* \param fileName Name of file to create
		* \param ownerName name of file owner
		* \param fileType Type of file. F - Fixed length. V - Variable length.
		* \param recordLength Length of each record / Maximum length for variable length.
		* \param numSectors Amount of sectors that file should have
		* \param keyType Record key type. I - Integer, F - Float, D - Double, C - Char.
		* \param keyOffset Offset of key in record
		* \param fit Fit type. 0 - First fit. 1 - Best fit. 2 - Worst fit.
		* \param keyLength When key type is char: Size of key
		* \sa delFile(const std::string &, const std::string &) extendFile(const std::string &, const std::string &, SectorId, uint32_t fit = 1)
		*/
		FMS_API void createFile(const std::string &fileName, const std::string &ownerName, const std::string &fileType,
			size_t recordLength, SectorId numSectors, const std::string &keyType, size_t keyOffset, uint32_t fit = 1, size_t keyLength = 1);

		/*! \brief Delete a file
		*
		* The file is in the root directory. No other folder is available as per the spec.
		* \param fileName Name of file to delete
		* \param ownerName Name of file owner
		* \sa delFile(const std::string &, const std::string &) 
		* \sa createFile(const std::string &fileName, const std::string &ownerName, const std::string &fileType, size_t recordLength, SectorId numSectors, const std::string &keyType, size_t keyOffset, size_t keyLength = 1)
		*/
		FMS_API void delFile(const std::string &, const std::string &);

		/*! \brief Extend the size of a file
		*
		* The file is in the root directory. No other folder is available as per the spec.
		* \param fileName Name of file to extend
		* \param ownerName Name of file owner
		* \param amount Amount of sectors to add
		* \param fit Fit type. 0 - First fit. 1 - Best fit. 2 - Worst fit.
		* \sa delFile(const std::string &, const std::string &)
		* \sa createFile(const std::string &fileName, const std::string &ownerName, const std::string &fileType, size_t recordLength, SectorId numSectors, const std::string &keyType, size_t keyOffset, uint32_t fit = 1, size_t keyLength = 1)
		*/
		FMS_API void extendFile(const std::string &, const std::string &, SectorId, uint32_t fit = 1);

		/*! \brief Find file in disk
		*
		* The file is in the root directory. No other folder is available as per the spec.
		* \param fileName Name of file to find
		* \param ePlace Entry place of file info after the func ending.
		* \return FileHeader obj of the file
		*/
		FMS_API FileHeader findFile(const std::string &, size_t &);

		/*! \brief Defrag the disk
		* 
		* Try to defrag the root directory
		* \param rounds Maximum amount of rounds to try and defrag, 0 for unlimited.
		*/
		FMS_API void defrag(size_t rounds=0);

		/*! \brief Open a file.
		*
		* \param fileName Name of the file
		* \param userName Name of user requesting the file 
		* \param mode Mode of openning. I - Input. O - Output. IO - Input/Output. E - Edit.
		* \return Unique_ptr to an Fcb for the file.
		*/
		FMS_API std::unique_ptr<Fcb> openFile(const std::string &fileName, const std::string &userName, const std::string &mode);

		/*! \brief What should be the first cluster of the file if it's from the start.
		* 
		* \param fat The fat to check against
		* \return Suggested value for firfst cluster of file.
		*/
		static ClusterId findFirstClusterOfFile(DatType);

		/*! \brief Upload a file from real disk to disk.
		*
		* \param src Path / Filename of source.
		* \param fName File name on disk to be created.
		* \param fOwner Owner name.
		* \param fit Allocation fit. 0 - First fit. 1 - Best fit. 2 - Worst fit.
		* \param recSizeOption Record size option. 0 - 30, 1 - 64, 2 - 98, 3 - 200.
		*/
		FMS_API void uploadFile(const std::string&, const std::string&, const std::string&, uint32_t fit = 1, uint8_t recSizeOption = 0);

		/*! \brief Download a file from disk to real disk.
		*
		* \param dest Path / Filename of destination.
		* \param fName File name on disk.
		* \param fOwner Owner name.
		*/
		FMS_API void downloadFile(const std::string&, const std::string&, const std::string&);

		/*! \brief Returns size of file in Clusters.
		*
		* \param fName Name of file
		* \return Size of file
		*/
		FMS_API ClusterId sizeOfFile(const std::string& fName);

		/*! \brief Returns size vector of file.
		*
		* \param fName Name of file
		* \return Vector of allocations
		*/
		FMS_API std::vector<std::pair<ClusterId, SectorId> > locationsVectorOfFile(const std::string& fName);
	};
}

#pragma pack(pop)