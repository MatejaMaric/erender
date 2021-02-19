#include<iostream>
#include<string>
#include<chrono>

#include<SFML/Graphics.hpp>

class Bitmap
{
public:
	int width, height;
	unsigned char *pixels;
  sf::Image* image;
  bool isLoaded;
  std::chrono::duration<double> loadingTime;
	Bitmap(int width_, int height_);
	Bitmap(std::string);
	~Bitmap();
	void fill(int r, int g, int b);
	void setPixel(int x,  int y, int r, int g, int b);
};

