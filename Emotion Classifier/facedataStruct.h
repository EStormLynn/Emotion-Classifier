#pragma once
#include "pxcbase.h"

enum LandmarkType
{
	LANDMARK_NOT_NAMED = 0,

	LANDMARK_EYE_RIGHT_CENTER,
	LANDMARK_EYE_LEFT_CENTER,

	LANDMARK_EYELID_RIGHT_TOP,
	LANDMARK_EYELID_RIGHT_BOTTOM,
	LANDMARK_EYELID_RIGHT_RIGHT,
	LANDMARK_EYELID_RIGHT_LEFT,

	LANDMARK_EYELID_LEFT_TOP,
	LANDMARK_EYELID_LEFT_BOTTOM,
	LANDMARK_EYELID_LEFT_RIGHT,
	LANDMARK_EYELID_LEFT_LEFT,

	LANDMARK_EYEBROW_RIGHT_CENTER,
	LANDMARK_EYEBROW_RIGHT_RIGHT,
	LANDMARK_EYEBROW_RIGHT_LEFT,

	LANDMARK_EYEBROW_LEFT_CENTER,
	LANDMARK_EYEBROW_LEFT_RIGHT,
	LANDMARK_EYEBROW_LEFT_LEFT,

	LANDMARK_NOSE_TIP,
	LANDMARK_NOSE_TOP,
	LANDMARK_NOSE_BOTTOM,
	LANDMARK_NOSE_RIGHT,
	LANDMARK_NOSE_LEFT,

	LANDMARK_LIP_RIGHT,
	LANDMARK_LIP_LEFT,

	LANDMARK_UPPER_LIP_CENTER,
	LANDMARK_UPPER_LIP_RIGHT,
	LANDMARK_UPPER_LIP_LEFT,

	LANDMARK_LOWER_LIP_CENTER,
	LANDMARK_LOWER_LIP_RIGHT,
	LANDMARK_LOWER_LIP_LEFT,

	LANDMARK_FACE_BORDER_TOP_RIGHT,
	LANDMARK_FACE_BORDER_TOP_LEFT,

	LANDMARK_CHIN
};

enum LandmarksGroupType
{
	LANDMARK_GROUP_LEFT_EYE = 0x0001,
	LANDMARK_GROUP_RIGHT_EYE = 0x0002,
	LANDMARK_GROUP_RIGHT_EYEBROW = 0x0004,
	LANDMARK_GROUP_LEFT_EYEBROW = 0x0008,
	LANDMARK_GROUP_NOSE = 0x00010,
	LANDMARK_GROUP_MOUTH = 0x0020,
	LANDMARK_GROUP_JAW = 0x0040,
	LANDMARK_GROUP_RIGHT_EAR = 0x0080,
	LANDMARK_GROUP_LEFT_EAR = 0x0100,
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

struct Face
{
	LandmarkPoint landmarkPoint[78];
	HeadPosition headPosition;
	PoseEulerAngles poseEulerAngles;
};


class ExpressionsData
{
public:
	enum FaceExpression
	{
		EXPRESSION_BROW_RAISER_LEFT = 0,
		EXPRESSION_BROW_RAISER_RIGHT = 1,
		EXPRESSION_BROW_LOWERER_LEFT = 2,
		EXPRESSION_BROW_LOWERER_RIGHT = 3,

		EXPRESSION_SMILE = 4,
		EXPRESSION_KISS = 5,
		EXPRESSION_MOUTH_OPEN = 6,

		EXPRESSION_EYES_CLOSED_LEFT = 7,
		EXPRESSION_EYES_CLOSED_RIGHT = 8,

		/* Deprecated API */
		EXPRESSION_HEAD_TURN_LEFT = 9,
		EXPRESSION_HEAD_TURN_RIGHT = 10,
		EXPRESSION_HEAD_UP = 11,
		EXPRESSION_HEAD_DOWN = 12,
		EXPRESSION_HEAD_TILT_LEFT = 13,
		EXPRESSION_HEAD_TILT_RIGHT = 14,
		/* End Deprecated API */

		EXPRESSION_EYES_TURN_LEFT = 15,
		EXPRESSION_EYES_TURN_RIGHT = 16,
		EXPRESSION_EYES_UP = 17,
		EXPRESSION_EYES_DOWN = 18,
		EXPRESSION_TONGUE_OUT = 19,
		EXPRESSION_PUFF_RIGHT = 20,
		EXPRESSION_PUFF_LEFT = 21
	};

	struct FaceExpressionResult
	{
		pxcI32 intensity; // percentage 0 - 100
		pxcI32 reserved[10];
	};

protected:
	virtual ~ExpressionsData() {}
};

class PulseData
{
public:
	/**
	@brief Queries user estimated heart rate.
	@param[out] outHeartRate - Heart rate estimation.
	@return true if the execution was successful , false if heart rate calculation failed.
	*/
	virtual pxcF32 PXCAPI QueryHeartRate() const = 0;
};