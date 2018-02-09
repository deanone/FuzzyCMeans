/*!
 * PropertiesParser.cpp: implementation of the PropertiesParser class.
 */

#include "PropertiesParser.h"
#include <fstream>
#include <sstream>

/*!
 * Constructor. Initializes the parser parsing the properties file and
 * reading all properties in the \c properties_map.
 *
 * @param propertiesFilename the filename of the properties file.
 */
PropertiesParser::PropertiesParser(std::string properties_filename)
{
	addPropertiesFile(properties_filename);
}

/*!
 * Destructor. Destroys the map object properties_map of the class and frees the corresponding memory.
 */
PropertiesParser::~PropertiesParser()
{
	properties_map.clear();
}

/*!
 * Parses a properties file and reads all properties in the \c properties_map.
 * It may be used consecutively to parse multiple properties files.
 *
 * @param propertiesFilename the filename of the properties file.
 */
void PropertiesParser::addPropertiesFile(std::string properties_filename)
{
	std::ifstream properties_file_stream(properties_filename);
	std::string line;
	if (properties_file_stream.is_open())
	{
		if (properties_file_stream.good())
		{
			while (properties_file_stream.eof() == false)
			{
				line.clear();
				std::getline(properties_file_stream, line);
				if (line.length() > 0 && line[0] != '#')	/*! line is not a comment line*/
				{
					std::string property_name;
					std::string property_value;
					std::stringstream ss(line);
					char c;//c used to eat the '=' character
					ss >> property_name >> c >> property_value;
					properties_map[property_name] = property_value;
				}
			}
		}
		properties_file_stream.close();
	}
}

/*!
 * Checks if a property exists.
 *
 * @param property_name the name of the property to be checked.
 * @return \c true if property exists, \c false otherwise.
 */
bool PropertiesParser::propertyExists(std::string property_name)
{
	return (!(properties_map.find(property_name) == properties_map.end()));
}

/*!
 * Returns the string value of a property.
 *
 * @param property_name the name of the property of which the value is returned.
 * @return a string value for the property.
 */
std::string PropertiesParser::getPropertyAsString(std::string property_name)
{
	return properties_map[property_name];
}

/*!
 * Returns the integer value of a property.
 *
 * @param property_name the name of the property of which the value is returned.
 * @return an integer value for the property.
 */
int PropertiesParser::getPropertyAsInt(std::string property_name)
{
	int property_value = 0;
	std::stringstream str_stream(properties_map[property_name]);
	str_stream >> property_value;
	return property_value;
}

/*!
 * Returns the boolean value of a property.
 *
 * @param property_name the name of the property of which the value is returned.
 * @return a boolean value for the property.
 */
bool PropertiesParser::getPropertyAsBool(std::string property_name)
{
	bool property_value = true;
	property_value = (properties_map[property_name] == "true");
	return property_value;
}

/*!
 * Returns the float value of a property.
 *
 * @param property_name the name of the property of which the value is returned.
 * @return a float value for the property.
 */
float PropertiesParser::getPropertyAsFloat(std::string property_name)
{
	float property_value = 0.0f;
	std::stringstream str_stream(properties_map[property_name]);
	str_stream >> property_value;
	return property_value;
}

/*!
 * Returns the double value of a property.
 *
 * @param property_name the name of the property of which the value is returned.
 * @return a double value for the property.
 */
double PropertiesParser::getPropertyAsDouble(std::string property_name)
{
	double property_value = 0.0;
	std::stringstream str_stream(properties_map[property_name]);
	str_stream >> property_value;
	return property_value;
}

/*!
 * Returns the string value of a property, if it exists, or a default value if
 * the property does not exist.
 *
 * @param property_name the name of the property of which the value is returned.
 * @param defaultproperty_value the default property value.
 * @return a string value for the property.
 */
std::string PropertiesParser::getPropertyAsStringOrDefaultTo(std::string property_name, std::string default_property_value)
{
	return propertyExists(property_name) ? getPropertyAsString(property_name) : default_property_value;
}

/*!
 * Returns the integer value of a property, if it exists, or a default value if
 * the property does not exist.
 *
 * @param property_name the name of the property of which the value is returned.
 * @param defaultproperty_value the default property value.
 * @return an integer value for the property.
 */
int PropertiesParser::getPropertyAsIntOrDefaultTo(std::string property_name, int default_property_value)
{
	return propertyExists(property_name) ? getPropertyAsInt(property_name) : default_property_value;
}

/*!
 * Returns the boolean value of a property, if it exists, or a default value if
 * the property does not exist.
 *
 * @param property_name the name of the property of which the value is returned.
 * @param defaultproperty_value the default property value.
 * @return a boolean value for the property.
 */
bool PropertiesParser::getPropertyAsBoolOrDefaultTo(std::string property_name, bool default_property_value)
{
	return propertyExists(property_name) ? getPropertyAsBool(property_name) : default_property_value;
}

/*!
 * Returns the float value of a property, if it exists, or a default value if
 * the property does not exist.
 *
 * @param property_name the name of the property of which the value is returned.
 * @param defaultproperty_value the default property value.
 * @return a float value for the property.
 */
float PropertiesParser::getPropertyAsFloatOrDefaultTo(std::string property_name, float default_property_value)
{
	return propertyExists(property_name) ? getPropertyAsFloat(property_name) : default_property_value;
}

/*!
 * Returns the double value of a property, if it exists, or a default value if
 * the property does not exist.
 * 
 * @param property_name the name of the property of which the value is returned.
 * @param defaultproperty_value the default property value.
 * @return a double value for the property.
 */
double PropertiesParser::getPropertyAsDoubleOrDefaultTo(std::string property_name, double default_property_value)
{
	return propertyExists(property_name) ? getPropertyAsDouble(property_name) : default_property_value;
}