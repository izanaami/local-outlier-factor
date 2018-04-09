#ifndef LOF_H
#define LOF_H

#include <math.h>
#include "point.h"
#include <iostream>
#include <map>
#include <iterator>

class LOF	
	/*	local outlier factor
	*/
{
//public:
private:
	std::vector<CPoint> vec_Instances; 
	std::vector<double> vec_MaxAttributeValue;
	std::vector<double> vec_MinAttributeValue;
	
	bool normalize;
	int n_InstanceDimension;

	void NormalizeInstances();
	CPoint NormalizeInstance(CPoint);
	void ComputeInstanceAttributeBounds();

public:
	LOF(std::vector<CPoint>, bool);
	~LOF();

	double LocalOutlierFactor(int, CPoint);
	void debug_printout();
};

double k_distance(int, CPoint, std::vector<CPoint>, std::vector<CPoint>*);

double ReachabilityDist(int, CPoint, CPoint, std::vector<CPoint>);

double LocalReachabilityDensity(int, CPoint, std::vector<CPoint>);

struct outlier
{
	double lof;			// lof分值
	CPoint instance;	// CPoint类的坐标信息
	int index;			// 该instance的下标
};

std::vector<outlier> GetOutliers(int, std::vector<CPoint>);

#endif 