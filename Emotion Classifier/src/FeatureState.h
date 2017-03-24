#pragma once
#include "map"
#include "vector"
#include "iostream"
#include "algorithm"
#include "string"
struct State
{
	std::string stateName;		//状态名
	int i;						//状态码，0关，1开
	double d;					//变化量
};

typedef std::map<std::string, State> MapST;

class FeatureState
{
public:
	FeatureState(MapST state);

	void InitState();
	void MyEmotionState();
	double CompareState(MapST myState, MapST eMotionState);  //myState数据的特征状态，eMotionState基本表情的特征状态


	~FeatureState();

private:
	static void HappyState();
	static void SupriseState();
	static void SadnessState();
	static void AngryState();
	static void FearState();
	static void DisgustState();
};

