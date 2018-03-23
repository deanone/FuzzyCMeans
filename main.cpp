#include <string>
#include <iostream>

#include "FuzzyCMeans.h"
#include "GenericFunc.h"

int main()
{
	std::string dataset_filename = gnfnc::getExecutablePathAndMatchItWithFilename("data.csv");
	std::string properties_fileName = gnfnc::getExecutablePathAndMatchItWithFilename("fcm.properties");
	FuzzyCMeans fcm(dataset_filename, properties_fileName);
	fcm.runFuzzyCMeans();
	fcm.printCentroids();
	//fcm.printPartitionMatrix();
	std::cin.get();
	return 0;
}