#include "GenericFunc.h"

std::string gf::getExecutablePath()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return std::string( result, (count > 0) ? count : 0 );
}

std::string gf::getExecutablePathAndMatchItWithFilename(std::string filename)
{
    std::string execPath = getExecutablePath();
    size_t found = execPath.find_last_of("/");
    execPath = execPath.substr(0, found);
    std::stringstream ss;
    ss << execPath << "/" << filename;
    return ss.str();
}