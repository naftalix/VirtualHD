#pragma once
#include<memory>
#include<vector>
#include "Sector.h"
#pragma pack(push, 1)

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace Fms{

	/*! \brief Amount of directory entries per sector.

	This is strictly defined by the assignment. We would have used math to calculate it, but it seems that according to our math it should be 15.
	None the less, it could be replaced with: SECTORSIZE / sizeof(DirEntry) for more general behaviour.
	*/
	const SectorId ENTRIESPERSECTOR = 14; 
	
	//! Type for file size in bytes
	typedef uint32_t FileSize;

	/*! \brief Defined structure for Directory / Sub-Directory.
	* 
	*/
	struct Dir{
		//! Defined structure for Directory Entry.
		struct DirEntry{
			//! Default constructor.
			FMS_API DirEntry();

			/*! \brief Operator ==.
			* 
			* \param entry Directory Entry
			* \return this == dirEntry
			*/
			FMS_API bool operator==(const DirEntry&) const;

			/*! \brief Operator !=.
			* 
			* \param entry Directory Entry
			* \return this != dirEntry
			*/
			FMS_API bool operator!=(const DirEntry&) const;

			char fileName[12]; //!< Name of file.
			char fileOwner[12]; //!< Owner of file.
			SectorId fileAddr; //!< First sector used by the file.
			char crDate[10]; //!< Date of when the file was created.
			FileSize fileSize; //!< File size in bytes.
			RecordId eofRecNr; //!< Location of EOF for the file.
			RecordId maxRecSize; //!< Maximum record size.
			RecordId actualRecSize; //!< Actual record size.

			/*! \brief Format of record.
			* 
			* D - Directory.
			* F - Fixed length file.
			* V - Varried length file.
			*/
			char recFormat[2];
			SectorId keyOffset; //!< Offset before key in a record.
			SectorId keySize; //!< Size in bytes of key.

			/*! \brief Type of Key.
			* 
			* I - int.
			* F - Float.
			* D - Double.
			* C - Array of characters.
			*/
			char keyType[2];
			uint8_t entryStatus; //!< Status of entry. 0 - Wasn't used since last format. 1 - Active, file exist. 2 - Inactive, deleted file.
		};

		/* \brief Random access iterator for Dir.
		* 
		* This iterator is a complete random access iterator and may be used as such.
		* The items which are being iterated on, are DirEntrys in that dir.
		*/
		class iterator : std::iterator<std::random_access_iterator_tag, DirEntry>{
		private:
			SectorId loc;
			Dir *p;
		public:
			FMS_API iterator(Dir *p, SectorId loc=0);
			FMS_API bool operator==(const iterator&) const;
			FMS_API bool operator!=(const iterator&) const;
			FMS_API bool operator>(const iterator&) const;
			FMS_API bool operator<(const iterator&) const;
			FMS_API bool operator>=(const iterator&) const;
			FMS_API bool operator<=(const iterator&) const;
			FMS_API DirEntry& operator*();
			FMS_API DirEntry* operator->();
			FMS_API DirEntry& operator[](int);
			FMS_API iterator operator++();
			FMS_API iterator operator++(int);
			FMS_API iterator operator--();
			FMS_API iterator operator--(int);
			FMS_API iterator operator+(const int&) const;
			FMS_API iterator operator-(const int&) const;
			FMS_API iterator operator+=(const int&);
			FMS_API iterator operator-=(const int&);
			FMS_API int operator-(const iterator&) const;
		};

		/* \brief Const Random access iterator for Dir.
		* 
		* This iterator is a complete random access const_iterator and may be used as such.
		* The items which are being iterated on, are DirEntrys in that dir.
		*/
		class const_iterator : std::iterator<std::random_access_iterator_tag, DirEntry>{
		private:
			SectorId loc;
			const Dir *p;
		public:
			FMS_API const_iterator(const Dir *p, SectorId loc=0);
			FMS_API const_iterator(const iterator&);
			FMS_API bool operator==(const const_iterator&) const;
			FMS_API bool operator!=(const const_iterator&) const;
			FMS_API bool operator>(const const_iterator&) const;
			FMS_API bool operator<(const const_iterator&) const;
			FMS_API bool operator>=(const const_iterator&) const;
			FMS_API bool operator<=(const const_iterator&) const;
			FMS_API const DirEntry& operator*();
			FMS_API const DirEntry* operator->();
			FMS_API const DirEntry& operator[](int);
			FMS_API const_iterator operator++();
			FMS_API const_iterator operator++(int);
			FMS_API const_iterator operator--();
			FMS_API const_iterator operator--(int);
			FMS_API const_iterator operator+(const int&) const;
			FMS_API const_iterator operator-(const int&) const;
			FMS_API const_iterator operator+=(const int&);
			FMS_API const_iterator operator-=(const int&);
			FMS_API int operator-(const const_iterator&) const;
		};
		

		SectorId sectorNr; //!< Sector where this item is located.
		DirEntry dirs[CLUSTERSIZE][ENTRIESPERSECTOR]; //!< Array of all the directories / files pointed from this directory.

		/*! \brief Default constructor.
		* 
		* \sa Dir(const char *), Dir(std::vector<Sector>)
		*/
		FMS_API Dir();

		/*! \brief Contruct a directory from char stream.
		* 
		* Size of input is CLUSTERSIZE * SECTORSIZE.
		* \sa Dir(), Dir(std::vector<Sector>), sectorOutputAsCharStream()
		*/
		FMS_API Dir(const char *);

		/*! \brief Make valid char stream output for the directory.
		* 
		* Size of output is CLUSTERSIZE * SECTORSIZE.
		* \sa Dir(const char *)
		*/
		FMS_API std::unique_ptr<char[]> sectorOutputAsCharStream() const;

		/*! \brief Contruct a directory from a vector of sectors.
		* 
		* Sector count is CLUSTERSIZE.
		* \sa Dir(), Dir(const char *), sectorOutputAsVector()
		*/
		FMS_API Dir(std::vector<Sector>);

		/*! \brief Create a vector of sectors with the directory structure
		* 
		* Amount of sectors in the vector is CLUSTERSIZE
		* \sa Dir(std::vector<Sector>)
		*/
		FMS_API std::vector<Sector> sectorOutputAsVector() const;

		/*! \brief Operator [] abstraction.
		* 
		* \param i Index
		* \return Const reference to the entry
		* \sa operator[](SectorId) const
		*/
		FMS_API DirEntry& operator[](SectorId i);

		/*! \brief Operator [] abstraction, const version.
		* 
		* \param i Index
		* \return Reference to the entry
		* \sa operator[](SectorId)
		*/
		FMS_API const DirEntry& operator[](SectorId i) const;

		/*! \brief Operator ==.
		* 
		* \param dir Directory
		* \return this == dir
		*/
		FMS_API bool operator==(const Dir&) const;

		/*! \brief Operator !=.
		* 
		* \param dir Directory
		* \return this != dir
		*/
		FMS_API bool operator!=(const Dir&) const;

		/*! \brief Get begin iterator.
		* 
		* \return Iterator to the start of the directory
		*/
		FMS_API iterator begin();

		/*! \brief Get end iterator.
		* 
		* \return Iterator to the end of the directory
		*/
		FMS_API iterator end();

		/*! \brief Get begin const_iterator.
		* 
		* \return const_iterator to the start of the directory
		*/
		FMS_API const_iterator begin() const;

		/*! \brief Get end const_iterator.
		* 
		* \return const_iterator to the end of the directory
		*/
		FMS_API const_iterator end() const;

		/*! \brief Return the amount of entries the directory can hold.
		*
		* \return Amount of entries the directory can hold.
		*/
		FMS_API size_t size() const;

		/*! \brief Returns the amount of active entries in the directory.
		*
		* \return Amount of active entries in the directory.
		*/
		FMS_API uint32_t activeEntries() const;
		
		/*! \brief Pipe Dir object to ostream.
		*
		* \param out Stream object
		* \param dir The Dir to print
		* \return The stream object
		*/
		FMS_API friend std::ostream& operator<< (std::ostream&, const Dir&);

	};

}

#pragma pack(pop)
