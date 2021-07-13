#include "FuzzyCMeans.h"
#include "GenericFunc.h"

#include <string>
#include <iostream>

int main()
{
	std::string dataFilename = gf::getExecutablePathAndMatchItWithFilename("data.csv");
	std::string paramsFilename = gf::getExecutablePathAndMatchItWithFilename("fcm.properties");
	FuzzyCMeans fcm(dataFilename, paramsFilename);
	fcm.runFuzzyCMeans();
	fcm.printCentroids();
	fcm.printPartitionMatrix();
	std::cin.get();
	return 0;
}