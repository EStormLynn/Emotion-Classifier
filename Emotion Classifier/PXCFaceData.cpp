#include "PXCFaceData.h"

static std::vector<Face> _faceList;

PXCFaceData::PXCFaceData(void)
{
	
}

void PXCFaceData::update(Face face)
{
	_faceList.push_back(face);
}

std::vector<Face> PXCFaceData::facelist()
{
	return _faceList;
}

PXCFaceData::~PXCFaceData(void)
{

}
