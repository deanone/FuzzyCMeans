#include "FuzzyCMeans.h"
#include "PropertiesParser.h"
#include "MathFunc.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>

/*!
 * Constructor.
 */
FuzzyCMeans::FuzzyCMeans(std::string dataset_filename, std::string properties_fileName)
{
	srand(static_cast<unsigned int>(time(NULL)));
	PropertiesParser pp(properties_fileName);
	dimension = pp.getPropertyAsIntOrDefaultTo("dimension", 4);
	k = pp.getPropertyAsIntOrDefaultTo("k", 200);
	max_num_of_iterations = pp.getPropertyAsIntOrDefaultTo("max_num_of_iterations", 1000);
	m = pp.getPropertyAsIntOrDefaultTo("m", 2);
	eps = pp.getPropertyAsDoubleOrDefaultTo("eps", 1e-6);
	std::string dataline;
	std::ifstream in;
	in.open(dataset_filename);
	if (in.is_open())
	{
		while (std::getline(in, dataline))
		{
			std::stringstream ss(dataline);
			std::string item;
			std::vector<std::string> items;
			while (getline(ss, item, ','))
				items.push_back(item);
			int ID = std::stoi(items[0]);
			Point point(ID, k);
			// TODO: instead of adding value in each iteration by calling addValue function,
			// initialize values vector in the constructor and then change the values in each iteration
			for (size_t i = 1; i < items.size(); ++i)
				point.addValue(std::stod(items[i]));
			items.clear();
			points.push_back(point);
		}
		in.close();
	}
	for (size_t cluster_id = 0; cluster_id < k; ++cluster_id)
	{
		std::vector<double> initial_centroid;
		initial_centroid.assign(dimension, 0.0);
		Cluster cl(initial_centroid, cluster_id);
		clusters.push_back(cl);
	}
}

/*!
 * Constructor 2.
 */
FuzzyCMeans::FuzzyCMeans(std::string dataset_filename, int dimension_, int k_, int max_num_of_iterations_, int m_, double eps_) :
	dimension(dimension_), k(k_), max_num_of_iterations(max_num_of_iterations_), m(m_), eps(eps_)
{
	srand(static_cast<unsigned int>(time(NULL)));
	std::string dataline;
	std::ifstream in;
	in.open(dataset_filename);
	if (in.is_open())
	{
		while (std::getline(in, dataline))
		{
			std::stringstream ss(dataline);
			std::string item;
			std::vector<std::string> items;
			while (getline(ss, item, ','))
				items.push_back(item);
			int ID = std::stoi(items[0]);
			Point point(ID, k);
			for (size_t i = 1; i < items.size(); ++i)
				point.addValue(std::stod(items[i]));
			items.clear();
			points.push_back(point);
		}
		in.close();
	}
	for (size_t cluster_id = 0; cluster_id < k; ++cluster_id)
	{
		std::vector<double> initial_centroid;
		initial_centroid.assign(dimension, 0.0);
		Cluster cl(initial_centroid, cluster_id);
		clusters.push_back(cl);
	}
}

/*!
 * Destructor.
 */
FuzzyCMeans::~FuzzyCMeans()
{
	if (!points.empty()) points.clear();
	if (!clusters.empty()) clusters.clear();
}

void FuzzyCMeans::computeClusters()
{
	for (size_t cluster_id = 0; cluster_id < k; ++cluster_id)
	{
		std::vector<double> nominator;
		nominator.assign(dimension, 0.0);
		double denominator = 0.0;
		for (size_t point_id = 0; point_id < points.size(); ++point_id)
		{
			double w_old_value = points[point_id].getWOldValue(cluster_id);
			w_old_value = std::pow(w_old_value, m);
			denominator += w_old_value;
			std::vector<double> temp = mfnc::multiplyVectorByConstant(*(points[point_id].getValues()), w_old_value);
			mfnc::addToVector(nominator, temp);
			temp.clear();
		}
		std::vector<double> centroid = mfnc::multiplyVectorByConstant(nominator, 1.0 / denominator);
		clusters[cluster_id].setCentroid(centroid);
	}
}

void FuzzyCMeans::computeNewMembershipCoefficients()
{
	for (size_t point_id = 0; point_id < points.size(); ++point_id)
	{
		std::vector<double> distances;
		for (size_t cluster_id = 0; cluster_id < clusters.size(); ++cluster_id)
		{
			//dist = mfnc::ComputeEuclideanDistance(*(points[point_id].getValues()), *center);
			double dist = mfnc::computeEuclideanDistance(*(points[point_id].getValues()), *(clusters[cluster_id].getCentroid()));
			distances.push_back(dist);
		}
		std::vector<double> w_new;
		for (size_t cluster_id1 = 0; cluster_id1 < clusters.size(); ++cluster_id1)
		{
			double currentClusterDistance = distances[cluster_id1];
			double distancesSum = 0.0;
			for (size_t cluster_id2 = 0; cluster_id2 < clusters.size(); ++cluster_id2)
			{
				double otherClusterDistance = distances[cluster_id2];
				distancesSum += std::pow(currentClusterDistance / otherClusterDistance, 2 / (m - 1));
			}
			w_new.push_back(1.0 / distancesSum);
		}
		distances.clear();
		points[point_id].updateWNew(w_new);
		w_new.clear();
	}
}

void FuzzyCMeans::updateMembershipCoefficients()
{
	for (size_t point_id = 0; point_id < points.size(); ++point_id)
		points[point_id].updateW();
}

/*!
 * Checks if the algorithm converged.
 */
bool FuzzyCMeans::isOver()
{
	bool over = true;
	for (size_t point_id = 0; point_id < points.size(); ++point_id)
	{
		if (!points[point_id].compareW(eps))
		{
			over = false;
			break;
		}
	}
	return over;
}

/*!
 * Runs the Fuzzy c-means routine.
 */
void FuzzyCMeans::runFuzzyCMeans()
{
	for (size_t iter = 0; iter < max_num_of_iterations; ++iter)
	{
		computeClusters();
		computeNewMembershipCoefficients();
		if (isOver())
			break;
		else
			updateMembershipCoefficients();
	}
}

void FuzzyCMeans::printPartitionMatrix()
{
	std::cout << "Partition Matrix:\n\n";
	for (size_t point_id = 0; point_id < points.size(); ++point_id)
		points[point_id].printMembershipCoefficients();
	std::cout << std::endl;
}

void FuzzyCMeans::printCentroids()
{
	std::cout << "Centroids:\n\n";
	for (size_t cluster_id = 0; cluster_id < clusters.size(); ++cluster_id)
		clusters[cluster_id].printCentroid();
	std::cout << std::endl;
}