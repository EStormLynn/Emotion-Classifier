#include "ReadData.h"
#include "PXCFaceData.h"

using namespace  std;
PXCFaceData *_prvface;

///构造函数
ReadData::ReadData(std::string &dir,PXCFaceData *PXCface)
{
	cout << dir << endl;
	std::ifstream infile;
	infile.open(dir.data());
	//assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	_prvface = PXCface;

	std::string s;
	while (std::getline(infile, s))
	{
		DataFrom df = CK;
		Analysis(s, df);			//0=Realsense ,1=CK+
		PXCFaceData::update(_prvface->face);
	}

	infile.close();             //关闭文件输入流 
}


void ReadData::Analysis(std::string &str, DataFrom df)
{
	switch (df)
	{
	case ReadData::Realsense:
		Anal_RS78(str);
		break;
	case ReadData::CK:
		Anal_CK(str);
		break;
	default:
		break;
	}
}

#pragma region 解析RealSense/CK+的数据
void ReadData::Anal_RS(std::string str)
{
	str.size();
	std::string s;
	std::vector<std::string> v_s;
	std::vector<double> v_d;
	int tag = -1;
	for (int i = 0, j = 0; i < str.length(); i++)
	{
		if (str[i] != '\t')
			s += str[i];
		else
		{
			v_s.push_back(s);			
			//v_d.push_back(str2double(s));
			s.clear();
		}
	}

	int t = 0, id = 256;
	for (std::vector<string>::iterator iter = v_s.begin(); iter != v_s.end(); iter++,t++)
	{
		if (t < 3)
			continue;
		double d = 0.0;
		if(t<227) switch (t % 7)
		{
		case 3:
			id = str2int(*iter);
			_prvface->face.landmarkPoint[id].source.index = id;
			break;
		case 4:
			//_prvface->face.landmarkPoint[id].source.alias = iter[t];
			break;
		case 5:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].world.x = d;
			break;
		case 6:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].world.y = d;
			break;
		case 0:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].world.z = d;
			break;
		case 1:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].image.x = d;
			break;
		case 2:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].image.y = d;
			break;
		default:
			break;
		}

		if (t == 227)		{
			d = str2double(*iter);
			_prvface->face.headPosition.headCenter.x = d;		}
		if (t == 228)		{
			d = str2double(*iter);
			_prvface->face.headPosition.headCenter.y = d;		}
		if (t == 229)		{
			d = str2double(*iter);
			_prvface->face.headPosition.headCenter.z = d;		}
		if (t == 230)		{
			d = str2double(*iter);
			_prvface->face.poseEulerAngles.pitch = d;		}
		if (t == 231) {
			d = str2double(*iter);
			_prvface->face.poseEulerAngles.roll = d;		}		
		if (t == 232)		{
			d = str2double(*iter);
			_prvface->face.poseEulerAngles.yaw = d;		}		
	}	
	std::cout << v_d.size();

}

void ReadData::Anal_RS78(std::string str)
{
	str.size();
	std::string s;
	std::vector<std::string> v_s;
	std::vector<double> v_d;
	int tag = -1;
	for (int i = 0, j = 0; i < str.length(); i++)
	{
		if (str[i] != '\t')
			s += str[i];
		else
		{
			v_s.push_back(s);
			//v_d.push_back(str2double(s));
			s.clear();
		}
	}

	int t = 0, id = 256;
	for (std::vector<string>::iterator iter = v_s.begin(); iter != v_s.end(); iter++, t++)
	{
		if (t < 3)
			continue;
		double d = 0.0;
		if (t<471) switch (t % 6)
		{
		case 3:
			id = str2int(*iter);
			_prvface->face.landmarkPoint[id].source.index = id;
			break;
		case 4:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].world.x = d;
			break;
		case 5:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].world.y = d;
			break;
		case 0:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].world.z = d;
			break;
		case 1:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].image.x = d;
			break;
		case 2:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].image.y = d;
			break;
		default:
			break;
		}

		if (t == 471) {
			d = str2double(*iter);
			_prvface->face.headPosition.headCenter.x = d;
		}
		if (t == 472) {
			d = str2double(*iter);
			_prvface->face.headPosition.headCenter.y = d;
		}
		if (t == 473) {
			d = str2double(*iter);
			_prvface->face.headPosition.headCenter.z = d;
		}
		if (t == 474) {
			d = str2double(*iter);
			_prvface->face.poseEulerAngles.pitch = d;
		}
		if (t == 475) {
			d = str2double(*iter);
			_prvface->face.poseEulerAngles.roll = d;
		}
		if (t == 476) {
			d = str2double(*iter);
			_prvface->face.poseEulerAngles.yaw = d;
		}
	}
	std::cout << v_s.size()<<std::endl;

}

void ReadData::Anal_CK(std::string str)
{
	str.size();
	std::string s;
	std::vector<std::string> v_s;
	std::vector<double> v_d;
	int tag = -1;
	for (int i = 0, j = 0; i < str.length(); i++)
	{
		if (str[i] != '\t')
			s += str[i];
		else
		{
			v_s.push_back(s);
			s.clear();
		}
	}

	int t = 0, id = 256;
	for (std::vector<string>::iterator iter = v_s.begin(); iter != v_s.end(); iter++, t++)
	{
		if (t < 1)
			continue;
		double d = 0.0;
		if (t<256) switch (t % 3)
		{
		case 1:
			id = str2int(*iter);
			_prvface->face.landmarkPoint[id].source.index = id;
			break;
		case 2:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].image.x = d;
			break;
		case 0:
			d = str2double(*iter);
			_prvface->face.landmarkPoint[id].image.y = d;
			break;
		default:
			break;
		}
	}
	std::cout << ">" << std::endl;
}
#pragma endregion

#pragma region 字符型转数值型
double ReadData::str2double(std::string str)
{
	std::stringstream ss;
	double i;
	ss << str;
	ss >> i;
	return i;
}

int ReadData::str2int(std::string str)
{
	std::stringstream ss;
	int i;
	ss << str;
	ss >> i;
	return i;
}
#pragma endregion

ReadData::~ReadData()
{

}
