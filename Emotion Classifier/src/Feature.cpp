#include "Feature.h"
#define M_PI 3.14159265358979323846

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

double Feature::GetAngle(PXCPointF32 pointA, PXCPointF32 pointB, PXCPointF32 pointC)
{
	double ans = 0.0,cosAns=0;
	PXCPointF32 BA, BC;//BA,BCœÚ¡ø
	BA.x = pointA.x - pointB.x;
	BA.y = pointA.y - pointB.y;
	BC.x = pointC.x - pointB.x;
	BC.y = pointC.y - pointB.y;
	cosAns = (BA.x*BC.x + BA.y*BC.y) / (sqrt(BA.x*BA.x + BA.y*BA.y)*sqrt(BC.x*BC.x + BC.y*BC.y));
	ans = acos(cosAns);
	ans = ans / M_PI * 180;
	return ans;

}
double Feature::GetAngle(PXCPoint3DF32 pointA, PXCPoint3DF32 pointB, PXCPoint3DF32 pointC)
{
	double ans = 0.0;
	return ans;
}

Feature::~Feature()
{
}

