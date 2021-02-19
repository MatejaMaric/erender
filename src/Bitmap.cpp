#include "Bitmap.h"

Bitmap::Bitmap(int width_, int height_) {
  std::chrono::high_resolution_clock::time_point time1 = std::chrono::high_resolution_clock::now();

	width = width_;
	height = height_;
	pixels = new unsigned char[width * height * 4];
  image = nullptr;

	std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
	loadingTime = std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1);
}

Bitmap::Bitmap(std::string fileName) {
  std::chrono::high_resolution_clock::time_point time1 = std::chrono::high_resolution_clock::now();

  image = new sf::Image();
  isLoaded = image->loadFromFile(fileName);
  if (isLoaded) {
    width = image->getSize().x;
    height = image->getSize().y;
    pixels = (unsigned char*)image->getPixelsPtr();
  }
  else {
    width = 0;
    height = 0;
    pixels = nullptr;
  }

	std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
	loadingTime = std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1);
}

Bitmap::~Bitmap() {
  if (image == nullptr)
    delete[] pixels;
  else
    delete image;
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
