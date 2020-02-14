// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "Extern/tiny_obj_loader.h"
#include "FilesManager.h"
#include "android/asset_manager.h"
#include "sstream"
#include "istream"
#include "vector"
#include "Extern/stb_image.h"
#include "stdlib.h"
#include "Attributes.h"
#include <string>




struct MeshAttributes : public Attributes{
	std::vector<float> positions;
	std::vector<unsigned int> indices;
	std::vector<float> texCoords;
	std::vector<float> normals;
	std::vector<float> originVertices;
	std::vector<int> originIndices;
	int originIndicesPerFace = 0;

	MeshAttributes() {};
	~MeshAttributes()override {
	};
};

struct TexAttributes : public Attributes{
	int width;
	int height;
	int numberOfComponents;
	unsigned char* data;

	TexAttributes() {};

	~TexAttributes()override {
		free(data);
	};

};

namespace amp
{
	
	class MeshLoaderFromObj
	{
	public:
		MeshLoaderFromObj() {};
		MeshLoaderFromObj(const MeshLoaderFromObj&) = delete;
		MeshLoaderFromObj(MeshLoaderFromObj&&) = delete;

		//Path relative from the Asset Folder as origin
		//Mesh Attributes pointer has to be deleted by the user of this function
		MeshAttributes* loadOBJMesh(const char* path, const char* pathMTL);

		//Path relative from the Asset Folder as origin
		//Tex Attributes pointer has to be deleted by the user of this function
		TexAttributes* loadTextureFromImage(const char* path, bool flip = false);

		//Path relative from the Asset Folder as origin
		//File has to be deleted after usage
		FILE* getRawFile(const char* path);

		//Path relative from the Asset Folder as origin
		//Tex Attributes pointer has to be deleted by the user of this function
		void readOBJVerticesAndIndices(const char* path, MeshAttributes* meshAttr);

		void split(std::string const& str, const char* delim, std::vector<std::string>& out);
	
	private:
		AAssetManager* manager;
		void setAssetManager(AAssetManager* manager) { this->manager = manager; };
		MeshAttributes* readOBJ(std::istringstream& MTLStream, std::istringstream& OBJStream, const char* path);
		friend class AMP_Engine;
	};
}

