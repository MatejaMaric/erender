#include<iostream>
class Bitmap
{
public:
	int width, height;
	unsigned char *pixels;
	Bitmap(int width_, int height_);
	~Bitmap();
	void fill(int r, int g, int b);
	void setPixel(int x,  int y, int r, int g, int b);
};

