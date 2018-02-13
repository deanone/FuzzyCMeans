/*!
* GenericFunc.cpp : imlementation of the gnfnc namespace.
*/

/*!
* project specific required inclusions
*/
#include "GenericFunc.h"
#include <Windows.h>
#include <vector>
#include <sstream>

std::string gnfnc::getExecutablePath()
{
	std::vector<char> executablePath(MAX_PATH);
	DWORD result = ::GetModuleFileNameA(NULL, &executablePath[0], static_cast<DWORD>(executablePath.size()));
	while (result == executablePath.size())
	{
		executablePath.resize(executablePath.size() * 2);
		result = ::GetModuleFileNameA(NULL, &executablePath[0], static_cast<DWORD>(executablePath.size()));
	}
	if (result == 0)
		throw std::runtime_error("GetModuleFileName() failed");
	return std::string(executablePath.begin(), executablePath.begin() + result);
}

/*!
*Function that concatenates the path of the project's executable with a filename.
*@return the concatenation of the path of the project's executable with a filename.
*/
std::string gnfnc::getExecutablePathAndMatchItWithFilename(const std::string& fileName)
{
	std::string execPath = getExecutablePath();
	size_t found = execPath.find_last_of("\\");
	execPath = execPath.substr(0, found);
	std::stringstream ss;
	ss << execPath << "\\" << fileName;
	return ss.str();
}