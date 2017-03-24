#pragma once
#include "iostream"
#include "fstream"
#include "cassert"
#include "string"
#include "sstream"


class ReadData
{

	enum DataFrom
	{
		Realsense = 0,
		CK,
	};
public:
	friend class PXCFaceData;
	ReadData(std::string &Dir, PXCFaceData *face);
	
	~ReadData();

private:
	void Analysis(std::string &str, DataFrom tag);  //��������
	void Anal_RS(std::string str);					//����RealSense����,32�����
	void Anal_RS78(std::string str);				//����RealSense����,78�����
	void Anal_CK(std::string str);					//����CK����,78�����

	double str2double(std::string str);
	int str2int(std::string str);

};

