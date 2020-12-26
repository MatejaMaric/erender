#include"Matrix4f.h"
class Vector4f
{
public:
	float x, y, z, w;
	Vector4f();
	Vector4f(float x_, float y_, float z_, float w_);
	float dotProduct(const Vector4f& a);
	Vector4f crossProduct(const Vector4f& a);
	Vector4f multiplyMatrix(const Matrix4f& a);
};

