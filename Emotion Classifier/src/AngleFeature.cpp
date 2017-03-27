#include "Feature.h"

const int usedAngleNum = 8;
std::vector<double> angleFeature(usedAngleNum+1);
static std::vector < std::vector<double> > _angleList;

AngleFeature::AngleFeature(PXCFaceData *face)
{
	_angleList.clear();
	std::cout << "AngleFeature" << std::endl;
	CatureFeature(*face);

}
enum Mouth {
	//嘴角下拉 （61，33，58）（61，39，64） up

	//嘴角张大（47，51） up 距离x

	//嘴角上扬（30，33，56）（32，39，66）down
};

enum Brow {
	//眼睛变小（12，14，16）（20，22，24）down

	//眼睛变大（12，14，16）（20，22，24）up
};

void AngleFeature::CatureFeature(PXCFaceData facedata)
{
	int a[26][3] = { { 61,33,58 },{ 61,39,64 },
	{ 30,33,56 },{ 32,39,66 },
	{ 12,14,16 },{ 20,22,24 },
	{ 12,14,16 },{ 20,22,24 }, };

	std::vector<Face> faceList = facedata.facelist();

	for (auto iter = faceList.begin(); iter != faceList.end(); iter++)
	{
		int t = 1;
		for (int i = 1; i <= usedAngleNum; i++)
		{
			angleFeature[t++] = GetAngle(iter->landmarkPoint[(a[i][0])].image, iter->landmarkPoint[(a[i][1])].image, iter->landmarkPoint[(a[i][2])].image);
		}
		_angleList.push_back(angleFeature);
	}
}

std::vector< std::vector<double> > AngleFeature::getAList()
{
	return _angleList;
}