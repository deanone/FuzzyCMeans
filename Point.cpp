#include "Point.h"
#include "MathFunc.h"

#include <iostream>
#include <numeric>

Point::Point() : ID(-1)
{
}

Point::Point(int ID, int k)
{
	this->ID = ID;
	for (size_t i = 0; i < k; ++i)
	{
		double initialCoefficient = (static_cast<double>(rand()) / (RAND_MAX));
		wOld.push_back(initialCoefficient);
	}
	wNew.assign(k, 0.0);
}

Point::~Point()
{
	if (!values.empty())
	{
		values.clear();	
	}
	if (!wOld.empty())
	{
		wOld.clear();
	}
	if (!wNew.empty())
	{
		wNew.clear();	
	}
}

void Point::setID(int ID)
{
	this->ID = ID;
}

int Point::getID() const
{
	return ID;
}

void Point::addValue(double val)
{
	values.push_back(val);
}

double Point::getValue(size_t index)
{
	if (index >= 0 && index < values.size())
	{
		return values[index];
	}
	else
	{
		return -1.0;	//	-1.0 error indicator
	}
}

size_t Point::getValuesSize()
{
	return values.size();
}

void Point::changeValue(size_t index, double valNew)
{
	if (index >= 0 && index < values.size())
	{
		values[index] = valNew;
	}
}

DoubleVector* Point::getValues()
{
	return &values;
}

void Point::updateWNew(DoubleVector& wNew)
{
	for (size_t i = 0; i < wNew.size(); ++i)
	{
		this->wNew[i] = wNew[i];
	}
}

void Point::updateW()
{
	for (size_t i = 0; i < wOld.size(); ++i)
	{
		wOld[i] = wNew[i];
		wNew[i] = 0.0;
	}
}

bool Point::compareW(double eps)
{
	double dist = mfnc::computeEuclideanDistance(wOld, wNew);
	if (dist <= eps)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

double Point::getWOldValue(int clusterID)
{
	double wOldVal = -1.0;
	if ((clusterID >= 0) && (clusterID < wOld.size())) 
	{
		wOldVal = wOld[clusterID];
	}
	return wOldVal;
}

void Point::printMembershipCoefficients()
{
	for (size_t i = 0; i < wOld.size(); ++i)
	{
		if (i != (wOld.size() - 1)) 
		{
			std::cout << wOld[i]  << ", ";
		}
		else 
		{
			std::cout << wOld[i];
		}
	}
	//std::cout << "," << std::accumulate(w_old.begin(), w_old.end(), 0.0);
	std::cout << std::endl;
}