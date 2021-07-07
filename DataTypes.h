#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#include <unistd.h>

// STL
#include <vector>
#include <map>
#include <algorithm> 
#include <numeric>
#include <complex>
#include <functional>

// typedefs
typedef std::vector<float> FloatVector;
typedef std::vector<FloatVector> FloatVector2D;
typedef std::vector<double> DoubleVector;
typedef std::vector<DoubleVector> DoubleVector2D;
typedef std::vector<int> IntVector;
typedef std::vector<IntVector> IntVector2D;
typedef std::vector<std::string> StringVector;
typedef std::vector<StringVector> StringVector2D;
typedef std::pair<int,int> IntIntPair;
typedef std::pair<int,float> IntFloatPair;
typedef std::map<int,int> IntIntMap;
typedef std::map<int,IntVector> IntIntVectorMap;
typedef std::map<int,FloatVector> IntFloatVectorMap;

#endif	// DATATYPES_H