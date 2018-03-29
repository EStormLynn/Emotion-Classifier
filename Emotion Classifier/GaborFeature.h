#pragma once
#include <opencv2/opencv.hpp>
#include <cmath>

#define Gabor_num    40
#define U   8
#define V   5

class GaborFeature
{
public:
	GaborFeature();


	GaborFeature() :m_kmax(CV_PI / 2), m_f(sqrt(2.0)), m_sigma(CV_PI), ds_w(10), ds_h(11), ke_w(31), ke_h(31), raT(0.9) {};

	void  MakeAllGaborKernal();

	void  MakeGaborKernal(int ke_h, int ke_w, int u, int v, Mat &GaborReal, Mat &GaborImg);

	conv2(const Mat &img, const Mat ikernel, convtype type);

	Mat  Gabor_T_Fast1(Mat &src, int ds_h, int ds_w, Mat kel_GR[Gabor_num], Mat kel_GI[Gabor_num]);

	int  Gabor_T_Fast2(Mat &src, int ds_h, int ds_w, Mat kel_GR[Gabor_num], Mat kel_GI[Gabor_num], double* feature);

	Mat  Create_GaborF(Mat& src);

	int  getGaborMeanAndVarianceFeature(Mat &src, double* feature);

private:
	double m_kmax;
	double m_f;
	double m_sigma;
	int ds_w;
	int ds_h;
	int ke_w;
	int ke_h;
	double raT;
	Mat  GaborReal[Gabor_num];
	Mat  GaborImg[Gabor_num];


	~GaborFeature();
};

