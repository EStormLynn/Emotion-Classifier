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

	std::vector < std::vector<double> > eList = euclideanFea.uclideanList();   //�������������ڵ�Ϊÿ֡��������
	std::vector < std::vector<double> > eDeltaList;							   //������������仯�����ڵ�Ϊÿ֡���������仯��
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
	
	//��¼�����仯����
	std::pair<int, double> cntM[26]; //pair���飬firstΪ0,1��-1��ʾ���䣬���󣬼�С����������second �仯��


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
		printf("�۾���СE1��:%f %,%f %\n", cntM[11].second, cntM[12].second);
		State E1;
		E1.stateName = "�۾���С";
		E1.i = 1;
		E1.d = (cntM[11].second + cntM[12].second) / 2;
		state[E1.stateName] = E1;
	}
		

	if (cntM[11].first > 0 || cntM[12].first > 0)		
	{
		printf("�۾����E2��:%f %,%f %\n", cntM[11].second, cntM[12].second);
		State E2;
		E2.stateName = "�۾����";
		E2.i = 1;
		E2.d = (cntM[11].second + cntM[12].second) / 2;
		state[E2.stateName] = E2;
	}

 	if (cntM[20].first > 0)
	{
		printf("����Ŵ�M1��:%f % \n", cntM[20].second);
		State M1;
		M1.stateName = "����Ŵ�";
		M1.i = 1;
		M1.d = cntM[20].second;
		state[M1.stateName] = M1;
	}

 	if (cntM[22].first < 0 || cntM[23].first < 0)		
	{
		printf("�������M2��:%f %,%f %\n", cntM[22].second, cntM[23].second);
		State M2;
		M2.stateName = "�������";
		M2.i = 1;
		M2.d = (cntM[22].second + cntM[23].second) / 2;
		state[M2.stateName] = M2;
	}

	
 	if (cntM[17].first < 0 || cntM[18].first < 0)	
	{
		printf("�������M3��:%f %,%f %\n", cntM[17].second, cntM[18].second);
		State M3;
		M3.stateName = "�������";
		M3.i = 1;
		M3.d = (cntM[17].second + cntM[18].second) / 2;
		state[M3.stateName] = M3;
	}

 	if (cntM[19].first < 0 && cntM[21].first > 0)
	{
		printf("�첿�ϲ���λ������M4��:%f %,%f %\n", cntM[19].second, cntM[21].second);
		State M4;
		M4.stateName = "�첿�ϲ���λ������";
		M4.i = 1;
		M4.d = (cntM[19].second + cntM[21].second) / 2;
		state[M4.stateName] = M4;
	}

 	if (cntM[20].first > 0 && cntM[20].second< 0.2)
	{
		printf("�첿΢��M5��:%f % \n", cntM[20].second);
		State M5;
		M5.stateName = "�첿΢��";
		M5.i = 1;
		M5.d = cntM[20].second;
		state[M5.stateName] = M5;
	}

 	if (cntM[5].first > 0 || cntM[6].first > 0 )
	{
		printf("üȩ̈��B1��:%f %,%f %\n", cntM[5].second, cntM[6].second);
		State B1;
		B1.stateName = "üȩ̈��";
		B1.i = 1;
		B1.d = (cntM[5].second + cntM[6].second) / 2;
		state[B1.stateName] = B1;
	}

 	if (cntM[3].first > 0)
	{
		printf("üë��ƲB2��:%f %\n", cntM[3].second);
		State B2;
		B2.stateName = "üë��Ʋ";
		B2.i = 1;
		B2.d = cntM[3].second;
		state[B2.stateName] = B2;
	}
	
 	if (cntM[5].first < 0 && cntM[6].first < 0)
	{
		printf("üë�м伷ѹB3��::%f %,%f %\n", cntM[5].second, cntM[6].second);

		State B3;
		B3.stateName = "üë�м伷ѹ";
		B3.i = 1;
		B3.d = (cntM[5].second + cntM[6].second) / 2;
		state[B3.stateName] = B3;
	}

	
	FeatureState featureState(state);
	
	
	std::vector<LandmarkPoint> f(5);


	delete face;
}