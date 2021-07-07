#ifndef POINT_H
#define POINT_H

#include "DataTypes.h"

class Point
{
	int ID;
	DoubleVector values;
	
	/*! cluster membership coefficients */
	DoubleVector wOld;

	/*! cluster membership coefficients */
	DoubleVector wNew;	

public:

	/*!
 	 * Default constructor.
 	 */
	Point();

	/*!
 	 * Constructor.
 	 * @param ID the ID of the Point.
 	 * @param k the number of clusters.
 	 */
	Point(int ID, int k);
	
	/*!
 	 * Destructor.
 	 */
	~Point();

	/*! 
	 * Sets the ID of the Point.
	 * @param ID the ID of the Point.
	 */
	void setID(int ID);

	/*!
	 * Returns the ID of the Point. 
	 * @return the ID of the Point.
	 */
	int getID() const;

	/*!
 	 * Adds a value to the vector of values of the Point.
 	 * @param val the value to be added.
 	 */
	void addValue(double val);

	/*!
 	 * Returns a specific value from the vector of values of the Point.
 	 * @param index the index of the specific value.
 	 * @return the specific value.
 	 */
	double getValue(size_t index);
	
	/*!
	 * Returns the size of the vector of values of the Point.
	 * @return the size of the vector of values of the Point.
	 */
	size_t getValuesSize();

	/*!
	 * Changes a specific value of the vector of values of the Point.
	 * @param index the index of the specific value
	 * @param valNew the new value.
	 */
	void changeValue(size_t index, double valNew);
	
	/*!
	 * Returns the vector of values of the Point.
	 * @return the vector of values of the Point.
	 */
	DoubleVector* getValues();

		
	/*!
	 * Updates wNew of the Point.
	 * @param wNew the new wNew of the Point.
	 */
	void updateWNew(DoubleVector& wNew);
	
	/*!
	 * Updates both wOld and wNew of the Point.
	 */
	void updateW();
	
	/*!
	 * Compares wOld and wNew of the Point based on their Euclidean distance.
	 * @param eps the distance threshold under which wOld and wNew are considered equal. 
	 */
	bool compareW(double eps);

	/*!
	 * Returns a specific value of wOld.
	 * @param clusterID the index for which the value of wOld is requested.
	 * @return the value of wOld.
	 */
	double getWOldValue(int clusterID);
	
	/*!
	 * Prints to the standard output the membership coefficients of the Point.
	 */
	void printMembershipCoefficients();
};

#endif	//	POINT_H