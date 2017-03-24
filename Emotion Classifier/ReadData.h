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
	void Analysis(std::string &str, DataFrom tag);  //解析数据
	void Anal_RS(std::string str);					//解析RealSense数据,32个点的
	void Anal_RS78(std::string str);				//解析RealSense数据,78个点的
	void Anal_CK(std::string str);					//解析CK数据,78个点的

	double str2double(std::string str);
	int str2int(std::string str);

};

