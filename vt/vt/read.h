#include<iostream>
#include<Eigen/Core>
#include <string>
#include <fstream>
#include<sstream>
#include <vector>

using namespace Eigen;
using namespace std;


void readObjFile(std::string filename, MatrixXd& V, MatrixXi& F) {
	std::vector<std::array<float, 3> > pts;
	std::vector<std::array<int, 3> > facets;
	pts.clear();
	facets.clear();
	std::fstream pointCouldStream;
	pointCouldStream.open(filename.c_str(), std::ifstream::in);
	if (!pointCouldStream.is_open())
	{
		std::cout << "Error opening pointCould file\n"; exit(1);
	}
	cout << "开始！" << endl;
	while (!pointCouldStream.eof())
	{
		char tmpLine[400] = { 0 };
		pointCouldStream.getline(tmpLine, 200);
		std::istringstream  istr;
		istr.str(tmpLine);
		std::string lineType;
		istr >> lineType;

		float XCoord, YCoord, ZCoord, garbageVal;
		int  p1, p2, p3;
		if (lineType.compare("v") == 0) {
			istr >> XCoord >> YCoord >> ZCoord;
			pts.push_back(std::array<float, 3>{ {XCoord, YCoord, ZCoord}});
		}
		else if (lineType.compare("f") == 0) {//只考虑单存顶点的情况
			istr >> p1 >> p2 >> p3;
			facets.push_back(std::array<int, 3>{ {p1 - 1, p2 - 1, p3 - 1}});
		}
	}
	pointCouldStream.close();
	int row = pts.size();
	V = MatrixXd::Random(row, 3);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 3; j++) {
			V(i,j) = pts[i][j];
		}
	}
	row = facets.size();
	F= MatrixXi::Random(row, 3);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 3; j++) {
			F(i, j) = facets[i][j];
		}
	}

	cout << V << endl;
	cout << F << endl;



}
