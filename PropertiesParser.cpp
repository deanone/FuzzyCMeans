#include <fstream>
#include <sstream>

#include "PropertiesParser.h"

PropertiesParser::PropertiesParser(std::string propertiesFilename)
{
	addPropertiesFile(propertiesFilename);
}

void PropertiesParser::addPropertiesFile(std::string propertiesFilename)
{
	std::ifstream properties_file;
	properties_file.open(propertiesFilename.c_str(), std::ios::in);
	std::string line;
	if (properties_file.good())
	{
		while (properties_file.eof() == false)
		{
			line.clear();
			getline(properties_file, line);
			if (line.length() > 0 && line[0] != '#')
			{
				std::string propertyName;
				std::string propertyValue;
				std::stringstream ss(line);
				char c;//c used to eat the '=' character
				ss >> propertyName >> c >> propertyValue;
				propMap[propertyName] = propertyValue;
			}
		}
	}
	properties_file.close();
}

bool PropertiesParser::propertyExists(std::string propertyName)
{
	return (!(propMap.find(propertyName) == propMap.end()));
}

std::string PropertiesParser::getPropertyAsString(std::string propertyName)
{
	return propMap[propertyName];
}

int PropertiesParser::getPropertyAsInt(std::string propertyName)
{
	int propertyValue;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

bool PropertiesParser::getPropertyAsBool(std::string propertyName)
{
	bool propertyValue;
	propertyValue = (propMap[propertyName] == "true");
	return propertyValue;
}

float PropertiesParser::getPropertyAsFloat(std::string propertyName)
{
	float propertyValue;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

double PropertiesParser::getPropertyAsDouble(std::string propertyName)
{
	double propertyValue;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

std::string PropertiesParser::getPropertyAsStringOrDefaultTo(std::string propertyName, std::string defaultPropertyValue)
{
	if (propertyExists(propertyName))
	{
		return getPropertyAsString(propertyName);
	}
	else
	{
		return defaultPropertyValue;
	}
}

int PropertiesParser::getPropertyAsIntOrDefaultTo(std::string propertyName, int defaultPropertyValue)
{
	if (propertyExists(propertyName))
	{
		return getPropertyAsInt(propertyName);
	}
	else
	{
		return defaultPropertyValue;
	}
}

bool PropertiesParser::getPropertyAsBoolOrDefaultTo(std::string propertyName, bool defaultPropertyValue)
{
	if (propertyExists(propertyName))
	{
		return getPropertyAsBool(propertyName);
	}
	else
	{
		return defaultPropertyValue;
	}
}

float PropertiesParser::getPropertyAsFloatOrDefaultTo(std::string propertyName, float defaultPropertyValue)
{
	if (propertyExists(propertyName))
	{
		return getPropertyAsFloat(propertyName);
	}
	else
	{
		return defaultPropertyValue;
	}
}

double PropertiesParser::getPropertyAsDoubleOrDefaultTo(std::string propertyName, double defaultPropertyValue)
{
	if (propertyExists(propertyName))
	{
		return getPropertyAsDouble(propertyName);
	}
	else
	{
		return defaultPropertyValue;
	}
}