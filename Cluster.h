#ifndef CLUSTER_H
#define CLUSTER_H

#include "Point.h"

class Cluster
{
	int id;
public:
	std::vector<double> centroid;
public:
	Cluster(std::vector<double>& centroid, int id_);
	~Cluster();
	void setID(const int id);
	int getID() const;
	void setCentroid(std::vector<double>& centroid);
	std::vector<double>* getCentroid();
	void printCentroid();
};

#endif	//	!CLUSTER_H