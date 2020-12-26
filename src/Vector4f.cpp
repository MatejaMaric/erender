#include "Vector4f.h"

Vector4f::Vector4f() {}

Vector4f::Vector4f(float x_, float y_, float z_, float w_) 
{
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

float Vector4f::dotProduct(const Vector4f& a)
{
	return ((x * a.x) + (y * a.y) + (z * a.z));
}

Vector4f Vector4f::crossProduct(const Vector4f& a)
{
	return Vector4f((y * a.z - z * a.y), (z * a.x - x * a.z), (x * a.y - y * a.x), (w * a.w));
}

Vector4f Vector4f::multiplyMatrix(const Matrix4f& a)
{
	float x1, y1, z1, w1;
	x1 = ((x * a.m[0][0]) + (y * a.m[0][1]) + (z * a.m[0][2]) + (w * a.m[0][3]));
	y1 = ((x * a.m[1][0]) + (y * a.m[1][1]) + (z * a.m[1][2]) + (w * a.m[1][3]));
	z1 = ((x * a.m[2][0]) + (y * a.m[2][1]) + (z * a.m[2][2]) + (w * a.m[2][3]));
	w1 = ((x * a.m[3][0]) + (y * a.m[3][1]) + (z * a.m[3][2]) + (w * a.m[3][3]));
	return Vector4f(x1, y1, z1, w1);
}

