#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include"Render.h"

int main()
{
	float width, height;
	float fov;
	std::cout << "Enter window width and height.\n";
	std::cin >> width >> height;
	std::cout << "Enter Field of View.\n";
	std::cin >> fov;
	std::cout << "Loading...\n";

	sf::RenderWindow window(sf::VideoMode(width, height), "C++ CPU Renderer", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	window.setFramerateLimit(60);

	sf::Texture texture;
	texture.create(width, height);

	sf::Sprite sprite(texture);

	sf::Clock clock;
	sf::Time time;

	Render render(width, height);	

  Bitmap* modelTexture;

  bool textureLoaded = false;

	std::chrono::high_resolution_clock::time_point time1 = std::chrono::high_resolution_clock::now();
	sf::Image image;
  textureLoaded = image.loadFromFile("model/modelTexture.png");
  if (textureLoaded) {
    modelTexture = new Bitmap(image.getSize().x, image.getSize().y);
    const sf::Uint8* pp = image.getPixelsPtr();
    for (int i = 0; i < image.getSize().x * image.getSize().y * 4; i += 4) {
      modelTexture->pixels[i + 0] = (unsigned char)pp[i + 0];
      modelTexture->pixels[i + 1] = (unsigned char)pp[i + 1];
      modelTexture->pixels[i + 2] = (unsigned char)pp[i + 2];
      modelTexture->pixels[i + 3] = (unsigned char)pp[i + 3];
    }
  }
	std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> modelTextureLoadingTime = std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1);

	ObjModel model("model/model.obj");

  if (textureLoaded) {
    std::cout << "Texture loading time: " << modelTextureLoadingTime.count() << "\n";
  }
  else {
    std::cerr << "Couldn't load and/or find texture!\n";
  }

  if (model.isLoaded) {
    std::cout << "Model loading time: " << model.loadingTime.count() << "s\n";
    std::cout << "Vertices count: " << model.vertices.size() << "\nNumber of normals: " << model.normals.size() << "\nUV count: " << model.uvcoo.size() << "\n";
    std::cout << "Number of faces: " << model.faces.size() << "\n";
  }
  else {
    std::cerr << "Couldn't load and/or find model!\n";
  }

  if (textureLoaded && model.isLoaded) {
    while (window.isOpen())
    {
      while (window.pollEvent(event))
        if (event.type == sf::Event::Closed)
          window.close();

      time = clock.getElapsedTime();

      Vertice a1, b1, c1, d1, e1, f1;

      Matrix4f move = Matrix4f::move(0.0f, -150.0f, 600.0f);
      Matrix4f rotate = Matrix4f::rotate(0.0f, time.asSeconds() * 25.0f, 0.0f);
      Matrix4f scale = Matrix4f::scale(1.0f, 1.0f, 1.0f);
      Matrix4f project = Matrix4f::perspective(1.0f, 10000.0f, fov, width / height);
      Matrix4f end_matrix = project * move * rotate * scale;
    
      ObjModel projectedModel = model.multiplyMatrix(end_matrix);
      projectedModel.divideW();
      projectedModel.screenspace(width, height);
      

      render.fill(255, 255, 255);
      render.resetZBuf();
      render.renderModel(projectedModel, *modelTexture);
      
      texture.update((sf::Uint8*)render.pixels);
      window.draw(sprite);
      window.display();
    }
  }

  delete modelTexture;

	return 0;
}
