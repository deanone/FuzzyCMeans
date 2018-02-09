#ifndef FuzzyCMeans_H
#define FuzzyCMeans_H

#include "Point.h"
#include "Cluster.h"

// Implementation of the Fuzzy c-means clustering algorithm.
// https://en.wikipedia.org/wiki/Fuzzy_clustering
// author: asal
// date: 09/02/2018

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
	FuzzyCMeans(std::string dataset_filename, std::string properties_fileName);
	FuzzyCMeans(std::string dataset_filename, int dimension_, int k_, int max_num_Of_iterations_, int m_, double eps_);
	~FuzzyCMeans();
	
	void computeClusters();
	void computeNewMembershipCoefficients();
	void updateMembershipCoefficients();
	bool isOver();
	void runFuzzyCMeans();
	void printPartitionMatrix();
	void printCentroids();
};

#endif	//	!FuzzyCMeans_H