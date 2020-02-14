// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "Text.h"
#include "GLES3/gl31.h"
#include "../AssetLoader/MeshLoaderFromObj.h"
#include "Actor.h"
#include "AMP_Engine.h"
#include "Components/Mesh.h"
#include "GLHelper.h"

namespace amp
{
	class CubeMap : public Actor
	{
	public:
		CubeMap(amp::Type type):Actor(type){
			cube = AddComponent<Mesh>();
		};
		virtual ~CubeMap();
		CubeMap(const CubeMap&) = delete;
		CubeMap(CubeMap&&) = delete;

		void createCubeMap(TEXT forward, TEXT backward, TEXT left, TEXT right, TEXT top, TEXT bottom);

		void SetCubeMapParams();

		void CreateCubemap();

		void SetCubeMapTextures(TEXT* paths);

		void drawAfterScene();

		void BeforeSystemShutdown() override;

		Mesh* cube;
	private:
		TEXT boxObj = TEXT("3DModels/box.obj");
		TEXT boxMtl = TEXT("3DModels/box.mtl");
		TEXT shaderPath = TEXT("Shader/Skybox.glsl");

		unsigned int cubeMapBuffer = GL_NONE;
		unsigned int texID = GL_NONE;
		const int numberOfVertices = 108;
	
		float skyboxVertices[108] = {       
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
	};
}

