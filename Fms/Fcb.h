#pragma once
#include "Dir.h"
#include "Dat.h"
#include "Sector.h"
#include<memory>

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace Fms{

	class Disk;

	/*! \brief File control block.
	*
	* This is used to open a file and maniplulate each and every record inside it. It enables moving through the records, reading them as well as writing them.
	*/
	class Fcb{
	private:
		//! Initalize the object.
		void init();

		/*! Check where the virtual sector gets mapped to.
		*
		* \return Physical sector of current logical sector.
		*/
		SectorId getRealSectorNumber() const;

		//! Move the current record to the next one.
		void moveToNextRecord();

		bool lock; //!< Prevent working with the file when it is locked.
		Sector buffer; //!< Buffer for reading / writing sectors
		RecordId currRecNumber; //!< Current record number in file
		SectorId currSecNr; //!< Current sector being read (This is a logical value. I.e. the X sector of the file)
		RecordId currRecNrInBuff; //!< Current record number in current sector
		bool loaded; //!< Used for checking whenever we got buffer in memory or not
	public:
		//! The method which the FCB can be used.
		enum class OpenMode : int {I,O,IO};

		Disk* d; //!< Pointer to the Disk this FCB effects.
		Dir::DirEntry fileDesc; //!< Current file description.
		DatType fat; //!< Fat of current read file
		OpenMode mode; //!< Method which the FCB is being used


		//! Default constructor.
		FMS_API Fcb();

		//! Constructor that sets disk ptr automatically.
		FMS_API Fcb(Disk*);

		//! Destructor.
		FMS_API ~Fcb();

		//! Close the file.
		FMS_API void closeFile();

		//! Save changes written in current buffer to disk.
		FMS_API void flushFile();

		/* ! \brief Read a record into char* (Deprecated). 
		*
		* This function is deprecated. This is because it is not safe in terms of returned value.
		* You'll have to make sure the char* being sent is of fileDesc.actualRecSize size.
		* Usage of the other read function is recommended.
		* \param dst Place where the data should be written
		* \param mode 0 - Read and move forward. 1 - Read and lock for changing the record.
		* \sa read(uint32_t)
		*/
		//void read(char *, uint32_t mode=0);

		/*! \brief Read a record.
		*
		* The returned char[] size is of fileDesc.actualRecSize.
		* \param mode 0 - Read and move forward. 1 - Read and lock for changing the record.
		* \return Char array of the string. Size is fileDesc.actualRecSize.
		* \sa read(char*, uint32_t)
		*/
		FMS_API std::unique_ptr<char[]> read(uint32_t mode=0);

		/*! \brief Write a record.
		*
		* \param src Char stream at the size of fileDesc.actualRecSize to be written.
		*/
		FMS_API void write(char *);

		/*! \brief Seek to record.
		*
		* Moves the needle to the requested record. Buffer gets updated.
		* \param mode 0 - From start. 1 - From current location. 2 - From EOF.
		* \param amount Amount of records to move.
		*/
		FMS_API void seek(uint32_t mode, int32_t amount);

		//! Cancel update record.
		FMS_API void updateCancel();

		/*! \brief Delete the current record.
		*
		* Delete the current record by setting the record key as 0/NULL. After deletion it moves to next record.
		*/
		FMS_API void delRecord();

		/*! \brief Update the current record.
		*
		* Update the current record with a new one.
		* \param rec Char stream at the size of fileDesc.actualRecSize to be written instead of current record.
		*/
		FMS_API void update(char *);

		/*! Check for EOF.
		*
		* \return bool whenever or not logical EOF was reached.
		*/
		FMS_API bool eof();
	};

}