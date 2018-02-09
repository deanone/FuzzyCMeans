#include "Cluster.h"

#include <iostream>

/*!
 * Constructor.
 * @param
 * @param
 */
Cluster::Cluster(std::vector<double>& centroid, int id_) : id(id_)
{
	for (size_t i = 0; i < centroid.size(); ++i)
		this->centroid.push_back(centroid[i]);
}

/*!
 * Destructor.
 */
Cluster::~Cluster()
{
	if (!centroid.empty()) centroid.clear();
}

/*!
 * Sets the ID of the cluster.
 * @param
 */
void Cluster::setID(const int id)
{
	this->id = id;
}

/*!
 * Returns the ID of the cluster.
 * @return
 */
int Cluster::getID() const
{
	return id;
}

/*!
 * Sets the centroid of the cluster.
 * @param
 */
void Cluster::setCentroid(std::vector<double>& centroid)
{
	for (size_t i = 0; i < centroid.size(); ++i)
		this->centroid[i] =centroid[i];
}

/*!
 * Returns centroid of the cluster.
 * @return
 */
std::vector<double>* Cluster::getCentroid()
{
	return &centroid;
}

void Cluster::printCentroid()
{
	for (size_t i = 0; i < centroid.size(); ++i)
	{
		if (i != (centroid.size() - 1))
			std::cout << centroid[i] << ", ";
		else
			std::cout << centroid[i];
	}
	std::cout << std::endl;
}