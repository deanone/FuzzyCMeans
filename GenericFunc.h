#ifndef GF_H
#define GF_H

#include "DataTypes.h"

namespace gf
{
	/*!
	 * Returns the absolute path of the executable's directory.
	 * @return the absolute path of the executable's directory.
	 */
	std::string getExecutablePath();

	/*!
	 * Returns the absolute path a file located in the executable's directory.
	 * @param fileName the name of the file (e.g., file.txt)
	 * @return the absolute path of the file
	 */
	std::string getExecutablePathAndMatchItWithFilename(std::string filename);
}

#endif	//	GF_H