// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>
#include "GLES3/gl3platform.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "Component.h"
#include "../AssetLoader/MeshLoaderFromObj.h"
#include "Text.h"
#include "Static/Camera.h"
#include "Graphics/Shader.h"
#include "AMP_Engine.h"
#include "Graphics/GLHelper.h"

namespace amp
{
	class Mesh : public Component
	{
	public:
		Mesh(){};
		Mesh(Mesh&&) = delete;

		Mesh(const Mesh&) = delete;

		virtual ~Mesh();

	public:

		void Mesh_SetUpGL(TEXT ShaderProgramPath,TEXT MeshAttributesPath, TEXT MeshMTLPath,TEXT TexturePath);

	private:
		MeshAttributes* LoadMesh(TEXT MeshAttributesPath, TEXT MeshMTLPath);
		void SetAttributes(MeshAttributes* meshAttr);
		void LoadShader(TEXT ShaderProgramPath);
		void LoadTexture(TEXT TexturePath);
		void draw();
		
		GLuint indexBuffer = GL_NONE;
		GLuint positionBuffer = GL_NONE;
		GLuint texCoordBuffer = GL_NONE;
		GLuint normalBuffer = GL_NONE;
		GLuint texture  = GL_NONE;
		GLuint TexID = GL_NONE;

		unsigned int ShaderProgram;

		GLsizei NumIndices = 0;
		TEXT MeshAttributesPath;
		bool isDrawEnabled = true;
	protected:
	public: void update() override;

		  friend class DynamicMesh;
		  friend class DynamicConcaveMesh;
		  friend class CubeMap;
	};
}

