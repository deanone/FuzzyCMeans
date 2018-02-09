/*!
 * PropertiesParser.h : interface of the PropertiesParser class.
 * Using this class one can read a properties file which contains values in the following form:
 * [propertyName] = [propertyValue]
 */

#ifndef PROPERTIES_PARSER_H
#define PROPERTIES_PARSER_H

#include <string>
#include <map>

class PropertiesParser
{
	std::map<std::string, std::string> properties_map;
public:
	PropertiesParser(std::string properties_filename);
	~PropertiesParser();
	void addPropertiesFile(std::string properties_filename);
	bool propertyExists(std::string property_name);
	std::string getPropertyAsString(std::string property_name);
	int getPropertyAsInt(std::string property_name);
	bool getPropertyAsBool(std::string property_name);
	float getPropertyAsFloat(std::string property_name);
	double getPropertyAsDouble(std::string property_name);
	std::string getPropertyAsStringOrDefaultTo(std::string property_name, std::string default_property_value);
	int getPropertyAsIntOrDefaultTo(std::string property_name, int default_property_value);
	bool getPropertyAsBoolOrDefaultTo(std::string property_name, bool default_property_value);
	float getPropertyAsFloatOrDefaultTo(std::string property_name, float default_property_value);
	double getPropertyAsDoubleOrDefaultTo(std::string property_name, double default_property_value);
};

#endif	//	!PROPERTIES_PARSER_H