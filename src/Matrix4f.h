#include<math.h>
class Matrix4f
{
public:
	float m[4][4];
	Matrix4f();
	Matrix4f multiply(Matrix4f& a);
	Matrix4f operator* (Matrix4f& a);
	static Matrix4f identity();
	static Matrix4f move(float kx, float ky, float kz);
	static Matrix4f rotate(float xs, float ys, float zs);
	static Matrix4f scale(float px, float py, float pz);
	static Matrix4f perspective(float near, float far, float fov, float aspectRatio);
};

