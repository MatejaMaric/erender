#include "Bitmap.h"

Bitmap::Bitmap(int width_, int height_) {
	width = width_;
	height = height_;
	pixels = new unsigned char[width * height * 4];
}

Bitmap::~Bitmap() {
	delete[] pixels;
}

void Bitmap::fill(int r, int g, int b) {
	for (int i = 0; i < width * height * 4; i+=4)
	{
		pixels[i + 0] = r;
		pixels[i + 1] = g;
		pixels[i + 2] = b;
		pixels[i + 3] = 255;
	}
}

void Bitmap::setPixel(int x, int y, int r, int g, int b) {
	int hlp = ((y * width) + x) * 4;
	if (!(hlp < 0 || hlp >(width * height * 4) - 3)) {
		pixels[hlp + 0] = r;
		pixels[hlp + 1] = g;
		pixels[hlp + 2] = b;
		pixels[hlp + 3] = 255;
	}
	else {
		std::cout << "Position of pixel:\t" << hlp << "\tX: " << x << "\tY: "<< y << "\n";
	}
}
