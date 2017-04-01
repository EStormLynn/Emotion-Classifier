#include "Feature.h"
#include "iostream"



std::vector<double> euclFeature(26);
static std::vector < std::vector<double> > _euclideanList;

EuclideanFeature::EuclideanFeature(PXCFaceData *face)
{
	_euclideanList.clear();

	CatureFeature(*face);
	std::cout << "EuclideanFeature"<<std::endl;

}

void EuclideanFeature::CatureFeature(PXCFaceData facedata)
{
	int a[26][2] ={ { 0,0 },{ 4,0 },{ 9,5 },{ 0,5 },{ 33,39 },{ 0,10 },
	{ 5,18 },{ 4,14 },{ 9,22 },{ 10,14 },{ 18,22 },
	{ 12,16 },{ 20,24 },{ 10,30 },{ 18,32 },{ 14,33 },
	{ 22,39 },{ 30,33 },{ 32,39 },{ 29,47 },{ 47,51 },
	{ 51,61 },{ 33,61 },{ 39,61 },{ 29,10 },{ 29,18 } };

	std::vector<Face> faceList = facedata.facelist();
	
	for (auto iter = faceList.begin(); iter != faceList.end(); iter++)
	{
		int t = 1;
		for (int i = 1; i < 26; i++)
		{
			euclFeature[t++] = GetDistance(iter->landmarkPoint[(a[i][0])].image, iter->landmarkPoint[(a[i][1])].image);
		}
		_euclideanList.push_back(euclFeature);
	}
}

std::vector < std::vector<double> > EuclideanFeature::getUList()
{
	return _euclideanList;
}