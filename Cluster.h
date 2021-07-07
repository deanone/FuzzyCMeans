#ifndef CLUSTER_H
#define CLUSTER_H

#include "DataTypes.h"
#include "Point.h"

class Cluster
{
	int ID;
public:
	DoubleVector centroid;
public:
	
	/*!
 	 * Constructor.
 	 * @param centroid the centroid of the Cluster.
 	 * @param ID the ID of the cluster.
 	 */
	Cluster(DoubleVector& centroid, int ID);
	
	/*!
 	 * Destructor.
 	 */
	~Cluster();

	/*! 
	 * Sets the ID of the Cluster.
	 * @param ID the ID of the Cluster.
	 */
	void setID(int ID);
	
	/*!
	 * Returns the ID of the Cluster. 
	 * @return the ID of the Cluster.
	 */
	int getID() const;
	
	/*! 
	 * Sets the centroid of the Cluster.
	 * @param centroid the centroid of the Cluster.
	 */
	void setCentroid(DoubleVector& centroid);
	
	/*!
	 * Returns the centroid of the Cluster. 
	 * @return the centroid of the Cluster.
	 */
	DoubleVector* getCentroid();
	
	/*!
	 * Prints to the standard output the centroid of the Cluster. 
	 */
	void printCentroid();
};

#endif	//	CLUSTER_H