#include "iostream"
#include "PXCFaceData.h"
#include "ReadData.h"
#include "Feature.h"
#include "FeatureState.h"


#include "map"


int main()
{

	std::string dir = R"(C:\Users\SeekHit\Desktop\emotion test\S054\002\CKData.txt)";
	PXCFaceData *face = new PXCFaceData();

	ReadData readdata(dir,face);

	//PXCFaceData
	

	EuclideanFeature euclideanFea(face);

	std::vector < std::vector<double> > eList = euclideanFea.uclideanList();   //脸部特征链表，节点为每帧所有特征
	std::vector < std::vector<double> > eDeltaList;							   //脸部特征链表变化量，节点为每帧所有特征变化量
	eDeltaList.clear();
	std::vector<double> temp;
	for (int i = 0; i < eList.size()-1; i++)
	{
		temp.clear();
		for (int j = 0; j < 26; j++)
		{
			double re1=eList[i + 1][j];
			double re2=eList[i][j];
			temp.push_back(re2-re1);
		}
		eDeltaList.push_back(temp);
	}
	
	//记录特征变化多少
	std::pair<int, double> cntM[26]; //pair数组，first为0,1，-1表示不变，增大，减小—————second 变化率


	for (int i = 1; i < 26; i++)
	{
		double del = (eList.back()[i] - eList.front()[i]) / eList.front()[i];

		int tag = 0;
		if (del > 0.05)
			tag = 1;
		else if (del < -0.05)
			tag = -1;

		cntM[i] = std::make_pair(tag, del);
		//std::cout << del << std::endl;
	}

	MapST state;
	if (cntM[11].first < 0 || cntM[12].first < 0)
	{
		printf("眼睛变小E1了:%f %,%f %\n", cntM[11].second, cntM[12].second);
		State E1;
		E1.stateName = "眼睛变小";
		E1.i = 1;
		E1.d = (cntM[11].second + cntM[12].second) / 2;
		state[E1.stateName] = E1;
	}
		

	if (cntM[11].first > 0 || cntM[12].first > 0)		
	{
		printf("眼睛变大E2了:%f %,%f %\n", cntM[11].second, cntM[12].second);
		State E2;
		E2.stateName = "眼睛变大";
		E2.i = 1;
		E2.d = (cntM[11].second + cntM[12].second) / 2;
		state[E2.stateName] = E2;
	}

 	if (cntM[20].first > 0)
	{
		printf("嘴巴张大M1了:%f % \n", cntM[20].second);
		State M1;
		M1.stateName = "嘴巴张大";
		M1.i = 1;
		M1.d = cntM[20].second;
		state[M1.stateName] = M1;
	}

 	if (cntM[22].first < 0 || cntM[23].first < 0)		
	{
		printf("嘴角下拉M2了:%f %,%f %\n", cntM[22].second, cntM[23].second);
		State M2;
		M2.stateName = "嘴角下拉";
		M2.i = 1;
		M2.d = (cntM[22].second + cntM[23].second) / 2;
		state[M2.stateName] = M2;
	}

	
 	if (cntM[17].first < 0 || cntM[18].first < 0)	
	{
		printf("嘴角上扬M3了:%f %,%f %\n", cntM[17].second, cntM[18].second);
		State M3;
		M3.stateName = "嘴角上扬";
		M3.i = 1;
		M3.d = (cntM[17].second + cntM[18].second) / 2;
		state[M3.stateName] = M3;
	}

 	if (cntM[19].first < 0 && cntM[21].first > 0)
	{
		printf("嘴部合并，位置上移M4了:%f %,%f %\n", cntM[19].second, cntM[21].second);
		State M4;
		M4.stateName = "嘴部合并，位置上移";
		M4.i = 1;
		M4.d = (cntM[19].second + cntM[21].second) / 2;
		state[M4.stateName] = M4;
	}

 	if (cntM[20].first > 0 && cntM[20].second< 0.2)
	{
		printf("嘴部微张M5了:%f % \n", cntM[20].second);
		State M5;
		M5.stateName = "嘴部微张";
		M5.i = 1;
		M5.d = cntM[20].second;
		state[M5.stateName] = M5;
	}

 	if (cntM[5].first > 0 || cntM[6].first > 0 )
	{
		printf("眉毛抬高B1了:%f %,%f %\n", cntM[5].second, cntM[6].second);
		State B1;
		B1.stateName = "眉毛抬高";
		B1.i = 1;
		B1.d = (cntM[5].second + cntM[6].second) / 2;
		state[B1.stateName] = B1;
	}

 	if (cntM[3].first > 0)
	{
		printf("眉毛外撇B2了:%f %\n", cntM[3].second);
		State B2;
		B2.stateName = "眉毛外撇";
		B2.i = 1;
		B2.d = cntM[3].second;
		state[B2.stateName] = B2;
	}
	
 	if (cntM[5].first < 0 && cntM[6].first < 0)
	{
		printf("眉毛中间挤压B3了::%f %,%f %\n", cntM[5].second, cntM[6].second);

		State B3;
		B3.stateName = "眉毛中间挤压";
		B3.i = 1;
		B3.d = (cntM[5].second + cntM[6].second) / 2;
		state[B3.stateName] = B3;
	}

	
	FeatureState featureState(state);
	
	
	std::vector<LandmarkPoint> f(5);


	delete face;
}