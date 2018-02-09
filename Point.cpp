#include "Point.h"
#include "MathFunc.h"

#include <iostream>
#include <numeric>

/*!
 * Constructor.
 */
Point::Point() : id(-1)
{
}

Point::Point(const int id, const int k)
{
	this->id = id;
	for (size_t cluster_id = 0; cluster_id < k; ++cluster_id)
	{
		double initial_coefficient = ((double)rand() / (RAND_MAX));
		w_old.push_back(initial_coefficient);
	}
	w_new.assign(k, 0.0);
}

/*!
 * Destructor.
 */
Point::~Point()
{
	if (!values.empty()) values.clear();
	if (!w_old.empty()) w_old.clear();
	if (!w_new.empty()) w_new.clear();
}

/*!
 * Sets the ID of the point.
 */
void Point::setID(const int id)
{
	this->id = id;
}

/*
 * Returns the ID of the point.
 * @return
 */
int Point::getID() const
{
	return id;
}

/*!
 * Add value to the values vector of the point.
 * @param
 */
void Point::addValue(const double value)
{
	values.push_back(value);
}

/*!
 * Get a value from the values vector of the point, for a specific index.
 * @param
 * @return
 */
double Point::getValue(const size_t index)
{
	return (index >= 0 && index < values.size()) ? values[index] : -1.0;	// -1.0 error indicator
}

/*!
 * Get the size of the values vector of the point.
 * @return
 */
size_t Point::getValuesSize()
{
	return values.size();
}

/*!
 * Change a value of the values vector of the point, at a specific index.
 * @param
 * @param
 */
void Point::changeValue(const size_t index, const double newValue)
{
	if (index >= 0 && index < values.size())
		values[index] = newValue;
}

std::vector<double>* Point::getValues()
{
	return &values;
}

void Point::updateWNew(std::vector<double>& w_new)
{
	for (size_t i = 0; i < w_new.size(); ++i)
		this->w_new[i] = w_new[i];
}

bool Point::compareW(const double eps)
{
	double dist = mfnc::computeEuclideanDistance(w_old, w_new);
	if (dist <= eps)
		return true;
	else
		return false;
}

double Point::getWOldValue(const int clusterID)
{
	double w_old_value = -1.0;
	if ((clusterID >= 0) && (clusterID < w_old.size()))
		w_old_value = w_old[clusterID];
	return w_old_value;
}

void Point::updateW()
{
	for (size_t i = 0; i < w_old.size(); ++i)
	{
		w_old[i] = w_new[i];
		w_new[i] = 0.0;
	}
}

void Point::printMembershipCoefficients()
{
	for (size_t i = 0; i < w_old.size(); ++i)
	{
		if (i != (w_old.size() - 1))
			std::cout << w_old[i] * 100.0 << ", ";
		else
			std::cout << w_old[i] * 100.0;
	}
	//std::cout << "," << std::accumulate(w_old.begin(), w_old.end(), 0.0);
	std::cout << std::endl;
}