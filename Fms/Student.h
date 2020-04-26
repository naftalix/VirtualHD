#pragma once
#pragma pack(push, 1)

#include<memory>
#include<string>
#include<sstream>
#include "Disk.h"
#include "Fcb.h"

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

namespace FmsUtils{
	/*! \brief Student item.
	*
	* This is a simple student.
	*/
	struct Student{
		int32_t id; //!< Student ID
		char name[42]; //!< Student name
		char address[150]; //!< Student address
		int32_t average; //!< Student average

		//! Default constructor
		FMS_API Student();

		/*! \brief Create student from char stream.
		*
		* The size of the char stream should be 200 bytes
		* \param c Char stream
		* \sa Record(char*)
		*/
		FMS_API Student(std::unique_ptr<char[]> c);

		/*! \brief Create student from char stream.
		*
		* The size of the char stream should be 200 bytes
		* \param c Char stream
		* \sa Record(std::unique_ptr<char[]>)
		*/
		FMS_API Student(char* c);

		/*! \brief Create charstream of record.
		*
		* The length is 204 bytes.
		* \return Char stream that can be used to create the struct
		*/
		FMS_API std::unique_ptr<char[]> toCharStream();
	};

	/*! \brief Student record for saving to disk.
	*
	* This is the way to save the students to the disk as records.
	*/
	struct StudentRecord{
		int32_t key;
		Student student;

		//! Default constructor
		FMS_API StudentRecord();

		/*! \brief Create student from char stream.
		*
		* The size of the char stream should be 204 bytes
		* \param c Char stream
		* \sa StudentRecord(char*)
		*/
		FMS_API StudentRecord(std::unique_ptr<char[]> c);

		/*! \brief Create student from char stream.
		*
		* The size of the char stream should be 204 bytes
		* \param c Char stream
		* \sa StudentRecord(std::unique_ptr<char[]>)
		*/
		FMS_API StudentRecord(char* c);

		/*! \brief Create charstream of record.
		*
		* The length is 204 bytes.
		* \return Char stream that can be used to create the struct
		*/
		FMS_API std::unique_ptr<char[]> toCharStream();

		/*! \brief Upload students file.
		*
		* \param d Disk to be uploaded to. It has to be mounted.
		* \param fName File name on disk.
		* \param src File name on real disk.
		*/
		FMS_API static void uploadStudentsFile(Fms::Disk& d, std::string fName, std::string src);

		/*! \brief Download students file.
		*
		* \param d Disk to be downloaded from. It has to be mounted.
		* \param fName File name on disk.
		* \param dst File name on real disk.
		*/
		FMS_API static void downloadStudentsFile(Fms::Disk& d, std::string fName, std::string dst);

		/*! \brief Get all students as string.
		*
		* \param d Disk
		* \param fName Name of students file
		* \return String with all students
		*/
		FMS_API static std::string studentFileAsString(Fms::Disk& d, std::string fName);

		/* ! \brief Pipe student object to ostream.
		*
		* \param o Stream object
		* \param s The student to print
		* \return The stream object
		*/
		FMS_API friend std::ostream& operator<<(std::ostream&, const Student&);

		/*! \brief Pipe student object from istream.
		*
		* \param i Stream object
		* \param s The student to print
		* \return The stream object
		*/
		FMS_API friend std::istream& operator>>(std::istream&, Student&);
	};
}
#pragma pack(pop)