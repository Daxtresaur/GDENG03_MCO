#pragma once
class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);

	static float toRadians(float theta_in_degrees);
	static float toDegrees(float theta_in_radians);
};

