#include "FuzzyCMeans.h"
#include <string>
#include <iostream>

int main()
{
	std::string dataset_filename = "C:\\Users\\asal\\Desktop\\testFuzzyCMeans\\data.csv";
	std::string properties_fileName = "C:\\Users\\asal\\Desktop\\testFuzzyCMeans\\fcm.properties";
	FuzzyCMeans fcm(dataset_filename, properties_fileName);
	fcm.runFuzzyCMeans();
	fcm.printCentroids();
	fcm.printPartitionMatrix();
	return 0;
}