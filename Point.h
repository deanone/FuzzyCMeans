#ifndef POINT_H
#define POINT_H

#include <vector>

class Point
{
	int id;
	std::vector<double> values;
	std::vector<double> w_old;	// cluster membership coefficients
	std::vector<double> w_new;	// cluster membership coefficients
public:
	Point();
	Point(const int id, const int k);
	~Point();
	void setID(const int id);
	int getID() const;
	void addValue(const double value);
	double getValue(const size_t index);
	size_t getValuesSize();
	void changeValue(const size_t index, const double new_value);
	void updateWNew(std::vector<double>& w_new);
	void updateW();
	std::vector<double>* getValues();
	double getWOldValue(const int cluster_id);
	bool compareW(const double eps);
	void printMembershipCoefficients();
};

#endif	//	!POINT_H