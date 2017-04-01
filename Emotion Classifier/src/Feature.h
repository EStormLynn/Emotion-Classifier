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
		//1����üë��߽�� - ����üë�ڱ߽��(4, 0)
		EYEBROW_RIGHT_RIGHT_to_RIGHT_LEFT,

		//2 ����üë��߽��-����üë�ڱ߽��   (9,5)
		EYEBROW_LEFT_RIGHT_to_LEFT_LEFT,

		//3 ����üë�ڱ߽��-����üë�ڱ߽��   (0,5)
		EYEBROW_RIGHT_RIGHT_to_LEFT_RIGHT,

		//4 ����ǵ�-����ǵ�           (33,39)
		EYELID_RIGHT_LEFT_to_LEFT_RIGHT,

		//5 ����üë�ڱ߽��-�������۽ǵ�       (0,10)
		EYEBROW_RIGHT_LEFT_to_EYELID_RIGHT_LEFT,

		//6 ����üë�ڱ߽��-�������۽ǵ�       (5,18)
		EYEBROW_LEFT_RIGHT_to_EYELID_LEFT_RIGHT,

		//7 ����üë��߽��-�������۽ǵ�       (4,14)
		EYEBROW_RIGHT_RIGHT_to_EYELID_RIGHT_RIGHT,

		//8 ����üë��߽��-�������۽ǵ�       (9,22)
		EYEBROW_LEFT_LEFT_to_EYELID_LEFT_LEFT,

		//9 �������۽ǵ�-�������۽ǵ�           (10,14)
		EYELID_RIGHT_LEFT_to_RIGHT_RIGHT,

		//10 �������۽ǵ�-�������۽ǵ�          (18,22)
		EYELID_LEFT_RIGHT_to_LEFT_LEFT,

		//11 ������Ƥ�е�-������Ƥ�е�          (12,16)
		EYELID_RIGHT_TOP_to_RIGHT_BOTTOM,

		//12 ������Ƥ�е�-������Ƥ�е�          (20,24)
		EYELID_LEFT_TOP_to_LEFT_BOTTOM,

		//13 �������۽ǵ�-�ұ����              (10,30)
		EYELID_RIGHT_LEFT_to_NOSE_RIGHT,

		//14 �������۽ǵ�-������              (18,32)
		EYELID_LEFT_RIGHT_to_NOSE_LEFT,

		//15 �������۽ǵ�-����ǵ�              (14,33)
		EYELID_RIGHT_RIGHT_to_LIP_RIGHT,

		//16 �������۽ǵ�-����ǵ�              (22,39)
		EYELID_LEFT_LEFT_to_LIP_LEFT,

		//17 �ұ����-����ǵ�                  (30,33)
		NOSE_RIGHT_to_LIP_RIGHT,

		//18 ������-����ǵ�                  (32,39)
		NOSE_LEFT_to_LIP_LEFT,

		//19 �Ǽ��-���촽�е�                  (29,47)
		NOSE_TIP_to_UPPER_LIP_CENTER,

		//20 ���촽�е�-���촽�е�              (47,51)
		UPPER_LIP_CENTER_to_LOWER_LIP_CENTER,

		//21 ���촽�е�-�°͵�                  (51,61)
		LOWER_LIP_CENTER_to_CHIN,

		//22 ����ǵ�-�°͵�                    (33,61)
		LIP_RIGHT_to_CHIN,

		//23 ����ǵ�-�°͵�                    (39,61)
		LIP_LEFT_to_CHIN,

		//24 �Ǽ��-�������۽ǵ�                (29,10)
		NOSE_TIP_to_EYELID_RIGHT_LEFT,

		//25 �Ǽ��-�������۽ǵ�                (29,18)
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
		//������� ��61��33��58����61��39��64�� up

		//����Ŵ�47��51�� up

		//������30��33��56����32��39��66��down
	};

	enum Brow {
		//�۾���С��12��14��16����20��22��24��down

		//�۾����12��14��16����20��22��24��up
	};
};