#pragma once
#include "map"
#include "vector"
#include "iostream"
#include "algorithm"
#include "string"
struct State
{
	std::string stateName;		//״̬��
	int i;						//״̬�룬0�أ�1��
	double d;					//�仯��
};

typedef std::map<std::string, State> MapST;

class FeatureState
{
public:
	FeatureState(MapST state);

	void InitState();
	void MyEmotionState();
	double CompareState(MapST myState, MapST eMotionState);  //myState���ݵ�����״̬��eMotionState�������������״̬


	~FeatureState();

private:
	static void HappyState();
	static void SupriseState();
	static void SadnessState();
	static void AngryState();
	static void FearState();
	static void DisgustState();
};

