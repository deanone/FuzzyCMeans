#ifndef FUZZYCMEANS_H
#define FUZZYCMEANS_H

#include "DataTypes.h"
#include "Point.h"
#include "Cluster.h"

class FuzzyCMeans
{
	int	dimension;
	int k;
	int max_num_of_iterations;
	int m;
	double eps;
public:
	std::vector<Point> points;
	std::vector<Cluster> clusters;
public:

	/*!
	 * Constructor 1.
	 */
	FuzzyCMeans(std::string dataset_filename, std::string properties_fileName);
	
	/*!
	 * Constructor 2.
	 */
	FuzzyCMeans(std::string dataset_filename, int dimension_, int k_, int max_num_Of_iterations_, int m_, double eps_);
	
	/*!
	 * Destructor.
	 */
	~FuzzyCMeans();
	
	void computeClusters();
	void computeNewMembershipCoefficients();
	void updateMembershipCoefficients();
	bool isOver();
	void runFuzzyCMeans();
	void printPartitionMatrix();
	void printCentroids();
	double computeObjectiveFunction();
};

#endif	//	FUZZYCMEANS_H