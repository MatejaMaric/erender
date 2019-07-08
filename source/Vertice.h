#include"Vector4f.h"
class Vertice : public Vector4f
{
public:
	float u, v;
	Vertice();
	Vertice(float x_, float y_, float z_, float u_, float v_);
	Vertice(float x_, float y_, float z_, float w_, float u_, float v_);
	void screenspace(int screenWidth, int screenHeight);
	Vertice multiplyMatrix(const Matrix4f& a);
	Vertice& operator= (const Vector4f& a);
	Vertice divideW();
};

