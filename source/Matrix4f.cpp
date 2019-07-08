#include "Matrix4f.h"



Matrix4f::Matrix4f()
{
	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = 0;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
}

Matrix4f Matrix4f::multiply(Matrix4f& a)
{
	Matrix4f b = identity();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			b.m[i][j] = ((m[i][0] * a.m[0][j]) + (m[i][1] * a.m[1][j]) + (m[i][2] * a.m[2][j]) + (m[i][3] * a.m[3][j]));
		}
	}
	return b;
}

Matrix4f Matrix4f::operator*(Matrix4f& a)
{
	Matrix4f b = identity();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			b.m[i][j] = ((m[i][0] * a.m[0][j]) + (m[i][1] * a.m[1][j]) + (m[i][2] * a.m[2][j]) + (m[i][3] * a.m[3][j]));
		}
	}
	return b;
}

Matrix4f Matrix4f::identity()
{
	return Matrix4f();
}

Matrix4f Matrix4f::move(float kx, float ky, float kz)
{
	Matrix4f b;
	b.m[0][0] = 1;	b.m[0][1] = 0;	b.m[0][2] = 0;	b.m[0][3] = kx;
	b.m[1][0] = 0;	b.m[1][1] = 1;	b.m[1][2] = 0;	b.m[1][3] = ky;
	b.m[2][0] = 0;	b.m[2][1] = 0;	b.m[2][2] = 1;	b.m[2][3] = kz;
	b.m[3][0] = 0;	b.m[3][1] = 0;	b.m[3][2] = 0;	b.m[3][3] = 1;
	return b;
}

Matrix4f Matrix4f::rotate(float xs, float ys, float zs)
{
	double hlp = 3.14159265 / 180.0;
	xs *= hlp;
	ys *= hlp;
	zs *= hlp;
	Matrix4f b;
	b.m[0][0] = 1;	b.m[0][1] = 0;			b.m[0][2] = 0;			b.m[0][3] = 0;
	b.m[1][0] = 0;	b.m[1][1] = cos(xs);	b.m[1][2] = -sin(xs);	b.m[1][3] = 0;
	b.m[2][0] = 0;	b.m[2][1] = sin(xs);	b.m[2][2] = cos(xs);	b.m[2][3] = 0;
	b.m[3][0] = 0;	b.m[3][1] = 0;			b.m[3][2] = 0;			b.m[3][3] = 1;

	Matrix4f c;
	c.m[0][0] = cos(ys);	c.m[0][1] = 0;	c.m[0][2] = sin(ys);	c.m[0][3] = 0;
	c.m[1][0] = 0;			c.m[1][1] = 1;	c.m[1][2] = 0;			c.m[1][3] = 0;
	c.m[2][0] = -sin(ys);	c.m[2][1] = 0;	c.m[2][2] = cos(ys);	c.m[2][3] = 0;
	c.m[3][0] = 0;			c.m[3][1] = 0;	c.m[3][2] = 0;			c.m[3][3] = 1;

	Matrix4f d;
	d.m[0][0] = cos(zs);	d.m[0][1] = -sin(zs);	d.m[0][2] = 0;	d.m[0][3] = 0;
	d.m[1][0] = sin(zs);	d.m[1][1] = cos(zs);	d.m[1][2] = 0;	d.m[1][3] = 0;
	d.m[2][0] = 0;			d.m[2][1] = 0;			d.m[2][2] = 1;	d.m[2][3] = 0;
	d.m[3][0] = 0;			d.m[3][1] = 0;			d.m[3][2] = 0;	d.m[3][3] = 1;

	return d * c * b;
}

Matrix4f Matrix4f::scale(float px, float py, float pz)
{
	Matrix4f b;
	b.m[0][0] = px;	b.m[0][1] = 0;	b.m[0][2] = 0;	b.m[0][3] = 0;
	b.m[1][0] = 0;	b.m[1][1] = py;	b.m[1][2] = 0;	b.m[1][3] = 0;
	b.m[2][0] = 0;	b.m[2][1] = 0;	b.m[2][2] = pz;	b.m[2][3] = 0;
	b.m[3][0] = 0;	b.m[3][1] = 0;	b.m[3][2] = 0;	b.m[3][3] = 1;
	return b;
}

Matrix4f Matrix4f::perspective(float n, float f, float fov, float aspectRatio)
{
	float l, r, t, b;
	t = n * tan((fov / 2.0f) * (3.14159265 / 180.0));
	b = -t;
	r = aspectRatio * t;
	l = -r;
	Matrix4f a;
	a.m[0][0] = ((2.0f * n) / (r - l));	a.m[0][1] = 0;						a.m[0][2] = - ((r + l) / (r - l));	a.m[0][3] = 0;
	a.m[1][0] = 0;						a.m[1][1] = ((2.0f * n) / (t - b));	a.m[1][2] = - ((t + b) / (t - b));	a.m[1][3] = 0;
	a.m[2][0] = 0;						a.m[2][1] = 0;						a.m[2][2] = - (f / (n - f));		a.m[2][3] = ((n * f) / (n - f));
	a.m[3][0] = 0;						a.m[3][1] = 0;						a.m[3][2] = 1;						a.m[3][3] = 0;
	return a;
}
