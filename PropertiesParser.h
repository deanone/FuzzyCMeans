#ifndef PROPERTIES_PARSER_H
#define PROPERTIES_PARSER_H

#include <map>

class PropertiesParser
{
protected:
	
	/*!
	 * A map containing property names as keys and property values as values.
	 */
	std::map<std::string, std::string> propMap;

public:
	/*!
	 * Constructor.
	 */
	PropertiesParser(std::string propertiesFilename);
	
	/*!
	 * Creates the properties map from the properties contained in a file.
	 * @param propertiesFilename the name of the file that contains the properties.
	 */
	void addPropertiesFile(std::string propertiesFilename);
	
	/*!
	 * Checks if a specific property exists in the properties map.
	 * @param propertyName the name of the property to be checked.
	 * @return true if property exists in the properties map, false otherwise.
	 */
	bool propertyExists(std::string propertyName);
	
	/*!
	 * Returns a property as type string.
	 * @param propertyName the name of the property.
	 * @return the string type property.
	 */
	std::string getPropertyAsString(std::string propertyName);
	
	/*!
	 * Returns a property as type int.
	 * @param propertyName the name of the property.
	 * @return the int type property.
	 */
	int getPropertyAsInt(std::string propertyName);
	
	/*!
	 * Returns a property as type bool.
	 * @param propertyName the name of the property.
	 * @return the bool type property.
	 */
	bool getPropertyAsBool(std::string propertyName);
	
	/*!
	 * Returns a property as type float.
	 * @param propertyName the name of the property.
	 * @return the float type property.
	 */
	float getPropertyAsFloat(std::string propertyName);
	
	/*!
	 * Returns a property as type double.
	 * @param propertyName the name of the property.
	 * @return the double type property.
	 */
	double getPropertyAsDouble(std::string propertyName);
	
	/*!
	 * Returns a property as type string, or return a default string type value.
	 * @param propertyName the name of the property.
	 * @param defaultPropertyValue the default value of the property
	 * @return the string type property, or a default string type value.
	 */
	std::string getPropertyAsStringOrDefaultTo(std::string propertyName, std::string defaultPropertyValue);
	
	/*!
	 * Returns a property as type int, or return a default int type value.
	 * @param propertyName the name of the property.
	 * @param defaultPropertyValue the default value of the property
	 * @return the int type property, or a default int type value.
	 */
	int getPropertyAsIntOrDefaultTo(std::string propertyName, int defaultPropertyValue);
	
	/*!
	 * Returns a property as type bool, or return a default bool type value.
	 * @param propertyName the name of the property.
	 * @param defaultPropertyValue the default value of the property
	 * @return the bool type property, or a default bool type value.
	 */
	bool getPropertyAsBoolOrDefaultTo(std::string propertyName, bool defaultPropertyValue);
	
	/*!
	 * Returns a property as type float, or return a default float type value.
	 * @param propertyName the name of the property.
	 * @param defaultPropertyValue the default value of the property
	 * @return the int float property, or a default float type value.
	 */
	float getPropertyAsFloatOrDefaultTo(std::string propertyName, float defaultPropertyValue);
	
	/*!
	 * Returns a property as type double, or return a default double type value.
	 * @param propertyName the name of the property.
	 * @param defaultPropertyValue the default value of the property
	 * @return the double type property, or a default double type value.
	 */
	double getPropertyAsDoubleOrDefaultTo(std::string propertyName, double defaultPropertyValue);
};

#endif	//	PROPERTIES_PARSER_H