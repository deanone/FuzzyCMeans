#include "FuzzyCMeans.h"
#include "GenericFunc.h"

#include <string>
#include <iostream>

int main()
{
	std::string dataset_filename = gf::getExecutablePathAndMatchItWithFilename("data.csv");
	std::string properties_fileName = gf::getExecutablePathAndMatchItWithFilename("fcm.properties");
	FuzzyCMeans fcm(dataset_filename, properties_fileName);
	fcm.runFuzzyCMeans();
	fcm.printCentroids();
	fcm.printPartitionMatrix();
	std::cin.get();
	return 0;
}