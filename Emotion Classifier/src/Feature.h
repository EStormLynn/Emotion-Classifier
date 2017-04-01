#pragma once
#include "PXCFaceData.h"
#include "iostream"

class Feature
{
public:
	Feature();

	virtual void CatureFeature(PXCFaceData facedata) {}
	//virtual void DynamicFeature();

	double GetDistance(PXCPointF32 pointA, PXCPointF32 pointB);
	double GetDistance(PXCPoint3DF32 pointA, PXCPoint3DF32 pointB);

	double GetAngle(PXCPointF32 poinA, PXCPointF32 pointB, PXCPointF32 pointC);
	double GetAngle(PXCPoint3DF32 poinA, PXCPoint3DF32 pointB, PXCPoint3DF32 pointC);

	~Feature();
		
};

class EuclideanFeature :public Feature
{
public:
	EuclideanFeature(PXCFaceData *facedata);
	void CatureFeature(PXCFaceData facedata);
	std::vector< std::vector<double> > getUList();

	
private:
	enum FeatureName {
		//1右眼眉毛外边界点 - 右眼眉毛内边界点(4, 0)
		EYEBROW_RIGHT_RIGHT_to_RIGHT_LEFT,

		//2 左眼眉毛外边界点-左眼眉毛内边界点   (9,5)
		EYEBROW_LEFT_RIGHT_to_LEFT_LEFT,

		//3 右眼眉毛内边界点-左眼眉毛内边界点   (0,5)
		EYEBROW_RIGHT_RIGHT_to_LEFT_RIGHT,

		//4 右嘴角点-左嘴角点           (33,39)
		EYELID_RIGHT_LEFT_to_LEFT_RIGHT,

		//5 右眼眉毛内边界点-右眼内眼角点       (0,10)
		EYEBROW_RIGHT_LEFT_to_EYELID_RIGHT_LEFT,

		//6 左眼眉毛内边界点-左眼内眼角点       (5,18)
		EYEBROW_LEFT_RIGHT_to_EYELID_LEFT_RIGHT,

		//7 右眼眉毛外边界点-右眼外眼角点       (4,14)
		EYEBROW_RIGHT_RIGHT_to_EYELID_RIGHT_RIGHT,

		//8 左眼眉毛外边界点-左眼外眼角点       (9,22)
		EYEBROW_LEFT_LEFT_to_EYELID_LEFT_LEFT,

		//9 右眼内眼角点-右眼外眼角点           (10,14)
		EYELID_RIGHT_LEFT_to_RIGHT_RIGHT,

		//10 左眼内眼角点-左眼外眼角点          (18,22)
		EYELID_LEFT_RIGHT_to_LEFT_LEFT,

		//11 右上眼皮中点-右下眼皮中点          (12,16)
		EYELID_RIGHT_TOP_to_RIGHT_BOTTOM,

		//12 左上眼皮中点-左下眼皮中点          (20,24)
		EYELID_LEFT_TOP_to_LEFT_BOTTOM,

		//13 右眼内眼角点-右鼻翼点              (10,30)
		EYELID_RIGHT_LEFT_to_NOSE_RIGHT,

		//14 左眼内眼角点-左鼻翼点              (18,32)
		EYELID_LEFT_RIGHT_to_NOSE_LEFT,

		//15 右眼外眼角点-右嘴角点              (14,33)
		EYELID_RIGHT_RIGHT_to_LIP_RIGHT,

		//16 左眼外眼角点-左嘴角点              (22,39)
		EYELID_LEFT_LEFT_to_LIP_LEFT,

		//17 右鼻翼点-右嘴角点                  (30,33)
		NOSE_RIGHT_to_LIP_RIGHT,

		//18 左鼻翼点-左嘴角点                  (32,39)
		NOSE_LEFT_to_LIP_LEFT,

		//19 鼻尖点-上嘴唇中点                  (29,47)
		NOSE_TIP_to_UPPER_LIP_CENTER,

		//20 上嘴唇中点-下嘴唇中点              (47,51)
		UPPER_LIP_CENTER_to_LOWER_LIP_CENTER,

		//21 下嘴唇中点-下巴点                  (51,61)
		LOWER_LIP_CENTER_to_CHIN,

		//22 右嘴角点-下巴点                    (33,61)
		LIP_RIGHT_to_CHIN,

		//23 左嘴角点-下巴点                    (39,61)
		LIP_LEFT_to_CHIN,

		//24 鼻尖点-右眼内眼角点                (29,10)
		NOSE_TIP_to_EYELID_RIGHT_LEFT,

		//25 鼻尖点-左眼内眼角点                (29,18)
		NOSE_TIP_to_EYELID_LEFT_RIGHT,
	};
};

class AngleFeature :public Feature
{
public:
	AngleFeature(PXCFaceData *facedata);
	void CatureFeature(PXCFaceData facedata);
	std::vector< std::vector<double> > getAList();

private:
	enum Mouth {
		//嘴角下拉 （61，33，58）（61，39，64） up

		//嘴角张大（47，51） up

		//嘴角上扬（30，33，56）（32，39，66）down
	};

	enum Brow {
		//眼睛变小（12，14，16）（20，22，24）down

		//眼睛变大（12，14，16）（20，22，24）up
	};
};