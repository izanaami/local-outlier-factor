#include <iostream>
#include "iomanip"
#include <vector>
#include "point.h"
#include "lof.h"

using namespace std;

void main1(){
	/*
	CPoint point1(4, (double)1, (double)  2, (double) 4, (double) 3);
	CPoint point2(4, (double)2, (double)  2, (double) 2, (double) 3);
	CPoint point3(4, (double)3, (double)  32, (double) 3, (double) 3);
	CPoint point4(4, (double)2, (double)  2, (double)20, (double) 3);
	CPoint point5(4, (double)21, (double)  1, (double) 2, (double) 1);
	CPoint point6(4, (double)11,(double) 12, (double)12, (double)13);
	CPoint point7(4, (double)2, (double)2, (double)2, (double)3);*/
	CPoint point1(1, (double)4);
	CPoint point2(1, (double)4);
	CPoint point3(1, (double)1);
	CPoint point4(1, (double)3);
	CPoint point5(1, (double)1);
	CPoint point6(1, (double)4);
	CPoint point7(1, (double)3);
	vector<CPoint> vec_Instances;
	vec_Instances.push_back(point1);
	vec_Instances.push_back(point2);
	vec_Instances.push_back(point3);
	vec_Instances.push_back(point4);
	vec_Instances.push_back(point5);
	vec_Instances.push_back(point6);
	vec_Instances.push_back(point7);
	/*
	LOF lof(vec_Instances, true);

	lof.ComputeInstanceAttributeBounds();
	lof.debug_printout();
	
	vector<CPoint> vec_distances;
	double a = k_distance(1, point1, vec_Instances, &vec_distances);
	*/
	/*
	vector<CPoint>::iterator it, it1;
	for (it = ++vec_Instances.begin(); it != vec_Instances.end();)
	{
		it1 = find(vec_Instances.begin(), it, *it);
		if (it1 != it)
			it = vec_Instances.erase(it);
		else
			it++;
	}*/
	/*
	std::vector<CPoint> vec_InstancesWithourNeighbour = vec_Instances;
	// instances_withour_neighbour = set(instaces)	去除重复的instance
	for (int i = 0; i < vec_InstancesWithourNeighbour.size(); i++)
	{
		for (int j = i + 1; j < vec_InstancesWithourNeighbour.size(); j++)
		{
			if (IsSame(vec_InstancesWithourNeighbour.at(j), vec_InstancesWithourNeighbour.at(i)))
				// 删除第j个元素
				vec_InstancesWithourNeighbour.erase(vec_InstancesWithourNeighbour.begin() + j);
		}
	}
	cout << vec_InstancesWithourNeighbour.size();
	cout << vec_InstancesWithourNeighbour.at(0).GetValue(0);
	cout << vec_InstancesWithourNeighbour.at(1).GetValue(0);
	cout << vec_InstancesWithourNeighbour.at(2).GetValue(0);
	*/
	system("pause");
}

void main(){
	vector<CPoint> instances;
	instances.push_back(CPoint(2,  -4.8447532242074978   ,  -5.6869538132901658   ));
	instances.push_back(CPoint(2,  1.7265577109364076    ,  -2.5446963280374302   ));
	instances.push_back(CPoint(2,  -1.9885982441038819   ,  1.705719643962865     ));
	instances.push_back(CPoint(2,  -1.999050026772494    ,  -4.0367551415711844   ));
	instances.push_back(CPoint(2,  -2.0550860126898964   ,  -3.6247409893236426   ));
	instances.push_back(CPoint(2,  -1.4456945632547327   ,  -3.7669258809535102   ));
	instances.push_back(CPoint(2,  -4.6676062022635554   ,  1.4925324371089148    ));
	instances.push_back(CPoint(2,  -3.6526420667796877   ,  -3.5582661345085662   ));
	instances.push_back(CPoint(2,  6.4551493172954029    ,  -0.45434966683144573  ));
	instances.push_back(CPoint(2,  -0.56730591589443669  ,  -5.5859532963153349   ));
	instances.push_back(CPoint(2,  -5.1400897823762239   ,  -1.3359248994019064   ));
	instances.push_back(CPoint(2,  5.2586932439960243    ,  0.032431285797532586  ));
	instances.push_back(CPoint(2,  6.3610915734502838    ,  -0.99059648246991894  ));
	instances.push_back(CPoint(2,  -0.31086913190231447  ,  -2.8352818694180644   ));
	instances.push_back(CPoint(2,  1.2288582719783967    ,  -1.1362795178325829   ));
	instances.push_back(CPoint(2,  -0.17986204466346614  ,  -0.32813130288006365  ));
	instances.push_back(CPoint(2,  2.2532002509929216    ,  -0.5142311840491649   ));
	instances.push_back(CPoint(2,  -0.75397166138399296  ,  2.2465141276038754    ));
	instances.push_back(CPoint(2,  1.9382517648161239    ,  -1.7276112460593251   ));
	instances.push_back(CPoint(2,  1.6809250808549676    ,  -2.3433636210337503   ));
	instances.push_back(CPoint(2,  0.68466572523884783   ,  1.4374914487477481    ));
	instances.push_back(CPoint(2,  2.0032364431791514    ,  -2.9191062023123635   ));
	instances.push_back(CPoint(2,  -1.7565895138024741   ,  0.96995712544043267   ));
	instances.push_back(CPoint(2,  3.3809644295064505    ,  6.7497121359292684    ));
	instances.push_back(CPoint(2,  -4.2764152718650896   ,  5.6551328734397766    ));
	instances.push_back(CPoint(2,  -3.6347215445083019   ,  -0.85149861984875741  ));
	instances.push_back(CPoint(2,  -5.6249411288060385   ,  -3.9251965527768755   ));
	instances.push_back(CPoint(2,  4.6033708001912093    ,  1.3375110154658127    ));
	instances.push_back(CPoint(2,  -0.685421751407983    ,  -0.73115552984211407  ));
	instances.push_back(CPoint(2,  -2.3744241805625044   ,  1.3443896265777866    ));

	LOF lof(instances, true);

	vector<outlier>out;
	out = GetOutliers(5, instances);

	for (int i = 0; i < out.size(); i++)
	{
		cout << setiosflags(ios::fixed) << setprecision(20) << out.at(i).lof << " ( ";
		cout << setiosflags(ios::fixed) << setprecision(20) << out.at(i).instance.GetValue(0) << " , ";
		cout << setiosflags(ios::fixed) << setprecision(20) << out.at(i).instance.GetValue(1) << " ) "<<endl;
	}

	system("pause");
}