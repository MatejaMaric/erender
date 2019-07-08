#include"ObjModel.h"
class Render : public Bitmap
{
private:
	float edgeFun(const Vertice& A, const Vertice& B, const Vertice& P);
public:
	float* zBuffer;
	Render(int width_, int height_);
	void drawTriangle(Vertice t1, Vertice t2, Vertice t3, Bitmap& texture);
	void renderModel(ObjModel& model, Bitmap& texture);
	void resetZBuf();
};

