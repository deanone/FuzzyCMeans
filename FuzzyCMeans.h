#ifndef FUZZYCMEANS_H
#define FUZZYCMEANS_H

#include "DataTypes.h"
#include "Point.h"
#include "Cluster.h"

class FuzzyCMeans
{
	/*! 
	 * The dimension of the input data (i.e., number of features).
	 */
	int	dimension;

	/*! 
	 * The number of clusters. 
	 */
	int k;

	/*! 
	 * 
	 * The maximum number of iterations for the algorithm to converge.
	 */
	int maxNumOfIterations;

	/*! 
	 * Fuzzifier.
	 */

	int m;
	
	/*! The threshold controlling the convergence of the algorithm.
	 * 
	 */
	double eps;

public:
	/*! 
	 * Data to be clustered.
	 */
	std::vector<Point> points;
	
	/*! 
	 * The clusters to be constructed 
	 */
	std::vector<Cluster> clusters;

public:

	/*!
 	 * Constructor 1.
 	 * @param dataFilename the name of the file in which the data to be clustered are stored.
 	 * @param paramsFilename the name of the configuration file.
 	 */
	FuzzyCMeans(std::string dataFilename, std::string paramsFilename);
	
	/*!
 	 * Constructor 2.
 	 * @param dataFilename the name of the file in which the data to be clustered are stored.
 	 * @param paramsFilename the name of the configuration file.
 	 */
	FuzzyCMeans(std::string dataFilename, int dimension_, int k_, int maxNumOfIterations_, int m_, double eps_);
	
	/*!
	 * Destructor.
	 */
	~FuzzyCMeans();
	
	/*!
	 * It computes the clusters in every iteration of the algorithm.
	 */
	void computeClusters();

	/*!
	 * It computes the membership coefficients of points to clusters in every iteration of the algorithm.
	 */
	void computeNewMembershipCoefficients();

	/*!
	 * It updates the membership coefficients of points to clusters in every iteration of the algorithm.
	 */
	void updateMembershipCoefficients();
	
	/*!
	 * It checks if the algorithm converged.
	 * @return true if the algorithm converged, false otherwise.
	 */
	bool isOver();

	/*!
 	 * It runs the Fuzzy c-means routine.
 	 */
	void runFuzzyCMeans();

	/*!
 	 * It prints the partition matrix to the standard output.
 	 */
	void printPartitionMatrix();

	/*!
 	 * It prints the centroids to the standard output.
 	 */
	void printCentroids();

	/*!
 	 * It computes the value of the objective function that controls the convergence of the algorithm.
 	 */
	double computeObjectiveFunction();
};

#endif	//	FUZZYCMEANS_H