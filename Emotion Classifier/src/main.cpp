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
	AngleFeature angleFea(face);

	std::vector < std::vector<double> > eList,aList;   //�������������ڵ�Ϊÿ֡��������
	eList = euclideanFea.getUList();
	aList = angleFea.getAList();

	std::vector < std::vector<double> > eDeltaList,aDeltaList;		//������������仯�����ڵ�Ϊÿ֡���������仯��
	eDeltaList.clear();
	aDeltaList.clear();
	const int eNum = eList[1].size();//e��������
	const int aNum = aList[1].size();
	
	std::vector<double> temp;
	for (int i = 0; i < eNum; i++)
	{
		temp.clear();
		for (int j = 0; j < eNum; j++)
		{
			double re1=eList[i + 1][j];
			double re2=eList[i][j];
			temp.push_back(re2-re1);
		}
		eDeltaList.push_back(temp);
	}

	for (int i = 0; i < aNum - 1; i++)
	{
		temp.clear();
		for (int j = 0; j < aNum; j++)
		{
			double re1 = aList[i + 1][j];
			double re2 = aList[i][j];
			temp.push_back(re2 - re1);
		}
		aDeltaList.push_back(temp);
	}
	
	//��¼�����仯����
	std::pair<int, double> cntMe[32]; //pair���飬firstΪ0,1��-1��ʾ���䣬���󣬼�С����������second �仯��
	std::pair<int, double> cntMa[32]; //pair���飬firstΪ0,1��-1��ʾ���䣬���󣬼�С����������second �仯��

	for (int i = 1; i < eNum; i++)
	{
		double del = (eList.back()[i] - eList.front()[i]) / eList.front()[i];

		int tag = 0;
		if (del > 0.05)
			tag = 1;
		else if (del < -0.05)
			tag = -1;

		cntMe[i] = std::make_pair(tag, del);
		//std::cout << del << std::endl;
	}

	MapST state;
	if (cntMe[11].first < 0 || cntMe[12].first < 0)
	{
		printf("�۾���СE1��:%f %,%f %\n", cntMe[11].second, cntMe[12].second);
		State E1;
		E1.stateName = "�۾���С";
		E1.i = 1;
		E1.d = (cntMe[11].second + cntMe[12].second) / 2;
		state[E1.stateName] = E1;
	}
		

	if (cntMe[11].first > 0 || cntMe[12].first > 0)		
	{
		printf("�۾����E2��:%f %,%f %\n", cntMe[11].second, cntMe[12].second);
		State E2;
		E2.stateName = "�۾����";
		E2.i = 1;
		E2.d = (cntMe[11].second + cntMe[12].second) / 2;
		state[E2.stateName] = E2;
	}

 	if (cntMe[20].first > 0)
	{
		printf("����Ŵ�M1��:%f % \n", cntMe[20].second);
		State M1;
		M1.stateName = "����Ŵ�";
		M1.i = 1;
		M1.d = cntMe[20].second;
		state[M1.stateName] = M1;
	}

 	if (cntMe[22].first < 0 || cntMe[23].first < 0)		
	{
		printf("�������M2��:%f %,%f %\n", cntMe[22].second, cntMe[23].second);
		State M2;
		M2.stateName = "�������";
		M2.i = 1;
		M2.d = (cntMe[22].second + cntMe[23].second) / 2;
		state[M2.stateName] = M2;
	}

	
 	if (cntMe[17].first < 0 || cntMe[18].first < 0)	
	{
		printf("�������M3��:%f %,%f %\n", cntMe[17].second, cntMe[18].second);
		State M3;
		M3.stateName = "�������";
		M3.i = 1;
		M3.d = (cntMe[17].second + cntMe[18].second) / 2;
		state[M3.stateName] = M3;
	}

 	if (cntMe[19].first < 0 && cntMe[21].first > 0)
	{
		printf("�첿�ϲ���λ������M4��:%f %,%f %\n", cntMe[19].second, cntMe[21].second);
		State M4;
		M4.stateName = "�첿�ϲ���λ������";
		M4.i = 1;
		M4.d = (cntMe[19].second + cntMe[21].second) / 2;
		state[M4.stateName] = M4;
	}

 	if (cntMe[20].first > 0 && cntMe[20].second< 0.2)
	{
		printf("�첿΢��M5��:%f % \n", cntMe[20].second);
		State M5;
		M5.stateName = "�첿΢��";
		M5.i = 1;
		M5.d = cntMe[20].second;
		state[M5.stateName] = M5;
	}

 	if (cntMe[5].first > 0 || cntMe[6].first > 0 )
	{
		printf("üȩ̈��B1��:%f %,%f %\n", cntMe[5].second, cntMe[6].second);
		State B1;
		B1.stateName = "üȩ̈��";
		B1.i = 1;
		B1.d = (cntMe[5].second + cntMe[6].second) / 2;
		state[B1.stateName] = B1;
	}

 	if (cntMe[3].first > 0)
	{
		printf("üë��ƲB2��:%f %\n", cntMe[3].second);
		State B2;
		B2.stateName = "üë��Ʋ";
		B2.i = 1;
		B2.d = cntMe[3].second;
		state[B2.stateName] = B2;
	}
	
 	if (cntMe[5].first < 0 && cntMe[6].first < 0)
	{
		printf("üë�м伷ѹB3��::%f %,%f %\n", cntMe[5].second, cntMe[6].second);

		State B3;
		B3.stateName = "üë�м伷ѹ";
		B3.i = 1;
		B3.d = (cntMe[5].second + cntMe[6].second) / 2;
		state[B3.stateName] = B3;
	}


	
	FeatureState featureState(state);
	
	
	std::vector<LandmarkPoint> f(5);


	delete face;
}