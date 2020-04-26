#pragma once
#include "Fcb.h"
#include "Disk.h"
#include<memory>
#include<array>

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace Fms{

	/*! \brief Disk Management System
	*
	* This is used to manage multiple Fcb objects as well as limit the openning of already open files. This is the system behind that manages which files are open and in what way.
	*/
	class Dms{
	private:
		Fcb *fcbArray; //!< Array of Fcb to operate files
		size_t fcbArrSize; //!< Size of fcbArray

		//! Disabled copy constructor
		Dms(const Dms&);
		//! Disabled operator=
		Dms operator=(const Dms&);
	public:
		/*! \brief Constructor.
		*
		* \param fcbArrSize of Fcb items this instance should be capable of handling.
		*/
		FMS_API Dms(size_t fcbArrSize=5);

		//! Destructor.
		FMS_API ~Dms();

		/*! \brief Open a file.
		*
		* \param d Disk
		* \param fileName File name
		* \param userName User that requests to open the file
		* \param mode Openning opetion
		* \return Pointer to Fcb. Valid only in the scope of Dms.
		*/
		FMS_API Fcb* openFile(Disk*, const std::string &, const std::string &, const std::string &);

		/*! \brief Find a free Fcb to open a file.
		*
		* \param d Disk
		* \param fName File name
		* \return Pointer to Fcb. Valid only in the scope of Dms. In case none were found value is NULL.
		*/
		FMS_API Fcb* lookForFcb(Disk*, const std::string &);
	};
}
