#include"Vertice.h"
#include"Bitmap.h"
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<exception>

struct Triangle {
	int p[3][3];
};

struct Texture_Coordinates {
	float u, v;
};

class ObjModel
{
public:
	std::vector<Vertice> vertices;
	std::vector<Texture_Coordinates> uvcoo;
	std::vector<Vector4f> normals;
	std::vector<Triangle> faces;
	ObjModel();
	ObjModel(std::string fileName);
	ObjModel(const ObjModel& a);
	ObjModel multiplyMatrix(Matrix4f& a);
	void divideW();
	void screenspace(int width, int height);
};

