# Emotion-Classifier    
### Custom Classifier   
[![Travis](https://img.shields.io/travis/rust-lang/rust.svg)]() [![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://opensource.org/licenses/MIT)     

自己编写的分类器，初步完成6种基本表情分类。    

项目主要分为6个部分   


1.数据解析    
  
- [x] RealSense   
- [x] CK+  
- [ ] MMI   

2.数据存储结构   
  
3.动态特征特征计算   
  
- [x] 欧氏距离特征  
- [x] 角度变化特征  

4.特征向量值->特征状态  
5.特征状态编码匹配表情  
6.相似度排序   

### 目录结构描述
```
tree /f
└─Emotion Classifier
    │
    ├─include
    │      pxcbase.h                    //RealSense pxc头文件
    │      pxcdefs.h
    │      pxcfacedata.h
    │
    └─src
            AngleFeature.cpp            //角度特征
            EuclideanFeature.cpp        //欧式距离特征
            facedataStruct.h            
            Feature.cpp                 //特征基类
            Feature.h
            FeatureState.cpp            //特征状态
            FeatureState.h
            main.cpp                
            PXCFaceData.cpp             //数据信息类
            PXCFaceData.h
            ReadData.cpp                //数据读取
            ReadData.h
```

### 数据解析 
提供2个数据库~~2种~~ 3种格式的txt数据输入解析

函数|说明
---|---
`void Anal_RS(std::string str);`				    |解析RealSense数据,32个标记点
`void Anal_RS78(std::string str);`				|解析RealSense数据,78个标记点
`void Anal_CK(std::string str);`					|解析CK数据,78个标记点


### 数据存储结构 
每帧画面包含的数据包括
**78个标记点**（包括世界坐标，屏幕坐标）信息
**头部中心位置**（世界坐标）
**头部姿态**（~~四元组表示~~欧拉角表示（方便分析）） 
```c++
struct Face
{
	LandmarkPoint landmarkPoint[78];
	HeadPosition headPosition;
	PoseEulerAngles poseEulerAngles;
};
struct LandmarkPointSource
{
	pxcI32 index;
	LandmarkType alias;
	pxcI32 reserved[10];
};

struct LandmarkPoint
{
	LandmarkPointSource source;
	pxcI32 confidenceImage;
	pxcI32 confidenceWorld;
	PXCPoint3DF32 world;
	PXCPointF32   image;
	pxcI32 reserved[10];
};

struct HeadPosition
{
	PXCPoint3DF32 headCenter;
	pxcI32 confidence;
	pxcI32 reserved[9];
};

struct PoseEulerAngles
{
	pxcF32 yaw;
	pxcF32 pitch;
	pxcF32 roll;
	pxcI32 reserved[10];
};

struct PoseQuaternion
{
	pxcF32 x, y, z, w;
	pxcI32 reserved[10];
};
```

## 动态特征特征计算   
包含欧氏距离特征和欧拉角度特征，读取图片序列数据，计算动态变量特征 
<div align=center><img src="http://oo8jzybo8.bkt.clouddn.com/landmarkPoint.png" width="663" height="450" alt="程序界面"/></div>

**欧氏距离特征**      

编号|特征点ID|名称|说明     
---|:---:|:---:|:---:     
1|(4,0)|EYEBROW_RIGHT_RIGHT_to_RIGHT_LEFT|右眼眉毛外边界点 - 右眼眉毛内边界点
2|(9,5)|EYEBROW_LEFT_RIGHT_to_LEFT_LEFT| 左眼眉毛外边界点-左眼眉毛内边界点   
3|(0,5)|EYEBROW_RIGHT_RIGHT_to_LEFT_RIGHT|右眼眉毛内边界点-左眼眉毛内边界点   
4|(33,39)| EYELID_RIGHT_LEFT_to_LEFT_RIGHT|右嘴角点-左嘴角点           
5|(0,10)|EYEBROW_RIGHT_LEFT_to_EYELID_RIGHT_LEFT|右眼眉毛内边界点-右眼内眼角点       
6|(5,18)| EYEBROW_LEFT_RIGHT_to_EYELID_LEFT_RIGHT|左眼眉毛内边界点-左眼内眼角点       
7|(4,14) |EYEBROW_RIGHT_RIGHT_to_EYELID_RIGHT_RIGHT|右眼眉毛外边界点-右眼外眼角点      
8|(9,22)|EYEBROW_LEFT_LEFT_to_EYELID_LEFT_LEFT|左眼眉毛外边界点-左眼外眼角点      
9|(10,14)|EYELID_RIGHT_LEFT_to_RIGHT_RIGHT|右眼内眼角点-右眼外眼角点           
10|(18,22)|	EYELID_LEFT_RIGHT_to_LEFT_LEFT| 左眼内眼角点-左眼外眼角点         
11|(12,16)|		EYELID_RIGHT_TOP_to_RIGHT_BOTTOM| 右上眼皮中点-右下眼皮中点          
12|(20,24)|		EYELID_LEFT_TOP_to_LEFT_BOTTOM| 左上眼皮中点-左下眼皮中点          
13|(10,30)|		EYELID_RIGHT_LEFT_to_NOSE_RIGHT| 右眼内眼角点-右鼻翼点              
14|(18,32)|		EYELID_LEFT_RIGHT_to_NOSE_LEFT| 左眼内眼角点-左鼻翼点              
15|(14,33)|		EYELID_RIGHT_RIGHT_to_LIP_RIGHT| 右眼外眼角点-右嘴角点              
16|(22,39)|		EYELID_LEFT_LEFT_to_LIP_LEFT| 左眼外眼角点-左嘴角点              
17|(30,33)|		NOSE_RIGHT_to_LIP_RIGHT| 右鼻翼点-右嘴角点                  
18|(32,39)|		NOSE_LEFT_to_LIP_LEFT| 左鼻翼点-左嘴角点                  
19|(29,47)|		NOSE_TIP_to_UPPER_LIP_CENTER| 鼻尖点-上嘴唇中点                  
20|(47,51)|		UPPER_LIP_CENTER_to_LOWER_LIP_CENTER| 上嘴唇中点-下嘴唇中点              
21|(51,61)|		LOWER_LIP_CENTER_to_CHIN| 下嘴唇中点-下巴点                  
22|(33,61)|		LIP_RIGHT_to_CHIN| 右嘴角点-下巴点                    
23|(39,61)|		LIP_LEFT_to_CHIN| 左嘴角点-下巴点                    
24|(29,10)|		NOSE_TIP_to_EYELID_RIGHT_LEFT| 鼻尖点-右眼内眼角点                
25|(29,18)|		NOSE_TIP_to_EYELID_LEFT_RIGHT| 鼻尖点-左眼内眼角点       

**角度特征**     

编号|特征点ID|名称|说明  
---|:---:|:---:|:---:  
1|（61，33，58）（61，39，64）|嘴角下拉|up
2|（47，51）|嘴角张大|up
3|（30，33，56）（32，39，66）|嘴角上扬|down
4|（12，14，16）（20，22，24）|眼睛变小|down
5|（12，14，16）（20，22，24）|眼睛变大|up     


## 特征状态编码
![](http://oo8jzybo8.bkt.clouddn.com/%E7%8A%B6%E6%80%81%E7%BC%96%E7%A0%81.png)
```C++
struct State
{
	std::string stateName;		//状态名
	int i;						//状态码，0关，1开
	double d;					//变化量
};

typedef std::map<std::string, State> MapST;
```
## 相似度计算
```C++
double FeatureState::CompareState(MapST myState, MapST eMotionState,int Num)
{
	double similarity = 0.2;

	MapST::iterator iter = eMotionState.begin();
	while (iter != eMotionState.end())
	{
		std::string ss = iter->first;
		if (myState[ss] == iter->second)
		{			
			similarity += iter->second.i*iter->second.d;
		}
		iter++;
	}
	similarity /= eMotionState.size();
	return similarity;
}
```

## Licence

Copyright 2017 EstormLynn [MIT License](https://opensource.org/licenses/MIT)
