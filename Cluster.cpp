#include "Cluster.h"

#include <iostream>

Cluster::Cluster(DoubleVector& centroid, int ID)
{
	this->ID = ID;
	for (size_t i = 0; i < centroid.size(); ++i)
	{
		this->centroid.push_back(centroid[i]);
	}
}

Cluster::~Cluster()
{
	if (!centroid.empty())
	{
		centroid.clear();
	}
}

void Cluster::setID(int ID)
{
	this->ID = ID;
}

int Cluster::getID() const
{
	return ID;
}

void Cluster::setCentroid(DoubleVector& centroid)
{
	for (size_t i = 0; i < centroid.size(); ++i) 
	{
		this->centroid[i] = centroid[i];
	}
}

DoubleVector* Cluster::getCentroid()
{
	return &centroid;
}

void Cluster::printCentroid()
{
	for (size_t i = 0; i < centroid.size(); ++i)
	{
		if (i != (centroid.size() - 1)) 
		{
			std::cout << centroid[i] << ", ";
		}
		else 
		{
			std::cout << centroid[i];
		}
	}
	std::cout << std::endl;
}