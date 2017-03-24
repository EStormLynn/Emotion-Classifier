#pragma once
#include "facedataStruct.h"
#include "vector"

class PXCFaceData 
{
public:
	PXCFaceData(void);
	~PXCFaceData(void);

	Face face;
	//static std::vector<Face> faceList;


	void static update(Face face);

	std::vector<Face> facelist();


};
