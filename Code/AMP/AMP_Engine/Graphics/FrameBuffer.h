// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>
#include "GLES3/gl3platform.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "string"
#include "GLHelper.h"


namespace amp
{
	enum ShadingType {
		DEFAULT			= 0,
		INVERSE_COLOR	= 1,
		BLUR			= 2
	};
	
	class AMP_Engine;
	class FrameBuffer
	{
	public:
		FrameBuffer() {};
		~FrameBuffer();

		FrameBuffer(const FrameBuffer& f) = delete;
		FrameBuffer(FrameBuffer&& f) = delete;

		void setShaderPath(std::string path);
		void setShadingType(ShadingType type);
		ShadingType getShadingType();

	private:
		void enable(AMP_Engine* engine);
		void SetFragmentShaderFastest();
		void CreateFrameRenderBuffer();
		void SetRenderBuffer();
		void CreateRenderBuffer();
		void CreateFrameBuffer();
		void CreateFrameBufferTexture();
		void GetShader();
		void clear(bool isLowestLayer = false);
		void drawFrameBufferContent();
		void EnableDepthTesting();
		void DisableBlend();
		void BindFrameBuffer();
		void EnableBlend();
		void DisableDepthTesting();

		std::string shaderPath = "Shader/DefaultFrameBufferShader.glsl";
		ShadingType shadingType = ShadingType::DEFAULT;
		AMP_Engine* engine = nullptr;

		unsigned int mainFramebuffer = GL_NONE;
		unsigned int texColorBuffer = GL_NONE;
		unsigned int rbo = GL_NONE;
		unsigned int vertexBuffer = GL_NONE;
		unsigned int uvBuffer = GL_NONE;
		unsigned int shaderProgram = GL_NONE;
		unsigned int TextureID;

		glm::vec2 verticesArray[6] = {
			glm::vec2(-1, 1),  //top-left
			glm::vec2(-1,-1),  //bottom-left
			glm::vec2( 1, 1),  //top-right

			glm::vec2( 1,-1),  //bottom-right
			glm::vec2( 1, 1),  //top-right
			glm::vec2(-1,-1)   //bottom-left
		};

		glm::vec2 uvsArray[6] = {
			glm::vec2(0,1), //top-left
			glm::vec2(0,0),	//bottom-left
			glm::vec2(1,1),	//top-right

			glm::vec2(1,0),	//bottom-right
			glm::vec2(1,1),	//top-right
			glm::vec2(0,0)	//bottom-left
		};
		friend class AMP_Engine;
	};
}

