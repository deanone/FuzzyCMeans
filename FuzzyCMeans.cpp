#include "FuzzyCMeans.h"
#include "PropertiesParser.h"
#include "MathFunc.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>

FuzzyCMeans::FuzzyCMeans(std::string dataFilename, std::string paramsFilename)
{
	// reproducible results
	srand(static_cast<unsigned int>(time(NULL)));

	// reading properties from file
	PropertiesParser pp(paramsFilename);
	dimension = pp.getPropertyAsIntOrDefaultTo("dimension", 4);
	k = pp.getPropertyAsIntOrDefaultTo("k", 200);
	maxNumOfIterations = pp.getPropertyAsIntOrDefaultTo("maxNumOfIterations", 1000);
	m = pp.getPropertyAsIntOrDefaultTo("m", 2);
	eps = pp.getPropertyAsDoubleOrDefaultTo("eps", 1e-6);
	
	std::string dataline = "";
	std::ifstream in;
	in.open(dataFilename);
	if (in.is_open())
	{
		while (std::getline(in, dataline))
		{
			std::stringstream ss(dataline);
			std::string item = "";
			StringVector items;
			while (getline(ss, item, ','))	// comma-separated values
			{
				items.push_back(item);
			}
			
			int ID = std::stoi(items[0]);
			
			Point point(ID, k);
			for (size_t i = 1; i < items.size(); ++i) 
			{
				point.add(std::stod(items[i]));
			}
			items.clear();

			points.push_back(point);
		}
		in.close();
	}

	for (size_t clusterID = 0; clusterID < k; ++clusterID)
	{
		DoubleVector initialCentroid;
		initialCentroid.assign(dimension, 0.0);
		Cluster cl(initialCentroid, clusterID);
		clusters.push_back(cl);
	}
}

FuzzyCMeans::FuzzyCMeans(std::string dataFilename, int dimension_, int k_, int maxNumOfIterations_, int m_, double eps_) :
	dimension(dimension_), k(k_), maxNumOfIterations(maxNumOfIterations_), m(m_), eps(eps_)
{
	// reproducible results
	srand(static_cast<unsigned int>(time(NULL)));
	
	std::string dataline = "";
	std::ifstream in;
	in.open(dataFilename);
	if (in.is_open())
	{
		while (std::getline(in, dataline))
		{
			std::stringstream ss(dataline);
			std::string item;
			StringVector items;
			while (getline(ss, item, ','))	// comma-separated values
			{
				items.push_back(item);
			}

			int ID = std::stoi(items[0]);
			
			Point point(ID, k);
			for (size_t i = 1; i < items.size(); ++i) 
			{
				point.add(std::stod(items[i]));
			}
			
			items.clear();
			
			points.push_back(point);
		}
		in.close();
	}

	for (size_t clusterID = 0; clusterID < k; ++clusterID)
	{
		DoubleVector initialCentroid;
		initialCentroid.assign(dimension, 0.0);
		Cluster cl(initialCentroid, clusterID);
		clusters.push_back(cl);
	}
}

FuzzyCMeans::~FuzzyCMeans()
{
	if (!points.empty())
	{
		points.clear();
	}
	if (!clusters.empty()) 
	{
		clusters.clear();
	}
}

void FuzzyCMeans::computeClusters()
{
	for (size_t clusterID = 0; clusterID < k; ++clusterID)
	{
		DoubleVector nominator;
		nominator.assign(dimension, 0.0);
		double denominator = 0.0;
		for (size_t pointID = 0; pointID < points.size(); ++pointID)
		{
			double wOldValue = points[pointID].getWOldValue(clusterID);
			wOldValue = std::pow(wOldValue, m);
			denominator += wOldValue;
			DoubleVector temp = mfnc::multiplyVectorByConstant(*(points[pointID].getValues()), wOldValue);
			mfnc::addToVector(nominator, temp);
			temp.clear();
		}
		DoubleVector centroid = mfnc::multiplyVectorByConstant(nominator, 1.0 / denominator);
		clusters[clusterID].setCentroid(centroid);
	}
}

void FuzzyCMeans::computeNewMembershipCoefficients()
{
	for (size_t pointID = 0; pointID < points.size(); ++pointID)
	{
		DoubleVector distances;
		for (size_t clusterID = 0; clusterID < clusters.size(); ++clusterID)
		{
			double dist = mfnc::computeEuclideanDistance(*(points[pointID].getValues()), *(clusters[clusterID].getCentroid()));
			distances.push_back(dist);
		}

		DoubleVector wNew;
		for (size_t firstOtherClusterID = 0; firstOtherClusterID < clusters.size(); ++firstOtherClusterID)
		{
			double currentClusterDistance = distances[firstOtherClusterID];
			double distancesSum = 0.0;
			for (size_t secondOtherClusterID = 0; secondOtherClusterID < clusters.size(); ++secondOtherClusterID)
			{
				double otherClusterDistance = distances[secondOtherClusterID];
				distancesSum += std::pow(currentClusterDistance / otherClusterDistance, 2 / (m - 1));
			}
			wNew.push_back(1.0 / distancesSum);
		}
		distances.clear();
		points[pointID].updateWNew(wNew);
		wNew.clear();
	}
}

void FuzzyCMeans::updateMembershipCoefficients()
{
	for (size_t pointID = 0; pointID < points.size(); ++pointID)
	{
		points[pointID].updateW();
	}
}

bool FuzzyCMeans::isOver()
{
	bool over = true;
	for (size_t pointID = 0; pointID < points.size(); ++pointID)
	{
		if (!points[pointID].compareW(eps))
		{
			over = false;
			break;
		}
	}
	return over;
}

void FuzzyCMeans::runFuzzyCMeans()
{
	int start = clock();
	size_t iter = 0;
	double objectiveValue = 0.0;
	for (iter = 0; iter < maxNumOfIterations; ++iter)
	{
		objectiveValue = computeObjectiveFunction();
		std::cout << "Iteration count = " << iter << ", obj. fcn = " << objectiveValue << std::endl;
		computeClusters();
		computeNewMembershipCoefficients();
		if (isOver())
		{
			break;
		}
		else
		{
			updateMembershipCoefficients();
		}
	}
	int stop = clock();

	double elapsedTime = (stop - start) / static_cast<double>(CLOCKS_PER_SEC);
	
	std::cout << "Fuzzy c-means finished after " << (iter + 1) << " iteration(s) (" << elapsedTime << " sec.).\n\n";
}

void FuzzyCMeans::printPartitionMatrix()
{
	std::cout << "Partition Matrix:\n\n";
	for (size_t pointID = 0; pointID < points.size(); ++pointID)
	{
		points[pointID].printMembershipCoefficients();
	}
	std::cout << std::endl;
}

void FuzzyCMeans::printCentroids()
{
	std::cout << "Centroids:\n\n";
	for (size_t clusterID = 0; clusterID < clusters.size(); ++clusterID)
	{
		clusters[clusterID].printCentroid();
	}
	std::cout << std::endl;
}

double FuzzyCMeans::computeObjectiveFunction()
{
	double objectiveValue = 0.0;
	for (size_t pointID = 0; pointID < points.size(); ++pointID)
	{
		for (size_t clusterID = 0; clusterID < clusters.size(); ++clusterID)
		{
			double dist = mfnc::computeEuclideanDistance(*(points[pointID].getValues()), *(clusters[clusterID].getCentroid()));
			dist = std::pow(dist, 2.0);
			objectiveValue += (std::pow(points[pointID].getWOldValue(clusterID), m) * dist);
		}
	}
	return objectiveValue;
}