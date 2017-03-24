#include "Feature.h"


Feature::Feature()
{
	
}

double Feature::GetDistance(PXCPointF32 pointA, PXCPointF32 pointB)
{
	double ans = 0.0;	
	ans = sqrt((pointA.x - pointB.x)*(pointA.x - pointB.x) + (pointA.y - pointB.y)*(pointA.y - pointB.y));
	return ans;
}

double Feature::GetDistance(PXCPoint3DF32 pointA, PXCPoint3DF32 pointB)
{
	double ans = 0.0;
	ans = sqrt((pointA.x - pointB.x)*(pointA.x - pointB.x) + (pointA.y - pointB.y)*(pointA.y - pointB.y) + (pointA.z - pointB.z)*(pointA.z - pointB.z));
	return ans;
}

double Feature::GetAngle(PXCPointF32 poinA, PXCPointF32 pointB, PXCPointF32 pointC)
{
	double ans = 0.0;
	return ans;

}
double Feature::GetAngle(PXCPoint3DF32 poinA, PXCPoint3DF32 pointB, PXCPoint3DF32 pointC)
{
	double ans = 0.0;
	return ans;
}

Feature::~Feature()
{
}

