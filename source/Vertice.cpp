#include "Vertice.h"

Vertice::Vertice() : Vector4f() {}

Vertice::Vertice(float x_, float y_, float z_, float u_, float v_) : Vector4f (x_, y_, z_, 1)
{
	u = u_;
	v = v_;
}

Vertice::Vertice(float x_, float y_, float z_, float w_, float u_, float v_) : Vector4f(x_, y_, z_, w_)
{
	u = u_;
	v = v_;
}

void Vertice::screenspace(int screenWidth, int screenHeight)
{
	x = round(((x + 1.0f) / 2.0f) * screenWidth);
	y = round(((-y + 1.0f) / 2.0f) * screenHeight);
}

Vertice Vertice::multiplyMatrix(const Matrix4f& a)
{
	float x1, y1, z1, w1;
	x1 = ((x * a.m[0][0]) + (y * a.m[0][1]) + (z * a.m[0][2]) + (w * a.m[0][3]));
	y1 = ((x * a.m[1][0]) + (y * a.m[1][1]) + (z * a.m[1][2]) + (w * a.m[1][3]));
	z1 = ((x * a.m[2][0]) + (y * a.m[2][1]) + (z * a.m[2][2]) + (w * a.m[2][3]));
	w1 = ((x * a.m[3][0]) + (y * a.m[3][1]) + (z * a.m[3][2]) + (w * a.m[3][3]));
	return Vertice(x1, y1, z1, w1, u, v);
}

Vertice& Vertice::operator=(const Vector4f& a) 
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;
	return *this;
}

Vertice Vertice::divideW() 
{
	float rw = 1.0f / w;
	return Vertice(x * rw, y * rw, (z * rw), rw, u * rw, v * rw);
}
