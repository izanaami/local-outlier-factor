#include "lof.h"

LOF::LOF(std::vector<CPoint> instances, bool isnormalize)
{
	if (!vec_Instances.empty())
		vec_Instances.clear();
	if (!vec_MaxAttributeValue.empty())
		vec_MaxAttributeValue.clear();
	if (!vec_MinAttributeValue.empty())
		vec_MinAttributeValue.clear();

	vec_Instances = instances;
	// instance dimension
	n_InstanceDimension = vec_Instances.at(0).GetDimension();
	for (int i = 1; i < vec_Instances.size(); i++)
	{
		if (n_InstanceDimension != vec_Instances.at(i).GetDimension())
		{
			printf("class LOF init error: instances have different dimensions.");
			exit(0);
		}
	}

	normalize = isnormalize;
	if (normalize)
		NormalizeInstances();
}

LOF::~LOF()
{
	vec_Instances.clear();
	vec_MaxAttributeValue.clear();
	vec_MinAttributeValue.clear();
}

void LOF::ComputeInstanceAttributeBounds()
/*	得到每个维度上最大值和最小值组成的数组
*/
{
	vec_MaxAttributeValue.resize(n_InstanceDimension);
	vec_MinAttributeValue.resize(n_InstanceDimension);

	for (int i = 0; i < n_InstanceDimension; i++)
	{
		vec_MaxAttributeValue.at(i) = (double)vec_Instances.at(0).GetValue(i);
		vec_MinAttributeValue.at(i) = (double)vec_Instances.at(0).GetValue(i);
	}
	for (int j = 1; j < vec_Instances.size(); j++)
	{
		for (int i = 0; i < n_InstanceDimension; i++)
		{
			if ((double)vec_Instances.at(j).GetValue(i)>(double)vec_MaxAttributeValue.at(i))
				vec_MaxAttributeValue.at(i) = (double)vec_Instances.at(j).GetValue(i);
			if ((double)vec_Instances.at(j).GetValue(i)<(double)vec_MinAttributeValue.at(i))
				vec_MinAttributeValue.at(i) = (double)vec_Instances.at(j).GetValue(i);
		}
	}
}

void LOF::NormalizeInstances()
/*	Normalizes the instances and stores the infromation for rescaling new instances.
*/
{
	if (vec_MaxAttributeValue.size() == 0)
		this->ComputeInstanceAttributeBounds();
	for (int i = 0; i < vec_Instances.size(); i++)
		// normalize the i-th instance in instances
		vec_Instances.at(i) = this->NormalizeInstance(vec_Instances.at(i));
}

CPoint LOF::NormalizeInstance(CPoint instance)
/*	Normalize: (value - min)/(max - min)
*/
{
	CPoint normalizedInstance(n_InstanceDimension);	// 初始化CPoint类，数值为随机
	double max, min, value;
	
	for (int i = 0; i < n_InstanceDimension; i++)
	{
		value = (double)instance.GetValue(i);
		max = (double)vec_MaxAttributeValue.at(i);
		min = (double)vec_MinAttributeValue.at(i);
		if (max - min == 0)
			normalizedInstance.SetValue(i, 0.0);
		else
		{
			double normalizedValue;
			normalizedValue = (value - min) / (max - min);
			normalizedInstance.SetValue(i, normalizedValue);
		}
	}
	return normalizedInstance;
}

double LOF::LocalOutlierFactor(int minPts, CPoint instance)
/*	The (local) outlier factor of instance captures the degree to which we call instance an outlier.
	min_pts is a parameter that is specifying a minimum number of instances to consider for computing LOF value.
*/
{
	CPoint lofInstance = instance;
	if (normalize)
		lofInstance = NormalizeInstance(instance);
	
	double k_distanceValue;
	std::vector<CPoint> vec_Neighbours;

	k_distanceValue = k_distance(minPts, lofInstance, this->vec_Instances, &vec_Neighbours);

	double instanceLrd = LocalReachabilityDensity(minPts, lofInstance, this->vec_Instances);

	std::vector<double> vec_lrdRatios(vec_Neighbours.size(), 0.0);

	std::vector<CPoint> vec_InstancesWithoutNeighbour = this->vec_Instances;
	// instances_withour_neighbour = set(instaces)	去除重复的instance
	for (int i = 0; i < vec_InstancesWithoutNeighbour.size(); i++)
	{
		for (int j = i + 1; j < vec_InstancesWithoutNeighbour.size(); j++)
		{
			if (IsSame(vec_InstancesWithoutNeighbour.at(j), vec_InstancesWithoutNeighbour.at(i)))
			{
				// 删除第j个元素
				vec_InstancesWithoutNeighbour.erase(vec_InstancesWithoutNeighbour.begin() + j);
				j--;
			}
		}
	}

	for (int i = 0; i < vec_Neighbours.size(); i++)
	{
		// instances_without_neighbour.discard(neighbour) 去除和neighbour一样的元素
		for (int j = 0; j < vec_InstancesWithoutNeighbour.size(); j++)
		{
			if (IsSame(vec_Neighbours.at(i), vec_InstancesWithoutNeighbour.at(j)))
			{
				vec_InstancesWithoutNeighbour.erase(vec_InstancesWithoutNeighbour.begin() + j);
				j--;
			}
		}

		double neighbourLrd = LocalReachabilityDensity(minPts, vec_Neighbours.at(i), vec_InstancesWithoutNeighbour);
		vec_lrdRatios.at(i) = (double)(neighbourLrd / instanceLrd);
	}
	
	double sum = 0;
	for (int i = 0; i < vec_lrdRatios.size(); i++)
		sum += (double)vec_lrdRatios.at(i);
	
	double lenNeighbours = (double)vec_Neighbours.size();
	return (double)(sum / lenNeighbours);
}

void LOF::debug_printout()
/*	debug
*/
{

	std::cout << "instace num: " << vec_Instances.size() << std::endl;
	std::cout << "instace dimension: " << n_InstanceDimension << std::endl;

	std::cout << "max attribute value: (";
	for (int i = 0; i < n_InstanceDimension; i++)
		std::cout << vec_MaxAttributeValue.at(i) << ", ";
	std::cout << ")" << std::endl;

	std::cout << "min attribute value: (";
	for (int i = 0; i < n_InstanceDimension; i++)
		std::cout << vec_MinAttributeValue.at(i) << ", ";
	std::cout << ")" << std::endl;

	NormalizeInstances();
	std::cout << "normalized instance[0]: (";
	for (int i = 0; i < n_InstanceDimension; i++)
		std::cout << vec_Instances.at(0).GetValue(i) << ", ";
	std::cout << ")" << std::endl;
}

double k_distance(int k, CPoint instance, std::vector<CPoint> instances, std::vector<CPoint>* pvec_Neighbours)
/*	Computes the k-distance of instance as defined in paper. 
	It also gatheres the set of k-distance neighbours.
*/
{
	// distances:( key: distance_value -> value: instances )
	std::map<double, std::vector<CPoint>> map_Distances;
	std::map<double, std::vector<CPoint>>::iterator iter;
	
	double distanceValue;
	
	for (int i = 0; i < instances.size(); i++)
	{
		distanceValue = DistEuclidean(instance, instances.at(i));
		iter = map_Distances.find(distanceValue);
		if (iter != map_Distances.end())	// find
		{
			map_Distances[distanceValue].push_back(instances.at(i));
		}
		else    // not find
		{
			std::vector<CPoint> vec_temp;
			vec_temp.push_back(instances.at(i));
			// map会自动根据key进行排序
			map_Distances.insert(std::pair<double, std::vector<CPoint>>(distanceValue, vec_temp));
		}
	}

	int k_sero = 0;
	double k_dist;
	pvec_Neighbours->clear();

	// neighbours 保存最近的k个instance
	for (iter = map_Distances.begin(); iter != map_Distances.end(); ++iter)
	{
		k_sero += iter->second.size();
		for (int i = 0; i < iter->second.size(); i++)
		{
			pvec_Neighbours->push_back(iter->second.at(i));
		}
		k_dist = iter->first;	// 第k近的instance的距离
		if (k_sero >= k)
			break;
	}

	/*	// print
	for (iter = map_Distances.begin(); iter != map_Distances.end();++iter)
	{
		std::cout << iter->first << std::endl;
		for (int i = 0; i < iter->second.size(); i++)
		{
			for (int j = 0; j < iter->second.at(i).GetDimension(); j++)
			{
				std::cout << iter->second.at(i).GetValue(j) << " ";
			}
			std::cout << std::endl;
		}
	}*/
	return k_dist;
}

double ReachabilityDist(int k, CPoint instance1, CPoint instance2, std::vector<CPoint> vec_Instances)
/*	The reachability distance of instance1 with respect to instance2.
*/
{
	double k_distanceValue;
	std::vector<CPoint> neighbours;

	k_distanceValue = k_distance(k, instance2, vec_Instances, &neighbours);
	
	double distanceEuclidean = DistEuclidean(instance1, instance2);
	
	if ((double)k_distanceValue > (double)distanceEuclidean)
		return k_distanceValue;
	else
		return distanceEuclidean;
}

double LocalReachabilityDensity(int minPts, CPoint instance, std::vector<CPoint> vec_Instances)
/*	Local reachability density of instance is the inverse of the average reachability 
    distance based on the min_pts-nearest neighbors of instance.
*/
{
	double k_distanceValue;
	std::vector<CPoint> vec_Neighbours;

	k_distanceValue = k_distance(minPts, instance, vec_Instances, &vec_Neighbours);

	std::vector<double> vec_ReachabilityDistances(vec_Neighbours.size(), 0);	// n.zeros(len(neighbours))
	
	for (int i = 0; i < vec_Neighbours.size(); i++)
	{
		vec_ReachabilityDistances.at(i) = ReachabilityDist(minPts, instance, vec_Neighbours.at(i), vec_Instances);
	}

	double sumReachDist = 0.0;
	for (int i = 0; i < vec_ReachabilityDistances.size(); i++)
		sumReachDist += (double)vec_ReachabilityDistances.at(i);

	if (sumReachDist == 0.0)
		return DBL_MAX;	// return inf
	double lenNeighbour = (double)vec_Neighbours.size();
	return (double)(lenNeighbour / sumReachDist);
}

std::vector<outlier> GetOutliers(int k, std::vector<CPoint> vec_Instances)
/*	得到outliers，输出为vector<struct outlier>
	outlier{
	double lof;
	CPoint instance;
	int index;}
*/
{
	std::vector<CPoint> vec_InstancesBackUp;
	std::vector<outlier> vec_Outliers;
	vec_Outliers.clear();

	for (int i = 0; i < vec_Instances.size(); i++)
	{
		CPoint instance = vec_Instances.at(i);
		vec_InstancesBackUp = vec_Instances;
		vec_InstancesBackUp.erase(vec_InstancesBackUp.begin() + i);
		LOF l(vec_InstancesBackUp, true);
		double value = l.LocalOutlierFactor(k, instance);
		if (value>1.0)
		{
			outlier temp = { value, instance, i };	// { lof, instance, index }
			vec_Outliers.push_back(temp);
		}
	}

	// 冒泡排序
	for (int i = 0; i < vec_Outliers.size(); i++) 
	{
		for (int j = 0; j < vec_Outliers.size() - 1 - i; j++) 
		{
			if (vec_Outliers.at(j).lof < vec_Outliers.at(j + 1).lof) {
				outlier temp = vec_Outliers.at(j + 1);
				vec_Outliers.at(j + 1) = vec_Outliers.at(j);
				vec_Outliers.at(j) = temp;
			}
		}
	}

	return vec_Outliers;
}