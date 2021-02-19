#include "ObjModel.h"



ObjModel::ObjModel() {}

ObjModel::ObjModel(std::string fileName)
{
	std::chrono::high_resolution_clock::time_point time1 = std::chrono::high_resolution_clock::now();

	int hlp = 0;
	std::ifstream f(fileName);
	std::string s0;
	while (getline(f, s0)) {
		std::stringstream ss0(s0);
		std::string s1 = "";
		ss0 >> s1;
		if (s1.compare(0, s1.length(), "v") == 0) {
			ss0 >> s1;
			float x = std::stof(s1);
			ss0 >> s1;
			float y = std::stof(s1);
			ss0 >> s1;
			float z = std::stof(s1);
			Vertice t(x, y, z, 1.0f, 0.0f, 0.0f);
			vertices.push_back(t);
		}
		else if (s1.compare(0, s1.length(), "vn") == 0) {
			ss0 >> s1;
			float x = std::stof(s1);
			ss0 >> s1;
			float y = std::stof(s1);
			ss0 >> s1;
			float z = std::stof(s1);
			Vector4f v(x, y, z, 0.0f);
			normals.push_back(v);
		}
		else if (s1.compare(0, s1.length(), "vt") == 0) {
			ss0 >> s1;
			float u = std::stof(s1);
			ss0 >> s1;
			float v = std::stof(s1);
			Texture_Coordinates kt;
			kt.u = u;	kt.v = v;
			uvcoo.push_back(kt);
		}
		else if (s1.compare(0, s1.length(), "f") == 0) {
			Triangle pt;
			for (int i = 0; i < 3; i++) {
				ss0 >> s1;
				std::stringstream ss1(s1);
				std::string s2;
				for (int j = 0; std::getline(ss1, s2, '/'); j++) {
					pt.p[i][j] = std::stoi(s2);
				}
			}
			faces.push_back(pt);
		}
	}

	std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
	loadingTime = std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1);
}

ObjModel::ObjModel(const ObjModel& a) 
{
	vertices = a.vertices;
	uvcoo = a.uvcoo;
	normals = a.normals;
	faces = a.faces;
}

ObjModel ObjModel::multiplyMatrix(Matrix4f& a) 
{
	ObjModel hlp = *this;
	for (int i = 0; i < vertices.size(); i++)
	{
		hlp.vertices[i] = hlp.vertices[i].multiplyMatrix(a);
	}
	return hlp;
}

void ObjModel::divideW() 
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i] = vertices[i].divideW();
	}
}

void ObjModel::screenspace(int width, int height)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].screenspace(width, height);
	}
}
