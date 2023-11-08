#include"AngleConverter.h"
#include<cmath>

float AngleConverter::PI = 2 * acos(0.f);

float AngleConverter::toRadians(float theta_in_degrees) {
	return theta_in_degrees * PI / 180.f;
}

float AngleConverter::toDegrees(float theta_in_radians) {
	return 180.f * theta_in_radians / PI;
}