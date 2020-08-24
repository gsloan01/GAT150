#pragma once
#include "Vector2.h"

namespace nc
{
	const float PI = 3.1415f;
	const float TWO_PI = PI * 2;
	const float RAD_TO_DEG = (180.0f / PI);
	const float DEG_TO_RAD = (PI / 180.0f);

	inline float RadiansToDegrees(float radians)
	{
		return radians * RAD_TO_DEG;
	}
	inline float DegreesToRadians(float degrees)
	{
		return degrees * DEG_TO_RAD;
	}

}