#include "MathUtils.h"
#include <stdlib.h>
#include<cmath>

float MathUtils::randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int MathUtils::randomInt(int a, int b)
{
    int range = a - b + 1;
    int num = rand() % range + a;

    return num;
}

float MathUtils::toRadians(float theta_in_degrees) {
    return theta_in_degrees * acos(0.f) / 90.f;
}

float MathUtils::toDegrees(float theta_in_radians) {
    return 90.f * theta_in_radians / acos(0.f);
}