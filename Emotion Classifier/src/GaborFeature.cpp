#include "GaborFeature.h"

enum convtype
{
	full,
	same,
	valid
};

GaborFeature::GaborFeature()
{
}

/*
*@函数名： conv2
*@功能：   卷积运算
*@参数：   const Mat &img    原图片
const Mat ikernel 卷积核
convtype type     卷积类型

*@返回值： Mat               矩阵卷积后的结果
*/

Mat GaborFeature::conv2(const Mat &img, const Mat ikernel, convtype type)
{
	Mat dest;
	Mat kernel;
	flip(ikernel, kernel, -1);
	Mat source = img;

	if (type == full)
	{
		source = Mat();
		int additionalRows = kernel.rows - 1, additionalCols = kernel.cols - 1;
		copyMakeBorder(img, source, (additionalRows + 1) / 2, additionalRows / 2, (additionalCols + 1) / 2, additionalCols / 2, BORDER_CONSTANT, Scalar(0));
	}
	Point anchor(kernel.cols - kernel.cols / 2 - 1, kernel.rows - kernel.rows / 2 - 1);
	int borderMode = BORDER_CONSTANT;

	filter2D(source, dest, img.depth(), kernel, anchor, 0, borderMode);

	if (type == valid)
	{
		dest = dest.colRange((kernel.cols - 1) / 2, dest.cols - kernel.cols / 2).rowRange((kernel.rows - 1) / 2, dest.rows - kernel.rows / 2);
	}
	return dest;
}

//生成所有Gabor核
void GaborFeature::MakeAllGaborKernal()
{
	int n = 0;

	for (int v = 0; v<V; v++)
	{
		for (int u = 0; u<U; u++)
		{
			MakeGaborKernal(ke_w, ke_h, u, v, GaborReal[v * 8 + u], GaborImg[v * 8 + u]);
		}
	}
}

/*
*@函数名： MakeGaborKernal
*@功能：   生成固定方向与固定尺度的Gabor核
*@参数：   int ke_h            核函数的高度
int ke_w            核函数的宽度
int u               Gabor的尺度
int v               Gabor的方向
Mat &GaborReal      Gabor的实部
Mat &GaborImg       Gabor的虚部

*@返回值： Mat              返回的Gabor特征
*/
void GaborFeature::MakeGaborKernal(int ke_h, int ke_w, int u, int v, Mat &GaborReal, Mat &GaborImg)
{
	int HarfH = ke_h / 2;
	int HarfW = ke_w / 2;
	double Qu = CV_PI * u / 8;
	double sqsigma = m_sigma * m_sigma;
	double Kv = m_kmax / (pow(m_f, v));
	double postmean = exp(-sqsigma / 2);

	GaborReal.create(HarfH + HarfW + 1, HarfH + HarfW + 1, CV_32FC1);
	GaborImg.create(HarfH + HarfW + 1, HarfH + HarfW + 1, CV_32FC1);
	float *ptr_real = NULL;
	float *ptr_img = NULL;

	for (int j = -HarfH; j <= HarfH; j++)
	{
		ptr_real = GaborReal.ptr<float>(j + HarfH);
		ptr_img = GaborImg.ptr<float>(j + HarfH);

		for (int i = -HarfW; i <= HarfW; i++)
		{
			double tmp1 = exp(-(Kv*Kv*(j*j + i * i) / (2 * sqsigma)));
			double tmp2 = cos(Kv*cos(Qu)*i + Kv * sin(Qu)*j) - postmean;
			double tmp3 = sin(Kv*cos(Qu)*i + Kv * sin(Qu)*j);
			ptr_real[i + HarfW] = Kv * Kv*tmp1*tmp2 / sqsigma;
			ptr_img[i + HarfW] = Kv * Kv*tmp1*tmp3 / sqsigma;
		}
	}
}

/*
*@函数名： Gabor_T_Fast1
*@功能：   获取固定核函数的Gabor特征
*@参数：   Mat &src                原图---彩色图片
int ds_h                下采样的高度
int ds_w                下采样的宽度
Mat kel_GR[Gabor_num]   固定核函数的实部
Mat kel_GI[Gabor_num]   固定核函数的虚部

*@返回值： Mat              返回的Gabor特征
*/
Mat GaborFeature::Gabor_T_Fast1(Mat &src, int ds_h, int ds_w, Mat kel_GR[Gabor_num], Mat kel_GI[Gabor_num])
{
	Mat feature;
	Mat feature1;

	for (int i = 0; i<Gabor_num; i++)
	{
		Mat feat_real_part;
		Mat feat_img_part;
		Mat feat_mode_part;

		feat_real_part = conv2(src, kel_GR[i], same);
		feat_img_part = conv2(src, kel_GI[i], same);
		multiply(feat_real_part, feat_real_part, feat_real_part);
		multiply(feat_img_part, feat_img_part, feat_img_part);
		add(feat_real_part, feat_img_part, feat_mode_part);
		sqrt(feat_mode_part, feat_mode_part);
		Mat tmp2;
		Mat tmp3;
		resize(feat_mode_part, tmp2, Size(ds_w, ds_h));
		tmp3 = tmp2.reshape(1, 1);

		float mean = 0;
		float std = 0;
		float sum1 = 0;
		float sum2 = 0;

		for (int j = 0; j<tmp3.cols; j++)
		{
			sum1 += tmp3.at<float>(0, j);
		}
		mean = sum1 / (tmp3.cols);

		for (int j = 0; j<tmp3.cols; j++)
		{
			sum2 += pow((tmp3.at<float>(0, j) - mean), 2);
		}
		sum2 /= tmp3.cols;
		std = sqrt(sum2);

		subtract(tmp3, mean, tmp3);
		divide(tmp3, std, tmp3);
		feature.push_back(tmp3);
	}

	feature1 = feature.reshape(1, 1);
	return feature1;
}

/*
*@函数名： Gabor_T_Fast2
*@功能：   获取固定核函数的Gabor均值与方差二维特征
*@参数：   Mat &src                原图---彩色图片
int ds_h                下采样的高度
int ds_w                下采样的宽度
Mat kel_GR[Gabor_num]   固定核函数的实部
Mat kel_GI[Gabor_num]   固定核函数的虚部
double* feature         特征值
*/
int GaborFeature::Gabor_T_Fast2(Mat &src, int ds_h, int ds_w, Mat kel_GR[Gabor_num], Mat kel_GI[Gabor_num], double* feature)
{
	vector<float> featureTmp;
	for (int i = 0; i<Gabor_num; i++)
	{
		Mat feat_real_part;
		Mat feat_img_part;
		Mat feat_mode_part;

		feat_real_part = conv2(src, kel_GR[i], same);
		feat_img_part = conv2(src, kel_GI[i], same);
		multiply(feat_real_part, feat_real_part, feat_real_part);
		multiply(feat_img_part, feat_img_part, feat_img_part);
		add(feat_real_part, feat_img_part, feat_mode_part);
		sqrt(feat_mode_part, feat_mode_part);
		Mat tmp2;
		Mat tmp3;
		//使用双线性插值法，使feat_mode_part宽高调整到（ds_w,ds_h)
		resize(feat_mode_part, tmp2, Size(ds_w, ds_h));
		tmp3 = tmp2.reshape(1, 1);

		//求均值mean和方差std
		float mean = 0;
		float std = 0;
		float sum1 = 0;
		float sum2 = 0;
		for (int j = 0; j<tmp3.cols; j++)
		{
			sum1 += tmp3.at<float>(0, j);
		}
		mean = sum1 / (tmp3.cols);

		for (int j = 0; j<tmp3.cols; j++)
		{
			sum2 += pow((tmp3.at<float>(0, j) - mean), 2);
		}
		sum2 /= tmp3.cols;
		std = sqrt(sum2);

		featureTmp.push_back(mean);
		featureTmp.push_back(std);
	}

	for (size_t i = 0; i<featureTmp.size(); ++i)
	{
		*(feature + i) = featureTmp.at(i);
	}

	return 0;
}

/*
*@函数名： Create_GaborF
*@功能：   获取Gabor特征
*@参数：   Mat &src         原图---彩色图片
*@返回值： Mat              返回的Gabor特征
*/
Mat GaborFeature::Create_GaborF(Mat &src)
{
	MakeAllGaborKernal();
	Mat feature;
	double tmp1 = ke_w / 2;
	double tmp2 = ke_h / 2;
	int radius_w = (int)floor(tmp1);
	int radius_h = (int)floor(tmp2);
	int center_w = radius_w + 1;
	int center_h = radius_h + 1;
	int step = 5;
	Mat kel_GR[Gabor_num], kel_GI[Gabor_num];
	int t1 = center_h - radius_h + step;
	int t2 = center_h + radius_h - step;
	int t3 = center_w - radius_w + step;
	int t4 = center_w + radius_w - step;

	for (int m = 0; m<Gabor_num; m++) {
		kel_GR[m] = GaborReal[m](Range(t1 - 1, t2), Range(t3 - 1, t4));
		kel_GI[m] = GaborImg[m](Range(t1 - 1, t2), Range(t3 - 1, t4));
	}

	feature = Gabor_T_Fast1(src, ds_h, ds_w, kel_GR, kel_GI);
	return feature;
}

/*
*@函数名： getGaborMeanAndVarianceFeature
*@功能：   获取Gabor的均值与方差二维特征
*@参数：   Mat &src         原图---彩色图片
double* feature  特征
*@返回值：
0    特征获取成功
-1   特征获取失败
*/
int GaborFeature::getGaborMeanAndVarianceFeature(Mat &src, double* feature)
{
	MakeAllGaborKernal();
	double tmp1 = ke_w / 2;
	double tmp2 = ke_h / 2;
	int radius_w = (int)floor(tmp1);
	int radius_h = (int)floor(tmp2);
	int center_w = radius_w + 1;
	int center_h = radius_h + 1;
	int step = 5;
	Mat kel_GR[Gabor_num], kel_GI[Gabor_num];
	int t1 = center_h - radius_h + step;
	int t2 = center_h + radius_h - step;
	int t3 = center_w - radius_w + step;
	int t4 = center_w + radius_w - step;

	for (int m = 0; m<Gabor_num; m++)
	{
		kel_GR[m] = GaborReal[m](Range(t1 - 1, t2), Range(t3 - 1, t4));
		kel_GI[m] = GaborImg[m](Range(t1 - 1, t2), Range(t3 - 1, t4));
	}

	Gabor_T_Fast2(src, ds_h, ds_w, kel_GR, kel_GI, feature);
	return 0;
}

GaborFeature::~GaborFeature()
{
}
