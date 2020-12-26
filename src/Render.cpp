#include <limits>

#include "Render.h"

Render::Render(int width_, int height_) : Bitmap(width_, height_)
{
	zBuffer = new float[width * height];
	for (int i = 0; i < width * height; i++)
		zBuffer[i] = std::numeric_limits<float>::infinity();
}

float Render::edgeFun(const Vertice& A, const Vertice& B, const Vertice& P)
{
	return ((P.x - A.x)*(B.y - A.y) - (P.y - A.y)*(B.x - A.x));
}

void Render::drawTriangle(Vertice t1, Vertice t2, Vertice t3, Bitmap& texture)
{
	int maxx = fmax(t1.x, fmax(t2.x, t3.x));
	int minx = fmin(t1.x, fmin(t2.x, t3.x));
	int maxy = fmax(t1.y, fmax(t2.y, t3.y));
	int miny = fmin(t1.y, fmin(t2.y, t3.y));

	Vertice p((float)minx + 0.5f, (float)miny + 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	
	int surface = edgeFun(t1, t2, t3);
	int w1_row = edgeFun(t2, t3, p);	int w1xk = (t3.y - t2.y), w1yk = -(t3.x - t2.x);
	int w2_row = edgeFun(t3, t1, p);	int w2xk = (t1.y - t3.y), w2yk = -(t1.x - t3.x);
	int w3_row = edgeFun(t1, t2, p);	int w3xk = (t2.y - t1.y), w3yk = -(t2.x - t1.x);

	for (int y = miny; y < maxy; y++) {
		int w1_vertice = w1_row;
		int w2_vertice = w2_row;
		int w3_vertice = w3_row;
		for (int x = minx; x < maxx; x++) {

			float w1 = w1_vertice;
			float w2 = w2_vertice;
			float w3 = w3_vertice;
			
				if ((w3 >= 0 && w1 >= 0 && w2 >= 0) || (w3 <= 0 && w1 <= 0 && w2 <= 0))
				{
					w1 /= surface;
					w2 /= surface;
					w3 /= surface;

					float w = 1.0f / (w1 * t1.w + w2 * t2.w + w3 * t3.w);
					float z =/* w * */1.0f / ((w1 * t1.z + w2 * t2.z + w3 * t3.z) * w);
					if (zBuffer[(y * (width)) + x] > z) {
						zBuffer[(y * (width)) + x] = z;
						float u = w * (w1 * t1.u + w2 * t2.u + w3 * t3.u);
						float v = w * (w1 * t1.v + w2 * t2.v + w3 * t3.v);

						u = round((u * texture.width));
						v = round((v * (texture.height - 1)));

						int hlp = ((v * texture.width) + u) * 4;
						int r = texture.pixels[hlp + 0];
						int g = texture.pixels[hlp + 1];
						int b = texture.pixels[hlp + 2];
						setPixel(x, y, r, g, b);
					}
				}
			
			w1_vertice += w1xk;
			w2_vertice += w2xk;
			w3_vertice += w3xk;
		}
		
		w1_row += w1yk;
		w2_row += w2yk;
		w3_row += w3yk;
	}
}


void Render::renderModel(ObjModel& model, Bitmap& texture)
{
	for (int i = 0; i < model.faces.size(); i++) {
		
		model.vertices[model.faces[i].p[0][0] - 1].u = model.uvcoo[model.faces[i].p[0][1] - 1].u * model.vertices[model.faces[i].p[0][0] - 1].w;
		model.vertices[model.faces[i].p[0][0] - 1].v = model.uvcoo[model.faces[i].p[0][1] - 1].v * model.vertices[model.faces[i].p[0][0] - 1].w;

		model.vertices[model.faces[i].p[1][0] - 1].u = model.uvcoo[model.faces[i].p[1][1] - 1].u * model.vertices[model.faces[i].p[1][0] - 1].w;
		model.vertices[model.faces[i].p[1][0] - 1].v = model.uvcoo[model.faces[i].p[1][1] - 1].v * model.vertices[model.faces[i].p[1][0] - 1].w;

		model.vertices[model.faces[i].p[2][0] - 1].u = model.uvcoo[model.faces[i].p[2][1] - 1].u * model.vertices[model.faces[i].p[2][0] - 1].w;
		model.vertices[model.faces[i].p[2][0] - 1].v = model.uvcoo[model.faces[i].p[2][1] - 1].v * model.vertices[model.faces[i].p[2][0] - 1].w;
		

		drawTriangle(model.vertices[model.faces[i].p[0][0] - 1], model.vertices[model.faces[i].p[1][0] - 1], model.vertices[model.faces[i].p[2][0] - 1], texture);
	}
}

void Render::resetZBuf() {
	for (int i = 0; i < width * height; i++)
		zBuffer[i] = std::numeric_limits<float>::infinity();
}
