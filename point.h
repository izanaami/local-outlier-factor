#ifndef POINT_H
#define POINT_H

#include <stdarg.h>
#include <vector>
#include<exception>

class CPoint
	/* n维坐标点
	*/
{ 
private:
	std::vector<double> coordinate;	//坐标值
	int dimension;					//维数
public:
	CPoint(int, ...);	// 带数值初始化
	~CPoint();

	void SetValue(int, double);	//修改指定下标的值
	double GetValue(int);	//得到指定下标的值
	int GetDimension();		//得到维度
	
};

bool IsSame(CPoint, CPoint);	//判断是否相同

double DistEuclidean(CPoint, CPoint);

#endif