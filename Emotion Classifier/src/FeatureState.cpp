#include "FeatureState.h"

MapST mapState;
MapST _happyState;
MapST _supriseState;
MapST _sadnessState;
MapST _angryState;
MapST _fearState;
MapST _disgustState;

std::vector<std::pair<double, std::string>>  ans;

FeatureState::FeatureState(MapST state)
{
	InitState();
	
	double happy = CompareState(state, _happyState,1);
	ans.push_back(std::make_pair(happy, "happy"));

	double suprise = CompareState(state, _supriseState,2);
	ans.push_back(std::make_pair(suprise, "suprise"));

	double sadness = CompareState(state, _sadnessState,3);
	ans.push_back(std::make_pair(sadness, "sadness"));

	double angry = CompareState(state, _angryState,4);
	ans.push_back(std::make_pair(angry, "angry"));

	double fear = CompareState(state, _fearState,5);
	ans.push_back(std::make_pair(fear, "fear"));

	double disgust = CompareState(state, _disgustState,6);
	ans.push_back(std::make_pair(disgust, "disgust"));

	sort(ans.begin(), ans.end());

	for (auto iter = ans.rbegin(); iter != ans.rend(); iter++)
	{
		std::cout << iter->second << ":" << iter->first << std::endl;
	}
	int dfd = 4;
}

void FeatureState::InitState()
{
	State B1, B2, B3, B4;
	State E1, E2;
	State M1, M2, M3, M4, M5;

	B1.stateName = "üȩ̈��";
	B2.stateName = "üë��Ʋ";
	B3.stateName = "üë�м伷ѹ";
	B4.stateName = "üë��ѹ�������м伷ѹ��";

	E1.stateName = "�۾���С";
	E2.stateName = "�۾����";

	M1.stateName = "����Ŵ�";
	M2.stateName = "�������";
	M3.stateName = "�������";
	M4.stateName = "�첿�ϲ���λ������";
	M5.stateName = "�첿΢��";

	mapState.insert(std::make_pair(B1.stateName, B1));
	mapState.insert(std::make_pair(B2.stateName, B2));
	mapState.insert(std::make_pair(B3.stateName, B3));
	mapState.insert(std::make_pair(B4.stateName, B4));

	mapState.insert(std::make_pair(E1.stateName, E1));
	mapState.insert(std::make_pair(E2.stateName, E2));

	mapState.insert(std::make_pair(M1.stateName, M1));
	mapState.insert(std::make_pair(M2.stateName, M2));
	mapState.insert(std::make_pair(M3.stateName, M3));
	mapState.insert(std::make_pair(M4.stateName, M4));
	mapState.insert(std::make_pair(M5.stateName, M5));

	MyEmotionState();

}

void FeatureState::MyEmotionState()
{
	HappyState();
	SupriseState();
	SadnessState();
	AngryState();
	FearState();
	DisgustState();
}


bool operator ==(State s1, State s2)
{
	return s1.stateName == s2.stateName;
}

double FeatureState::CompareState(MapST myState, MapST eMotionState,int Num)
{
	double similarity = 0.2;

	switch (Num)
	{
	case 1://happy
		if (myState.count("�������"))
			similarity = 0.5;
		if (myState.count("üë�м伷ѹ"))
			similarity = -0.2;
		break;
	case 2://suprise
		if (myState.count("üë�м伷ѹ")|| myState.count("üë��ѹ�������м伷ѹ��")|| myState.count("�۾���С"))
			return 0; break;
	case 3://sadness
		if (myState.count("üȩ̈��"))
			return 0; break; 	
	case 4://angry
		similarity = 0.3;
		if (myState.count("üȩ̈��"))
			return 0; break;
	case 5://fear
		similarity = 0.5;
		if (myState.count("�۾����"))
			similarity=1; 
		//if (myState.count("����Ŵ�"))
		//{
		//	State E;
		//	E.stateName = "�첿΢��";
		//	E.i = myState["����Ŵ�"].i;
		//	E.d = myState["����Ŵ�"].d;
		//	myState.insert(std::make_pair("�첿΢��", E));
		//}
			
		break;
	case 6://disgust
		if (myState.count("üë�м伷ѹ"))
		{
				State E;
				E.stateName = "üë��ѹ�������м伷ѹ��";
				E.i = myState["üë�м伷ѹ"].i;
				E.d = myState["üë�м伷ѹ"].d;
				myState.insert(std::make_pair("üë��ѹ�������м伷ѹ��", E));
		}
		//	return 0; break;
	default:
		break;
	}

	
	MapST::iterator iter = eMotionState.begin();
	while (iter != eMotionState.end())
	{
		std::string ss = iter->first;
		if (myState[ss] == iter->second)
		{
			//similarity += abs(myState[ss].d)*iter->second.d;
			
			similarity += iter->second.i*iter->second.d;

		}
		iter++;
	}
	similarity /= eMotionState.size();
	return similarity;
}

#pragma region ����6�ֱ�������
void FeatureState::HappyState()
{
	State E1, M3;

	E1.stateName = "�۾���С";
	E1.i = 1;
	E1.d = 1.0;
	_happyState.insert(std::make_pair(E1.stateName, E1));

	M3.stateName = "�������";
	M3.i = 1;
	M3.d = 1.0;
	_happyState.insert(std::make_pair(M3.stateName, M3));

}

void FeatureState::SupriseState()
{
	State B1, M1;

	B1.stateName = "üȩ̈��";
	B1.i = 1;
	B1.d = 1.0;
	_supriseState.insert(std::make_pair(B1.stateName, B1));

	M1.stateName = "����Ŵ�";
	M1.i = 1;
	M1.d = 1.0;
	_supriseState.insert(std::make_pair(M1.stateName, M1));
}

void FeatureState::SadnessState()
{
	State B2, M2;

	B2.stateName = "üë��Ʋ";
	B2.i = 1;
	B2.d = 1.0;
	_sadnessState.insert(std::make_pair(B2.stateName, B2));

	M2.stateName = "�������";
	M2.i = 1;
	M2.d = 1.0;
	_sadnessState.insert(std::make_pair(M2.stateName, M2));
}

void FeatureState::AngryState()
{
	State B3, E1,M4;

	B3.stateName = "üë�м伷ѹ";
	B3.i = 1;
	B3.d = 1.0;
	_angryState.insert(std::make_pair(B3.stateName, B3));

	E1.stateName = "�۾���С";
	E1.i = 1;
	E1.d = 1.0;
	_angryState.insert(std::make_pair(E1.stateName, E1));

	M4.stateName = "�첿�ϲ���λ������";
	M4.i = 1;
	M4.d = 1.0;
	_angryState.insert(std::make_pair(M4.stateName, M4));
}

void FeatureState::FearState()
{
	State B1, E2, M2, M5;

	B1.stateName = "üȩ̈��";
	B1.i = 1;
	B1.d = 1.0;
	_fearState.insert(std::make_pair(B1.stateName, B1));

	E2.stateName = "�۾����";
	E2.i = 1;
	E2.d = 1.0;
	_fearState.insert(std::make_pair(E2.stateName, E2));

	M2.stateName = "�������";
	M2.i = 1;
	M2.d = 1.0;
	_fearState.insert(std::make_pair(M2.stateName, M2));

	M5.stateName = "�첿΢��";
	M5.i = 1;
	M5.d = 1.0;
	_fearState.insert(std::make_pair(M5.stateName, M5));
}

void FeatureState::DisgustState()
{
	State B4, E1;

	B4.stateName = "üë��ѹ�������м伷ѹ��";
	B4.i = 1;
	B4.d = 1.0;
	_disgustState.insert(std::make_pair(B4.stateName, B4));

	E1.stateName = "�۾���С";
	E1.i = 1;
	E1.d = 1.0;
	_disgustState.insert(std::make_pair(E1.stateName, E1));
}
#pragma endregion

FeatureState::~FeatureState()
{
}
