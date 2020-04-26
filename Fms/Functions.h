#pragma once
#include<string>

#ifdef FMS_EXPORTS
#define FMS_API __declspec(dllexport) 
#else
#define FMS_API __declspec(dllimport) 
#endif

/*! \file Functions.h
*	This file contains helper functions for the Fms. Those functions don't really fit a class.
*/

namespace Fms{

	/*! \brief Receieve the current date in DDMMYYYY format.
	*
	* \return Date in DDMMYYYY format
	*/
	FMS_API std::string getDate();

	/*! \brief Convert string to wstring
	*
	* \param s String to convert
	* \return The string as wstring
	*/
	FMS_API std::wstring stringToWString(const std::string& s);


	/*! \brief Convert date from DDMMYY format to something readable.
	*
	* \param date Char array of size 10 in format DDMMYYYY
	* \result String of DD/MM/YYYY
	*/
	FMS_API std::string convertDate(const char date[]);

	/*! \brief Remove path from full path.
	*
	* C:\\path\\to\\file.bin -> file.bin
	* \param fileName Full path or file name
	* \return File name
	*/
	// c:\path\to\file.bin
	const std::string removePath(const std::string& fileName);
}